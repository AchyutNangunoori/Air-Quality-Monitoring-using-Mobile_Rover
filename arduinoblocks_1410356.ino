#include <SoftwareSerial.h>
#include <Wire.h>
#include "LiquidCrystal_I2C.h"
#include <DHT.h>

float gas;
SoftwareSerial bt_serial(11,10);
LiquidCrystal_I2C lcd_1(0x27,16,2);
DHT dht(2, DHT11);
float temp;
float humidity;
int dt=2000;
int fnc_dynamic_analogRead(int _pin){
	pinMode(_pin,INPUT);
	return analogRead(_pin);
}

void setup()
{


bt_serial.begin(9600);
	Serial.begin(9600);
	Serial.flush();
	while(Serial.available()>0)Serial.read();

	pinMode(A2, INPUT);

	gas = 0;
	temp = 0;
	//lcd_1.begin();
	lcd_1.noCursor();
	lcd_1.backlight();
  dht.begin();
}


void loop()
{

  	gas = fnc_dynamic_analogRead(0);
    temp=dht.readTemperature();
    humidity=dht.readHumidity();
  	//temp = analogRead(A2);
  	bt_serial.println(String("Gas Value: ")+String(gas));
  	bt_serial.println(String("Temperature: ")+(temp)+String("C"));
    bt_serial.println(String("Humidity: ")+(humidity)+String("%"));
  	Serial.println(String("Gas Value: ")+String(gas));
  	Serial.println(String("Tempearute: ")+(temp)+String(" C"));
    Serial.println(String("Humidity: ")+(humidity)+String(" %"));
  	lcd_1.setCursor(0, 0);
  	lcd_1.print(String("Gas Value: ")+String(gas));
    lcd_1.setCursor(0, 0);
  	lcd_1.print(String("Temperature:")+(temp)+String(" C"));
    lcd_1.setCursor(0, 1);
  	lcd_1.print(String("Humidity:")+(humidity)+String(" %"));
    delay(1000);
}