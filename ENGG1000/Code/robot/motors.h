#ifndef MOVEMENT
#define MOVEMENT

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

void pointLeft(int motorSpeed){
    Serial.println("Turning left");
    digitalWrite(rmotor1, HIGH);
    digitalWrite(rmotor2, LOW);
    digitalWrite(lmotor1, LOW);
    digitalWrite(lmotor2, HIGH);

    analogWrite(rspeed, motorSpeed);
    analogWrite(lspeed, motorSpeed);
}

void stop(){
    Serial.println("STOP");
    digitalWrite(rmotor1, LOW);
    digitalWrite(rmotor2, LOW);
    digitalWrite(lmotor1, LOW);
    digitalWrite(lmotor2, LOW);
}
#endif