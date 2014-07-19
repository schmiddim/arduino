
/*

AUTHOR: Hazim Bitar (techbitar)
DATE: Aug 29, 2013
LICENSE: Public domain (use at your own risk)
CONTACT: techbitar at gmail dot com (techbitar.com)

Source (including Manual for configuring the BT Chip
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
HC-05 TX --- Arduino Pin A0 (soft RX)
HC-05 RX --- Arduino Pin A1 (soft TX)
HC-05 Key (PIN 34) --- Arduino 5V


Beeper Wiring 12
*/
#define BT_RX A1
#define BT_TX A0


#include <SoftwareSerial.h>
 
SoftwareSerial BTSerial(BT_RX, BT_TX); // RX | TX
const int buzzer = 8;       //the buzzer
const int led=A2;  


String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup()
{
  pinMode(12, OUTPUT);    //Buzzere
  
  
  pinMode(8, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
  
  
  digitalWrite(BT_KEY, HIGH);
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  BTSerial.begin(9600);  // HC-05 default speed in AT command more
  BTSerial.println("Enter AT commands:");
  
  inputString.reserve(200);

}

void loop()
{
  
  //@todo - Newline / CR Stuff
  
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
  if(command == "led on\n"){
    digitalWrite(led, HIGH);
  }else if(command == "led off\n"){
    
    digitalWrite(led, LOW);  
  }else if(command=="beep\n"){
     beep(); 
  }else if(command.substring(0) == "beep_d"){
   
  }  else {
    Serial.println("==Commands==");
    Serial.println("led on");    
    Serial.println("led off");    
    Serial.println("beep");
    Serial.println("beep_d [duration]");
    
    BTSerial.println("==Commands==");
    BTSerial.println("led on");    
    BTSerial.println("led off");    
    BTSerial.println("beep");
    BTSerial.println("beep_d [duration]");
  }
}

//do a beep
void beep(){
    analogWrite(buzzer,128);
    delay(500);
    digitalWrite(buzzer, LOW);

}
//do a beep
void beep(int duration){
    analogWrite(buzzer,128);
    delay(duration);
    digitalWrite(buzzer, LOW);

}
