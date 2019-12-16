int analogPin = 0;     // potentiometer wiper (middle terminal) connected to analog pin 3

                       // outside leads to ground and +5V

int val = 0;           // variable to store the value read



void setup()

{

  Serial.begin(9600);          //  setup serial
  pinMode(13, OUTPUT);
}



void loop()

{

  val = analogRead(analogPin);    // read the input pin

  if(val < 10){
    digitalWrite(13, HIGH);
  }
  else{
    digitalWrite(13, LOW);
  }
  Serial.println(val);             // debug value

}