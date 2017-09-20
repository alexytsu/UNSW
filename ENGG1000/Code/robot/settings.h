#ifndef SETTINGS
#define SETTINGS

// motor one
#define rspeed 10;
#define rmotor1 8;
#define rmotor2 9;

// motor two
#define lspeed 5;
#define lmotor1 7;
#define lmotor2 6;

// ultrasound pins
#define trigPin 13
#define echoPin 12

void initializePins(){
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    pinMode(rspeed, OUTPUT);
    pinMode(rmotor1, OUPUT);
    pinMode(rmotor2, OUPUT);
    
    pinMode(lspeed, OUPUT);
    pinMode(lmotor1, OUPUT);
    pinMode(lmotor2, OUPUT);
}
#endif