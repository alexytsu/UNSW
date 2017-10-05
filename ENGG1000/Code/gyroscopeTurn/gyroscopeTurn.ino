#include <Wire.h>

#define WHO_AM_I_XG      0x0F
#define CTRL_REG1_G     0x10
#define CTRL_REG2_G     0x11
#define CTRL_REG3_G     0x12
#define ORIENT_CFG_G    0x13
#define INT_GEN_SRC_G   0x14
#define OUT_TEMP_L      0x15
#define OUT_X_L_G     0x18
#define CTRL_REG4     0x1E
#define CTRL_REG9     0x23
#define STATUS_REG_1    0x27
#define OUT_X_L_XL      0x28
#define FIFO_CTRL     0x2E
#define FIFO_SRC      0x2F

#define SENSITIVITY_GYROSCOPE_245    0.00875
#define SENSITIVITY_GYROSCOPE_500    0.0175
#define SENSITIVITY_GYROSCOPE_2000   0.07

int16_t gx, gy, gz; // x, y, and z axis readings of the gyroscope
int16_t temperature; // Chip temperature
float gBias[3] = {0,0,0};
int16_t gBiasRaw[3] = {0,0,0};
float gRes; 
bool _autoCalc = false;

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2
#define ALL_AXIS 3

#define FIFO_OFF 0
#define FIFO_THS 1

//gyro settings
uint16_t scale = 2000; // Changed this to 16-bit
uint8_t sampleRate = 6;
// New gyro stuff:
uint8_t bandwidth = 0;
uint8_t lowPowerEnable = false;
uint8_t HPFEnable = false;
uint8_t HPFCutoff = 0;

int rspeed = 10;
int rmotor1 = 8;//
int rmotor2 = 9;

// motor two
int lspeed = 5;
int lmotor1 = 7;
int lmotor2 = 6;

void stop()
{
  digitalWrite(rmotor1, LOW);
  digitalWrite(rmotor2, LOW);
  digitalWrite(lmotor1, LOW) ;
  digitalWrite(lmotor2, LOW);
}

void turnRight()
{
  digitalWrite(rmotor1, HIGH);
  digitalWrite(rmotor2, LOW);
  analogWrite(rspeed, 200);
  digitalWrite(lmotor1, LOW);
  digitalWrite(lmotor2, HIGH);
  analogWrite(lspeed, 250);

}

uint16_t begin()
{
  // Once we have the scale values, we can calculate the resolution
  // of each sensor. That's what these functions are for. One for each sensor
  gRes = SENSITIVITY_GYROSCOPE_2000;
  
  Wire.begin(); // Initialize I2C

  // To verify communication, we can read from the WHO_AM_I register of
  // each device. Store those in a variable so we can return them.
  uint8_t xgTest = I2CreadByte(WHO_AM_I_XG);  // Read the accel/mag WHO_AM_I

  // Gyro initialization stuff:
  initGyro(); // This will "turn on" the gyro. Setting up interrupts, etc.
  return xgTest;
}

