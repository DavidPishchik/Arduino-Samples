// include the servo library
#include <Servo.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


Servo myServo;  // create a servo object

int const potPin = A0; // analog pin used to connect the potentiometer
int potVal;  // variable to read the value from the analog pin
int angle;   // variable to hold the angle for the servo motor
int switchState = 0;
void setup() {
  lcd.begin(16, 2);
  pinMode(2, INPUT);
  lcd.print("ask the");


  
  
  myServo.attach(9); // attaches the servo on pin 9 to the servo object
  Serial.begin(9600); // open a serial connection to your computer
}



void loop() {
  switchState = digitalRead(2);
  
  potVal = analogRead(potPin); // read the value of the potentiometer
//  // print out the value to the serial monitor
//  Serial.print("potVal: ");
//  Serial.print(potVal);
 
   if (switchState == LOW){
     myServo.write(0);
   } else {
      myServo.write(160);
     delay(1500);

   }
  // scale the numbers from the pot
  angle = map(potVal, 0, 1023, 0, 179);

  // print out the angle for the servo motor
  Serial.print(", angle: ");
  Serial.println(angle);
  
  // set the servo position
 

  // wait for the servo to get there
 
}


