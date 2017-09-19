#include "settings.h"
#include "motors.h"

void setup(){ 
 
  // Initialize the serial communications
  Serial.begin(9600);

  // Print the program details
  Serial.println("-------------------------------------");
  Serial.println("Program: Motor Interface"); 
  Serial.println("Initializing ...");

  // Configuration the motor pins

  Serial.print("Motor 1");
  Serial.write(rmotor1);
  Serial.write(rmotor2);

  Serial.print("Motor 2");
  Serial.write(lmotor1);
  Serial.write(lmotor2);   

  // Initialization completed successfully
  Serial.println("Initialization complete");
  
}

// -------------------------------------------------------
// The loop() method runs over and over again
// -------------------------------------------------------
void loop(){
  
  char instruction = 0;
  int pwmDutyCycle = speed * 50;
  // See if there's incoming serial data:
  if (Serial.available()){

    // Read the oldest byte in the serial buffer:
    instruction = Serial.read();  
    
    // Is this a direction; 'f' 'b' 'l' 'r'

    switch (instruction){
        case 'f':
            forward(pwmDutyCycle);
            break;
        case 'b':
            backward(pwmDutyCycle);
            break;
        case 'l':
            pointLeft(pwmDutyCycle);
            break;
        case 'r':
            pointRight(pwmDutyCycle);
            break;
        case 's':
            stop();
            break;
        case 'x': 
            exit();
            break;
        case '0':
        case '1': 
        case '2':
        case '3':
        case '4':
        case '5':
            Serial.print("Set speed to ");
            Serial.write(speed);
            Serial.println("/5");
            speed = int(instruction)/2;
            break;
    }
    delay(10);
  }
}