void initGyro()
{
  uint8_t tempRegValue = 0;
  tempRegValue = (sampleRate & 0x07) << 5;

  tempRegValue |= (0x3 << 3);
  tempRegValue |= (bandwidth & 0x3);
  I2CwriteByte(CTRL_REG1_G, tempRegValue);
  
  // CTRL_REG2_G (Default value: 0x00)
  // [0][0][0][0][INT_SEL1][INT_SEL0][OUT_SEL1][OUT_SEL0]
  // INT_SEL[1:0] - INT selection configuration
  // OUT_SEL[1:0] - Out selection configuration
  I2CwriteByte(CTRL_REG2_G, 0x00);  
  
  // CTRL_REG3_G (Default value: 0x00)
  // [LP_mode][HP_EN][0][0][HPCF3_G][HPCF2_G][HPCF1_G][HPCF0_G]
  // LP_mode - Low-power mode enable (0: disabled, 1: enabled)
  // HP_EN - HPF enable (0:disabled, 1: enabled)
  // HPCF_G[3:0] - HPF cutoff frequency
  tempRegValue = lowPowerEnable ? (1<<7) : 0;
  if (HPFEnable)
  {
    tempRegValue |= (1<<6) | (HPFCutoff & 0x0F);
  }
  I2CwriteByte(CTRL_REG3_G, tempRegValue);
  
  // CTRL_REG4 (Default value: 0x38)
  // [0][0][Zen_G][Yen_G][Xen_G][0][LIR_XL1][4D_XL1]
  // Zen_G - Z-axis output enable (0:disable, 1:enable)
  // Yen_G - Y-axis output enable (0:disable, 1:enable)
  // Xen_G - X-axis output enable (0:disable, 1:enable)
  // LIR_XL1 - Latched interrupt (0:not latched, 1:latched)
  // 4D_XL1 - 4D option on interrupt (0:6D used, 1:4D used)
  tempRegValue = 0;
  tempRegValue |= (1<<5);
  tempRegValue |= (1<<4);
  tempRegValue |= (1<<3);
  tempRegValue |= (1<<1);
  I2CwriteByte(CTRL_REG4, tempRegValue);
  
  // ORIENT_CFG_G (Default value: 0x00)
  // [0][0][SignX_G][SignY_G][SignZ_G][Orient_2][Orient_1][Orient_0]
  // SignX_G - Pitch axis (X) angular rate sign (0: positive, 1: negative)
  // Orient [2:0] - Directional user orientation selection
  tempRegValue = 0;
  I2CwriteByte(ORIENT_CFG_G, tempRegValue);
}


// This is a function that uses the FIFO to accumulate sample of accelerometer and gyro data, average
// them, scales them to  gs and deg/s, respectively, and then passes the biases to the main sketch
// for subtraction from all subsequent data. There are no gyro and accelerometer bias registers to store
// the data as there are in the ADXL345, a precursor to the LSM9DS0, or the MPU-9150, so we have to
// subtract the biases ourselves. This results in a more accurate measurement in general and can
// remove errors due to imprecise or varying initial placement. Calibration of sensor data in this manner
// is good practice.
void calibrate(bool autoCalc)
{  
  uint8_t data[6] = {0, 0, 0, 0, 0, 0};
  uint8_t samples = 0;
  int ii;
  int32_t gBiasRawTemp[3] = {0, 0, 0};
  
  // Turn on FIFO and set threshold to 32 samples
  enableFIFO(true);
  setFIFO(FIFO_THS, 0x1F);
  while (samples < 0x1F)
  {
    samples = (I2CreadByte(FIFO_SRC) & 0x3F); // Read number of stored samples
  }
  for(ii = 0; ii < samples ; ii++) 
  { // Read the gyro data stored in the FIFO
    readGyro();
    gBiasRawTemp[0] += gx;
    gBiasRawTemp[1] += gy;
    gBiasRawTemp[2] += gz;
  }  
  for (ii = 0; ii < 3; ii++)
  {
    gBiasRaw[ii] = gBiasRawTemp[ii] / samples;
    gBias[ii] = gRes * gBiasRaw[ii];
  }
  
  enableFIFO(false);
  setFIFO(FIFO_OFF, 0x00);
  
  if (autoCalc) _autoCalc = true;
}

uint8_t gyroAvailable()
{
  uint8_t status = I2CreadByte(STATUS_REG_1);
  
  return ((status & (1<<1)) >> 1);
}


void readGyro()
{
  uint8_t temp[6]; // We'll read six bytes from the gyro into temp
  if ( I2CreadBytes(OUT_X_L_G, temp, 6) == 6) // Read 6 bytes, beginning at OUT_X_L_G
  {
    gx = (temp[1] << 8) | temp[0]; // Store x-axis values into gx
    gy = (temp[3] << 8) | temp[2]; // Store y-axis values into gy
    gz = (temp[5] << 8) | temp[4]; // Store z-axis values into gz
    if (_autoCalc)
    {
      gx -= gBiasRaw[X_AXIS];
      gy -= gBiasRaw[Y_AXIS];
      gz -= gBiasRaw[Z_AXIS];
    }
  }
}

