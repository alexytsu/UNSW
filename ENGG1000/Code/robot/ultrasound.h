#ifndef ULTRASOUND
#define ULTRASOUND

long ultrasoundDistance(){
    long duration, distance;
    
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digialWrite(trigPin, HIGH);

    delayMicroseconds(10);
    digialWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) /29.1;

    return distance;
}

#endif
