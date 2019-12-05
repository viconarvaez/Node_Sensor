//  Libraries Definition

#include <Wire.h>
#include <Adafruit_ADS1015.h>
//#define temperature 0x48 //B1001000    //Temperature Sensor Address 0x48
#define light  0x23         //Light Sensor Address 0x23
#define humidity 0x27       //Humidity Sensor Address 0x27


Adafruit_ADS1115 ads(0x48);
float Voltage = 0.0;
int Beta = 4540;
float To = 298;
float R1 = 1500000; // Rfixed for generating a Voltage Divisor
float Ro=100000;
float R;
float TempFin;

  

//  Connection with Temp Sensor and ADC (ADS1115)

float readTemp() {
  int16_t adc0;  // we read from the ADC, we have a sixteen bit integer as a result

  adc0 = ads.readADC_SingleEnded(3);

  Voltage = (adc0 * 0.1875) / 1000;
  //R = (Voltage * R1 / 5) / (1 - Voltage / 5);
  R=(R1*5/Voltage)-R1;
  float Temp=-273+Beta*To/(Beta + To*log(R/Ro)); 
 // Serial.print("AIN3: ");
  //Serial.print(Voltage);
  Serial.print("\Temperature: ");
  Serial.println(Temp);
  return Temp;
  delay(100);// before was 1000
}

float readHumidity() {
  Wire.beginTransmission(humidity);
  //Wire.write(sht21humid);// check lecture code
  Wire.endTransmission();
  delay(100);
  Wire.requestFrom(humidity, 3);
 
  byte msb = Wire.read();
  byte lsb = Wire.read();
  int h = (msb << 8) + lsb;
  int crc = Wire.read();
 
  float hum =  h *100.0/ (16384.0-2.0);
  Serial.print("humidity:");
  Serial.println(hum);
  return hum;}

float readLight() {
  Wire.beginTransmission(light);
  Wire.write(0x11);// check lecture code
  Wire.endTransmission();
  delay(100);
  Wire.requestFrom(light, 3);
 
  byte msb = Wire.read();
  byte lsb = Wire.read();
  int l = (msb << 8) + lsb;
  int crc = Wire.read();
 
  float lum = l / 1.2;
  Serial.print("Light:");
  Serial.println(lum);
  return lum;}
  
void setup() {
  Serial.begin(9600);
  ads.begin();
  while(!Serial); 
  Serial.println("---- NO CONNECTION :(((((  ----");
  Wire.begin();}
 
void loop() {
  float Temp = readTemp();
  float hum = readHumidity();
  float lum = readLight();
  
  delay(500);}
