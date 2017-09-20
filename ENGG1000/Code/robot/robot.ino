#include "settings.h"
#include "motors.h"
#include "ultrasound.h"

void setup(){ 
 
  // Initialize the serial communications
  Serial.begin(9600);
  initializePins();
  
}

// -------------------------------------------------------
// The loop() method runs over and over again
// -------------------------------------------------------
void loop(){
  
  long upDistance = ultrasoundDistance();
  if(upDistance < 5){
    stop();
  }else{
    forward();
  }
  
  delay(10);
}