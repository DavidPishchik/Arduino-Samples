/* How to use the DHT-22 sensor with Arduino uno
   Temperature and humidity sensor
*/

//Libraries
#include <DHT.h>

//Constants
int plusswitchpin = 0;     
int minuswitchpin = 0;    
#define DHTPIN 7     // Define DHT Pin 
#define DHTTYPE DHT22  // Define DHT 22  (AM2302) 
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino


//Variables
float hum;  //Stores humidity value
float temp; //Stores temperature value
int baseTemp = 20;


void setup() {

  pinMode(8, INPUT); // Btn to adjsut BaseTemp
  pinMode(9, INPUT); // Btn to adjsut BaseTemp
  
  Serial.begin(9600);
  dht.begin();

}



void loop() {
  plusswitchpin = digitalRead(9);
  minuswitchpin = digitalRead(8);
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
       
    if(hotTemp(temp, baseTemp)){
         // do something   
         Serial.print(" %,  Base Temp: ");
         Serial.print(baseTemp);
         Serial.print(" %,  Hot Temp: ");
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

