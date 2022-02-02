#include "DHT.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include<SoftwareSerial.h>

#define DHTPIN 2     // Digital pin connected to the DHT sensor
 
#define DHTTYPE DHT11   // DHT 11

#define TxD 10
#define RxD 9

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial bluetoothSerial(TxD, RxD);
char state= '0';
volatile float temp, hum;


void setup()
{
  Serial.begin(9600);
  bluetoothSerial.begin(9600);
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Temp=");
  lcd.setCursor(0,1);
  lcd.print("Humidity=");

  dht.begin(); 
}


void loop()
{ 
  float t;
  float h;
  t = dht.readTemperature();
  h = dht.readHumidity();
  if(bluetoothSerial.available()){
    state = bluetoothSerial.read();
    Serial.println(state);
    if(state=='0'){  
      temp=t;
      hum=h;
      lcd.setCursor(5,0);
      lcd.print(t);
      lcd.print(" C");
      lcd.setCursor(9,1);
      lcd.print(h);
      lcd.print("%");
      Serial.print(t);
      Serial.print(" C ");
      Serial.println(h);       
    }
    if(state=='1'){
      Serial.println("State 1");
      Serial.println("Old temp");
      Serial.println(temp);  
      temp=temp+1;
      Serial.println("New temp");
      Serial.println(temp);    
    }
    if(state=='2'){
      Serial.println("State 2");
      Serial.println("Old temp");
      Serial.println(temp); 
      temp = temp-1;
      Serial.println("New temp");
      Serial.println(temp);       
    }
    if(state=='3'){
      Serial.println("State 3");
      Serial.println("Old hum");
      Serial.println(hum); 
      hum = hum + 5;
    }
    if(state=='4'){
      Serial.println("State 4");
      Serial.println("Old hum");
      Serial.println(hum);
      hum = hum - 5;
      Serial.println("New hum");
      Serial.println(hum); 
    }
  }
    lcd.setCursor(5,0);
    lcd.print(t);
    lcd.print(" C");
    lcd.setCursor(9,1);
    lcd.print(h);
    lcd.print("%");
    Serial.print(t);
    Serial.print(" C ");
    Serial.println(h);  
    bluetoothSerial.print(t); //send distance to MIT App
    bluetoothSerial.print(";");
    bluetoothSerial.print(h); //send distance to MIT App 
    bluetoothSerial.print(";");
    bluetoothSerial.print(temp); //send distance to MIT App
    bluetoothSerial.print(";");
    bluetoothSerial.print(hum); //send distance to MIT App
    bluetoothSerial.println(";");
  delay(1000);
}
