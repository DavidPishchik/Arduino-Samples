#include <DHT.h>
#include <Servo.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo myServo;

//Constants
int plusswitchpin = 0;     
int minuswitchpin = 0;    
#define DHTPIN 7     // Define DHT Pin 
#define DHTTYPE DHT22  // Define DHT 22  (AM2302) 
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino
int angle;   // variable to hold the angle for the servo motor
int switchState = 0;

//Variables
float hum;  //Stores humidity value
float temp; //Stores temperature value
int baseTemp = 20;


void setup() {
  // put your setup code here, to run once:
  pinMode(8, INPUT); // Btn to adjsut BaseTemp
  pinMode(9, INPUT); // Btn to adjsut BaseTemp
  myServo.attach(13); 
  Serial.begin(9600);
  lcd.begin(16, 2);
  dht.begin();
}
void loop() {
  plusswitchpin = digitalRead(9);
  minuswitchpin = digitalRead(8);
  switchState = digitalRead(10);
    delay(2000);
    //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp= dht.readTemperature();
     
    if (plusswitchpin == 1){
      baseTemp++;
       Serial.print("increase by 1: ");
    }
    
    if (minuswitchpin == 1){
       baseTemp-- ;
        Serial.print("decrease by 1: ");
    }
    
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.print(" Celsius");
    Serial.print(" %,  Base Temp: ");
    Serial.println(baseTemp);
    
    lcd.setCursor(0, 0);
     lcd.print("SET:");   
     lcd.print(baseTemp);
     lcd.print((char)223);
      lcd.print(" H: ");   
      lcd.print(hum);
      lcd.print("%");  
   lcd.setCursor(0, 2);
     lcd.print("TEMP "); 
     lcd.print("C:");   
     lcd.print(round(temp)); 
     lcd.print((char)223);
     lcd.print(" F:");  
     lcd.print(round(temp * 1.8 + 32)); 
     lcd.print((char)223); 
    if(hotTemp(temp, baseTemp)){
         // do something   
         Serial.print(" %,  Base Temp: ");
         Serial.print(baseTemp);
         Serial.print(" %,  Hot Temp: ");
    }

   if (switchState == 0){
     myServo.write(100);
   } else {
      myServo.write(0);
     delay(1500);

   }
    delay(500); //Delay 2 sec.

    
}

boolean hotTemp(int temp, int baseTemp)
{
   boolean bigger = false;

   if (temp > baseTemp){
      bigger = true;
   }
   return bigger; 
}