void setGyroODR(uint8_t gRate)
{
  // Only do this if gRate is not 0 (which would disable the gyro)
  if ((gRate & 0x07) != 0)
  {
    // We need to preserve the other bytes in CTRL_REG1_G. So, first read it:
    uint8_t temp = I2CreadByte(CTRL_REG1_G);
    // Then mask out the gyro ODR bits:
    temp &= 0xFF^(0x7 << 5);
    temp |= (gRate & 0x07) << 5;
    // Update our settings struct
    sampleRate = gRate & 0x07;
    // And write the new register value back into CTRL_REG1_G:
    I2CwriteByte(CTRL_REG1_G, temp);
  }
}

void sleepGyro(bool enable)
{
  uint8_t temp = I2CreadByte( CTRL_REG9);
  if (enable) temp |= (1<<6);
  else temp &= ~(1<<6);
  I2CwriteByte(CTRL_REG9, temp);
}

void enableFIFO(bool enable)
{
  uint8_t temp = I2CreadByte(CTRL_REG9);
  if (enable) temp |= (1<<1);
  else temp &= ~(1<<1);
  I2CwriteByte( CTRL_REG9, temp);
}

void setFIFO(uint8_t fifoMode, uint8_t fifoThs)
{
  // Limit threshold - 0x1F (31) is the maximum. If more than that was asked
  // limit it to the maximum.
  uint8_t threshold = fifoThs <= 0x1F ? fifoThs : 0x1F;
  I2CwriteByte( FIFO_CTRL, ((fifoMode & 0x7) << 5) | (threshold & 0x1F));
}

// Wire.h read and write protocols
void I2CwriteByte(uint8_t subAddress, uint8_t data)
{
  Wire.beginTransmission(0x6B);  // Initialize the Tx buffer
  Wire.write(subAddress);           // Put slave register address in Tx buffer
  Wire.write(data);                 // Put data in Tx buffer
  Wire.endTransmission();           // Send the Tx buffer
}

uint8_t I2CreadByte(uint8_t subAddress)
{
  uint8_t data; // `data` will store the register data  
  
  Wire.beginTransmission(0x6B);         // Initialize the Tx buffer
  Wire.write(subAddress);                  // Put slave register address in Tx buffer
  Wire.endTransmission(false);             // Send the Tx buffer, but send a restart to keep connection alive
  Wire.requestFrom((uint8_t)0x6B, (uint8_t) 1);  // Read one byte from slave register address 
  
  data = Wire.read();                      // Fill Rx buffer with result
  return data;                             // Return data read from slave register
}

uint8_t I2CreadBytes(uint8_t subAddress, uint8_t * dest, uint8_t count)
{
  byte retVal;
  Wire.beginTransmission(0x6B);      // Initialize the Tx buffer
  // Next send the register to be read. OR with 0x80 to indicate multi-read.
  Wire.write(subAddress | 0x80);        // Put slave register address in Tx buffer
  retVal = Wire.endTransmission(false); // Send Tx buffer, send a restart to keep connection alive
  if (retVal != 0) // endTransmission should return 0 on success
    return 0;
  
  retVal = Wire.requestFrom((uint8_t)0x6B, count);  // Read bytes from slave register address 
  if (retVal != count)
    return 0;
  
  for (int i=0; i<count;)
    dest[i++] = Wire.read();
  
  return count;
}


