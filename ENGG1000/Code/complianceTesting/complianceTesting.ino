#define echoPin 11 // Echo Pin
#define trigPin 12 // Trigger Pin
#define LEDPin 13 // Onboard LED

int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance

int rspeed = 10;
int rmotor1 = 8;//
int rmotor2 = 9;

// motor two
int lspeed = 5;
int lmotor1 = 7;
int lmotor2 = 6;

void forward()
{
  digitalWrite(rmotor1, LOW);
  digitalWrite(rmotor2, HIGH);
  analogWrite(rspeed, 250);
  digitalWrite(lmotor1, LOW);
  digitalWrite(lmotor2, HIGH);
  analogWrite(lspeed, 250);

}

void stop()
{
  digitalWrite(rmotor1, LOW);
  digitalWrite(rmotor2, LOW);
  digitalWrite(lmotor1, LOW) ;
  digitalWrite(lmotor2, LOW);
}

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LEDPin, OUTPUT); // Use LED indicator (if required)
  pinMode(rmotor1, OUTPUT);
  pinMode(rmotor2, OUTPUT);
  pinMode(rspeed, OUTPUT);
  pinMode(lmotor1, OUTPUT);
  pinMode(lmotor2, OUTPUT);
  pinMode(lspeed, OUTPUT);

}

void loop() {
  /* The following trigPin/echoPin cycle is used to determine the
    distance of the nearest object by bouncing soundwaves off of it. */
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  //Calculate the distance (in cm) based on the speed of sound.
  distance = duration / 58.2;

  Serial.println(distance);

  if(distance < 50 && distance > 10) {

    stop();
  }else{
    forward();
  }
//Delay 50ms before next reading.
  delay(20);
}