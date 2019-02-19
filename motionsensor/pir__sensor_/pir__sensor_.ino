int ledPin = 13;                // choose the pin for the LED  
int inputPin = 8;               // choose the input pin (for PIR sensor)
//int buzzPin = 7; 
int buzzState = LOW;
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
int totalDetects = 0;
//int sensorValue = 5;
//int sensorLow = 1023;
//int sensorHigh = 0;

int timer = 500;   

void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
//  pinMode(buzzPin, OUTPUT);
  for (int thisPin = 2; thisPin < 8; thisPin++) {
    pinMode(thisPin, OUTPUT);
  }
  Serial.begin(9600);
}
 
void loop(){
//  digitalWrite(buzzPin, HIGH);

//  int pitch = map(sensorValue, sensorLow, sensorHigh, 50, 4000);
  
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
//    digitalWrite(buzzPin, HIGH);
     
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      for (int thisPin = 2; thisPin < 8; thisPin++) {
          //  turn the pin on:
          digitalWrite(thisPin, HIGH);
          delay(timer);
          // turn the pin off:
         
        }

      Serial.println("Motion detected!");
 
//      tone(7, 50); 
      Serial.println(totalDetects);
      totalDetects ++;
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned of
            for (int thisPin = 2; thisPin < 8; thisPin++) {
          //  turn the pin on:
          digitalWrite(thisPin, HIGH);
          delay(timer);
          // turn the pin off:
          digitalWrite(thisPin, LOW);
        }
      Serial.println("Motion ended!");
//      buzzState = LOW;
      
      // We only want to print on the output change, not state
      pirState = LOW;
//      noTone(7);
      delay(300);
    }
  }
}