/*****************************************************************
LSM9DS1_Basic_I2C.ino
SFE_LSM9DS1 Library Simple Example Code - I2C Interface
Jim Lindblom @ SparkFun Electronics
Original Creation Date: April 30, 2015
https://github.com/sparkfun/LSM9DS1_Breakout

The LSM9DS1 is a versatile 9DOF sensor. It has a built-in
accelerometer, gyroscope, and magnetometer. Very cool! Plus it
functions over either SPI or I2C.

This Arduino sketch is a demo of the simple side of the
SFE_LSM9DS1 library. It'll demo the following:
* How to create a LSM9DS1 object, using a constructor (global
  variables section).
* How to use the begin() function of the LSM9DS1 class.
* How to read the gyroscope, accelerometer, and magnetometer
  using the readGryo(), readAccel(), readMag() functions and 
  the gx, gy, gz, ax, ay, az, mx, my, and mz variables.
* How to calculate actual acceleration, rotation speed, 
  magnetic field strength using the calcAccel(), calcGyro() 
  and calcMag() functions.
* How to use the data from the LSM9DS1 to calculate 
  orientation and heading.

Hardware setup: This library supports communicating with the
LSM9DS1 over either I2C or SPI. This example demonstrates how
to use I2C. The pin-out is as follows:
    LSM9DS1 --------- Arduino
     SCL ---------- SCL (A5 on older 'Duinos')
     SDA ---------- SDA (A4 on older 'Duinos')
     VDD ------------- 3.3V
     GND ------------- GND
(CSG, CSXM, SDOG, and SDOXM should all be pulled high. 
Jumpers on the breakout board will do this for you.)

The LSM9DS1 has a maximum voltage of 3.6V. Make sure you power it
off the 3.3V rail! I2C pins are open-drain, so you'll be 
(mostly) safe connecting the LSM9DS1's SCL and SDA pins 
directly to the Arduino.

Development environment specifics:
    IDE: Arduino 1.6.3
    Hardware Platform: SparkFun Redboard
    LSM9DS1 Breakout Version: 1.0

This code is beerware. If you see me (or any other SparkFun 
employee) at the local, and you've found our code helpful, 
please buy us a round!

Distributed as-is; no warranty is given.
*****************************************************************/
#define PRINT_CALCULATED
#define PRINT_SPEED 250 // 250 ms between prints
static unsigned long lastPrint = 0; // Keep track of print time

void setup() 
{
  Serial.begin(9600);
  
  if (!begin())
  {
    Serial.println("Failed to communicate with LSM9DS1.");
    Serial.println("Double-check wiring.");
    Serial.println("Default settings in this sketch will " \
      "work for an out of the box LSM9DS1 " \
      "Breakout, but may need to be modified " \
      "if the board jumpers are.");
    while (1)
      ;
  }
  pinMode(rmotor1, OUTPUT);
  pinMode(rmotor2, OUTPUT);
  pinMode(rspeed, OUTPUT);
  pinMode(lmotor1, OUTPUT);
  pinMode(lmotor2, OUTPUT);
  pinMode(lspeed, OUTPUT);
  
  calibrate(true);
}
double totalx;
double totaly;
double totalz;

void loop()
{
  // Update the sensor values whenever new data is available
  if ( gyroAvailable() )
     readGyro();   //to read specific axis: call imu.readGyro(X_AXIS)

   if(totalx < 90){
     turnRight();
   }else{
     stop();
   }

printGyro();
delay(10);
}



void printGyro()
{
  // Now we can use the gx, gy, and gz variables as we please.
  // Either print them as raw ADC values, or calculated in DPS.

  totalx += gRes * gx/100;
  totaly += gRes * gy/100;
  totalz += gRes * gz/100;
  
  /*
  Serial.print(gRes * gx, 2);
  Serial.print("\t");
  Serial.print(gRes * gy, 2);
  Serial.print("\t");
  Serial.print(gRes * gz, 2);
  Serial.print("\t");
  Serial.println(millis());
  */
  Serial.println(totalx, 2);
  //Serial.print("\t");
  //Serial.print(totaly, 2);
  //Serial.print("\t");
  //Serial.print(totalz, 2);
  //Serial.print("\t\n");
}