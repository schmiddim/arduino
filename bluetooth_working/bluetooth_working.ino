
/*

AUTHOR: Hazim Bitar (techbitar)
DATE: Aug 29, 2013
LICENSE: Public domain (use at your own risk)
CONTACT: techbitar at gmail dot com (techbitar.com)

Source
http://www.instructables.com/id/Modify-The-HC-05-Bluetooth-Module-Defaults-Using-A/



App
//  https://play.google.com/store/apps/details?id=mobi.dzs.android.BluetoothSPP

Ebay
// http://www.ebay.de/itm/231258586592?ssPageName=STRK:MEWNX:IT&_trksid=p3984.m1439.l2649


This works on Digital Pins!

HC-05 GND --- Arduino GND Pin
HC-05 VCC (5V) --- Arduino 5V
HC-05 TX --- Arduino Pin 10 (soft RX)
HC-05 RX --- Arduino Pin11 (soft TX)
HC-05 Key (PIN 34) --- Arduino Pin 9

*/


#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX | TX

void setup()
{
  pinMode(9, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
  digitalWrite(9, HIGH);
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  BTSerial.begin(9600);  // HC-05 default speed in AT command more
}

void loop()
{

  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (BTSerial.available())
    Serial.write(BTSerial.read());

  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available())
    BTSerial.write(Serial.read());
}
