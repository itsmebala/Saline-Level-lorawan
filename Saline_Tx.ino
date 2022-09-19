Program for LoRa Sender

#include <SPI.h>
#include <LoRa.h>
#include "HX711.h"
#define DOUT 3
#define CLK 4

HX711 scale(DOUT, CLK);
float calibration_factor = -96650;
int data1;
void setup() {
Serial.begin(9600);
Serial.println("Press T to tare");
scale.set_scale(-96650);
scale.tare();
while (!Serial);
Serial.println("LoRa Sender");
if (!LoRa.begin(433E6)) {
Serial.println("Starting LoRa failed!");
while (1);

} pinMode(5,OUTPUT);
pinMode(8,OUTPUT);
}

void loop() {
Serial.print("Saline Bottle Weight: ");
Serial.print(scale.get_units(), 2);
Serial.println(" kg");
if(scale.get_units()<2)
{
digitalWrite(5,HIGH);
}
else
{
digitalWrite(5,LOW);
}

if(scale.get_units()<1)
{
digitalWrite(8,LOW);
data1=1;
}
else
{
digitalWrite(8,HIGH);
data1=0;
}

if(Serial.available())

55

{
char temp = Serial.read();
if(temp == 't' || temp == 'T')
scale.tare();
}

Serial.print("Lora Data Sent: ");
Serial.print(data1);
Serial.println("");
LoRa.beginPacket();
//LoRa.print("Saline Bottle Weight: ");
LoRa.print(data1);
LoRa.endPacket();
delay(5000);
}
