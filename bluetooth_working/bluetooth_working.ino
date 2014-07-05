
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

//Serial Event
http://arduino.cc/en/Tutorial/SerialEvent
This works on Digital Pins!

HC-05 GND --- Arduino GND Pin
HC-05 VCC (5V) --- Arduino 5V
HC-05 TX --- Arduino Pin 10 (soft RX)
HC-05 RX --- Arduino Pin11 (soft TX)
HC-05 Key (PIN 34) --- Arduino Pin 9


Beeper Wiring 12
*/


#include <SoftwareSerial.h>
 
SoftwareSerial BTSerial(10, 11); // RX | TX
const int buzzer = 8;       //the buzzer
const int led=12;  


String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup()
{
  pinMode(12, OUTPUT);    //Buzzere
  
  
  pinMode(8, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
  digitalWrite(9, HIGH);
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  BTSerial.begin(9600);  // HC-05 default speed in AT command more
  BTSerial.println("Enter AT commands:");
  
  inputString.reserve(200);

}

void loop()
{
  
 // digitalWrite(led, HIGH);
 // beep();  
  
  
  
  
   while (BTSerial.available()) {
    // get the new byte:
    char inChar = (char)BTSerial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
        Serial.println(inputString);
         BTSerial.println(inputString);
         processCommand("BT", inputString);
         inputString="";
    } 
  }  
   while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
        Serial.println(inputString);
         BTSerial.println(inputString);
         processCommand("PC", inputString);
         inputString="";
    } 
  }
  
}

//Handle commands here
void processCommand(String from, String command){

  
}

//do a beep
void beep(){
    analogWrite(buzzer,128);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);
}
