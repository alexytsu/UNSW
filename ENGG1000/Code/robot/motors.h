#ifndef MOVEMENT
#define MOVEMENT

int speed = 0;

void forward(int motorSpeed)
{
    Serial.println("Moving foward");
    digitalWrite(rmotor1, HIGH);
    digitalWrite(rmotor2, LOW);
    digitalWrite(lmotor1, HIGH);
    digitalWrite(lmotor2, LOW);

    analogWrite(rspeed, motorSpeed);
    analogWrite(lspeed, motorSpeed);
}

void backward(int motorSpeed)
{
    Serial.println("Moving backward");    
    digitalWrite(rmotor1, LOW);
    digitalWrite(rmotor2, HIGH);
    digitalWrite(lmotor1, LOW);
    digitalWrite(lmotor2, HIGH);

    analogWrite(rspeed, motorSpeed);
    analogWrite(lspeed, motorSpeed);
}

void pointRight(int motorSpeed)
{
    Serial.println("Turning right");

    digitalWrite(rmotor1, LOW);
    digitalWrite(rmotor2, HIGH);
    digitalWrite(lmotor1, HIGH);
    digitalWrite(lmotor2, LOW);

    analogWrite(rspeed, motorSpeed);
    analogWrite(lspeed, motorSpeed);
}

void pointLeft(int motorSpeed)
{
    Serial.println("Turning left");
    digitalWrite(rmotor1, HIGH);
    digitalWrite(rmotor2, LOW);
    digitalWrite(lmotor1, LOW);
    digitalWrite(lmotor2, HIGH);

    analogWrite(rspeed, motorSpeed);
    analogWrite(lspeed, motorSpeed);
}

void stop()
{
    Serial.println("STOP");
    digitalWrite(rmotor1, LOW);
    digitalWrite(rmotor2, LOW);
    digitalWrite(lmotor1, LOW);
    digitalWrite(lmotor2, LOW);
}

void motorInterface()
{
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
#endif