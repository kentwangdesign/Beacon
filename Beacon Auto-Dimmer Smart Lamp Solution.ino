//PIR Sensor
int PIR = 2;          // choose the input pin for PIR sensor
int previousState = LOW;          // we start, assuming no motion PIR sensor is detected
int PirVal = 0;          // variable for reading the PIR pin status

//Photocell Sensor
int photocellPin = 0;          // choose input pin for the PHOTO sensor
int threshold = 250;          // set PHOTO sensor threshold
int photocellReading;
int DimVal;

//LED Strip
int ledPin = 9;          // choose the pin for the LED strip

//Relay
int relay = 7;          // choose output pin for RELAY

//Others
boolean readMillis = true;          // to only read millis once
unsigned long nowTime;          // time of clock reading


void setup() {
  Serial.begin(9600);
  pinMode(PIR, INPUT);          // declare PIR sensor as input
  pinMode(photocellPin, INPUT);          // declare sensor PHOTO sensor as input
  pinMode(ledPin, OUTPUT);          // declare LED as output
  pinMode(relay, OUTPUT);          // declare RELAY as output
}


void loop() {
  PirVal = digitalRead(PIR);          // read PIR input value
  //Serial.println(millis());
  photocellReading = analogRead(photocellPin);          // read PHOTO sensor input value
  DimVal = map(photocellReading, 1, 120, 220, 20);          // distribute PHOTO sensor value to dimmer range
  DimVal = constrain(DimVal, 10, 225);          // limitation of dimmer range
  delay(1);
  analogWrite(ledPin, DimVal);          // write Relay value

  if ((PirVal == HIGH) && (photocellReading < threshold) && (previousState == LOW)) {          // check if condition is met 
    if (readMillis == true) {
      nowTime = millis();
      delay(10);
      readMillis = false;
      //Serial.println(nowTime);
      digitalWrite(relay, HIGH);          // turn on LED
      //Serial.print(photocellReading);          // print out light brightness
      //Serial.print("\t");
      //Serial.println(DimVal);          // print out dimmer brightness
      //Serial.println("Motion detected!");          // print out PIR status
    }
    //we have just turned on
  }
  

  if (((nowTime + 100000) < millis()) && (readMillis == false) && (PirVal == LOW)) {          // check if condition is NOT met
    digitalWrite(relay, LOW);          // turned off LED
    //Serial.println("Motion ended!");          // print out PIR status
    previousState = LOW;          // change PIR state
    readMillis = true;
  }
  //we have just turned off
}






