#include <SPI.h>
#include <LoRa.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); //scl-a5 sdl-a4
char data1;
int data2;
void setup() {
Serial.begin(9600);

56

while (!Serial);
Serial.println("LoRa Receiver");

if (!LoRa.begin(433E6)) {
Serial.println("Starting LoRa failed!");
while (1);
}
lcd.init();
lcd.backlight();
lcd.clear();
pinMode(3,OUTPUT);
lcd.setCursor(0, 0);
lcd.print("Saliene Level");
lcd.setCursor(0, 1);
lcd.print("Monitoring");
delay(3000);
}

void loop() {
// try to parse packet
int packetSize = LoRa.parsePacket();
if (packetSize) {
// received a packet
Serial.print("Saline Bottle Weight: '");
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Patient 1 Level");

57

// read packet
while (LoRa.available()) {
//Serial.print((char)LoRa.read());
int data2=int(LoRa.read());

Serial.print(data2);
if(data2>48)
{
digitalWrite(3,HIGH);
lcd.setCursor(1, 1);
lcd.print("***CRITICAL***");
}
else
{
digitalWrite(3,LOW);
lcd.setCursor(2, 1);
lcd.print("***NORMAL***");
}
}
// print RSSI of packet
Serial.print("' with RSSI ");
Serial.println(LoRa.packetRssi());
}
}
