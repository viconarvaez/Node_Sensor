#include <Wire.h>
 
#define sht21address B1000000
#define sht21temp  B1001000
#define sht21light B0100011
#define sht21humid B0100111
 
float readSHT21Temp() {
  Wire.beginTransmission(sht21address);
  Wire.write(sht21temp);   
  Wire.endTransmission();
  delay(100);
  Wire.requestFrom(sht21address, 3);
 
  byte msb = Wire.read();
  byte lsb = Wire.read();
  int t = (msb << 8) + lsb;
  int crc = Wire.read();
 
  float temperature = -46.85 + 175.72 * t / 65536.0;
  Serial.print("temperature:");
  Serial.println(temperature);
  return temperature;}

float readSHT21Light() {
  Wire.beginTransmission(sht21address);
  Wire.write(sht21light);   
  Wire.endTransmission();
  delay(100);
  Wire.requestFrom(sht21address, 3);
 
  byte msb = Wire.read();
  byte lsb = Wire.read();
  int l = (msb << 8) + lsb;
  int crc = Wire.read();
 
  float light = l/1.2;    //the expression from the Datasheet
  Serial.print("Light:");
  Serial.println(l);
  Serial.println(msb);
  Serial.println(lsb);
  return light;}

 
float readSHT21Humidity() {
  Wire.beginTransmission(sht21address);
  Wire.write(sht21humid);
  Wire.endTransmission();
  delay(100);
  Wire.requestFrom(sht21address, 3);
 
  byte msb = Wire.read();
  byte lsb = Wire.read();
  int h = (msb << 8) + lsb;
  int crc = Wire.read();
 
  float humidity =  h;
  Serial.print("humidity:");
  Serial.println(humidity);
  return humidity;}
 
void setup() {
  Serial.begin(9600);
  while(!Serial); 
  Serial.println("---- I2C tutorial ----");
  Wire.begin();}
 
void loop(){
  float light = readSHT21Light();
  float temp = readSHT21Temp();
  float hum = readSHT21Humidity();
  delay(1500);}  
