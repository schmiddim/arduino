/*
This is a clock driven by a DS1307 RTC Clock Module and controlled via Bluetooth @see Android Code @implement me!
 
 Scripts 7segmentWithTime and rtc_clock merged
 
 http://www.ebay.de/itm/281353517918?ssPageName=STRK:MEWNX:IT&_trksid=p3984.m1439.l2648
 
 @todo: finish me!!!
 
 https://github.com/maniacbug/RTClib
 @see
 http://www.l8ter.com/?p=417
 
 @Wiring:
 Wiring Clock
 SCL → A5
 SDA → A4
 VCC → 5V
 GND → GND
 
 Wiring BT
 HC-05 GND --- Arduino GND Pin
 HC-05 VCC (5V) --- Arduino 5V
 HC-05 TX --- Arduino Pin A1 (soft RX)
 HC-05 RX --- Arduino Pin A0 (soft TX)
 HC-05 Key  (Wakeup) (PIN 34) --- Arduino 5V

Wiring single led + Buzzer
Buzzer GND -> GND
       VCC -> A3
LED   GND -> 220ohm-->GND
      VCC -> A2
      
Date and time functions using a DS1307 RTC connected via I2C and Wire lib

 */
 
 
#define DEBUG 1

#include <Wire.h>
#include <SPI.h>

#include <RTClib.h>       
#include <RTC_DS1307.h>
#include <Charliplexing.h>
#include <led7Segment.h>
#include <SoftwareSerial.h>



//Bluetooth stuff
#define BT_RX A0
#define BT_TX A1

//Buzzer on Port A3
#define BUZZER A3
//LED on Port A2
#define LED A2


RTC_DS1307 RTC;

SoftwareSerial BTSerial(BT_RX, BT_TX); // RX | TX
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete


int brightness=7;

int currentHour=0;
int currentMinute= 0;


//Set the brightness levels for hour of the day (min=0, max=7)
const int brightnessForHours[24] ={
 0       //0
 ,0      //1
 ,0       //2
 ,0       //3
 ,0       //4
 ,0       //5
 ,3       //6
 ,4       //7
 ,7       //8
 ,7       //9
 ,7       //10
 ,7       //11
 ,7       //12
 ,7       //13
 ,7       //14
 ,7       //15
 ,7       //16
 ,7       //17
 ,6       //18
 ,5       //19
 ,4       //20
 ,3       //21
 ,2       //22
 ,1       //23
};

void setup () {

  pinMode(BUZZER, OUTPUT);    //Buzzere
  pinMode(LED, OUTPUT);    //led

  //led stuff 
  LedSign::Init( GRAYSCALE);

  //Bluetooth
  BTSerial.begin(9600);  // HC-05 default speed in AT command more
  inputString.reserve(200);


  Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  DateTime now = RTC.now();
  DateTime compiled = DateTime(__DATE__, __TIME__);
  if (now.unixtime() < compiled.unixtime()) {
    Serial.println("RTC is older than compile time! Updating");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}

void loop () {
  DateTime now = RTC.now();
  //Set Brightness trough array
  
  brightness = brightnessForHours[now.hour()];
  /*
  //Brightness make it darker from 1 - 7 
  if (now.hour() >=0 && now.hour() < 6){
    brightness=0; 
  }
  
  if(now.hour()>=7 && now.hour() <21){
   brightness=6; 
  }

  //Turn off from 22 - 1
  if(now.hour() >= 21 && now.hour() <23){
    brightness = 3; 

  }
    //Turn off from 22 - 1
  if(now.hour() >= 23){
    brightness = 1; 

  }
  */
  

  //Display Digits on Display
  showTime(now.hour(),now.minute(), brightness);  
  if(currentHour != now.hour() || currentMinute != now.minute()){         
    currentHour = now.hour();
    currentMinute= now.minute();         
    LedSign::Clear();
  }

  //Read Commands from Serial USB || BT
  while (BTSerial.available()) {
    // get the new byte:
    char inChar = (char)BTSerial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      processCommand("BT", inputString);
      inputString="";
    } 

  }  
  while (Serial.available()) {
    char inChar = (char)Serial.read(); 
    inputString += inChar;
    if (inChar == '\n') {
      //Serial.println(inputString);
      BTSerial.println(inputString);
      processCommand("PC", inputString);
      inputString="";
    } 
  }
}


//Handle commands here
//@todo wire up Communication Control here
void processCommand(String from, String command){


  if(command.substring(0, 3) == "cmd"){

    //User wants to do something with an alert
    if(command.substring(4,6) =="al"){
      if(command.substring(7,10) == "set"){
        if(validateTimeString(command.substring(11))){
          printlnBoth("timestring valid"); 

        }
      }
      else if(command.substring(7,10) == "del"){
        if(validateTimeString(command.substring(11))){
          printlnBoth("timestring valid"); 

        }          
      }
      else {
        printBoth("invalid...'");
        printlnBoth(command.substring(7,10) );
      }

      // validateTimeString(command);
      //     processAlertCommand(command.substring(6));
    }
    else if (command.substring(4, 8) == "stop"){
      processStopCommand(command.substring(8));
    }
    else if(command.substring(4, 11 ) == "setTime"){
      processSetTimeCommand(command.substring(11));
    }
    else if(command.substring(4,8) == "beep"){
      processBeepCommand(command.substring(8));
    }
    else if(command.substring(4,7) == "led"){
      processLedCommand(command.substring(7) );
    } 
    else{
      printBoth("command unknown: ");
      printlnBoth(command);
      printBothUsage();
    }
  }
  else{
    printBoth("Invalid command: ");
    serialDisplayTime(3000, 1);
  }


}
/**
 *  Timestring has only digits and length ==16?
 *
 */
bool validateTimeString(String timeString){
  if(timeString.length() != 16){
    printlnBoth("E 185" );
    return false;
  }
  for(int i=0;i<14;i++){
    if(i != 6){
      if(!isDigit(timeString.charAt(i) )){
        return false;
      }
    }
  }
  //in range? 
  
  //root@debian:/home/ms/sketchbook# echo "071500 01111100" >/dev/rfcomm0 


  return true;
}

void processStopCommand(String command){
  command.trim();
  printBoth("Stop the Alert: "); 
  printlnBoth(command); 
  //@TODO implement me
}
void processSetTimeCommand(String command){
  command.trim();
  printBoth("Set Time: "); 
  printlnBoth(command); 
  //@TODO implement me
}

void processBeepCommand(String command){
  command.trim();
  beep();
}

void processLedCommand(String command){
  //command.trim();
  printBoth("Set LED: "); 
  if( command.substring(0,2 ) == "on"){
    printlnBoth( " on " ); 
    digitalWrite(LED, HIGH);
  }
  else if(command.substring(0,3) == "off") {
    printlnBoth( " off " ); 
    digitalWrite(LED, LOW);  
  }

}


//do a beep
void beep(){
  analogWrite(BUZZER,128);
  delay(500);
  digitalWrite(BUZZER, LOW);

}

String getDayOfWeekName(int dayOfWeek){
  switch (dayOfWeek){
  case 0:
    return "Sunday";
  case 1:
    return "Monday";      
  case 2:
    return "Tuesday";
  case 3:
    return "Wednesday";            
  case 4:
    return "Thursday";
  case 5:
    return "Friday";     
  case 6:
    return "Friday";     
  default: 
    return "Unkown Day";
  }
}

void printBoth(String str){
#ifdef DEBUG
  BTSerial.print(str);
  Serial.print(str);
#endif
}
void printlnBoth(String str){
#ifdef DEBUG
  BTSerial.println(str);
  Serial.println(str);  
#endif
}
void printBothUsage(){
  printlnBoth("Alert Clock API by Michael Schmitt schmiddim@gmx.at");
  printlnBoth("==USAGE===");
  printlnBoth("dateformat: cmd alert del 074500-0100001");
  printlnBoth("al at 07:45 Monday + Saturday");
  printlnBoth("==Alerts==");
  printlnBoth("=Set an alert=");
  printlnBoth("cmd alert set D HH MM SS");
  printlnBoth("=Delete an alert=");
  printlnBoth("cmd alert del D HH MM SS");
  printlnBoth("=List alerts=");
  printlnBoth("cmd alert list");
  printlnBoth("==Stop Alert==");
  printlnBoth("cmd stop");
  printlnBoth("==Debug==");
  printlnBoth("cmd led on");
  printlnBoth("cmd led off");
  printlnBoth("cmd beep");
  printlnBoth("==@TODO==");
  printlnBoth("@brightness");
  printlnBoth("@settime");
}

void serialDisplayTime(int duration, int daysInFuture){
  DateTime now = RTC.now();    
  Serial.print(now.year(), DEC);

  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  Serial.print("current day of week: ");
  Serial.print(now.dayOfWeek(), DEC);
  Serial.print(", ");
  Serial.print(getDayOfWeekName(now.dayOfWeek()));
  Serial.println();

  Serial.print("since midnight 1/1/1970 = ");
  Serial.print(now.unixtime());
  Serial.print("s = ");
  Serial.print(now.unixtime() / 86400L);
  Serial.println("d");





  // calculate a date in future days and 30 seconds into the future
  DateTime future (now.unixtime() + daysInFuture * 86400L);

  Serial.print(" now + 1d + 30s: ");
  Serial.print(" now + ");
  Serial.print( daysInFuture );
  Serial.print( "days");

  Serial.print(future.year(), DEC);
  Serial.print('/');
  Serial.print(future.month(), DEC);
  Serial.print('/');
  Serial.print(future.day(), DEC);
  Serial.print(' ');
  Serial.print(future.hour(), DEC);
  Serial.print(':');
  Serial.print(future.minute(), DEC);
  Serial.print(':');
  Serial.print(future.second(), DEC);
  Serial.println();
  Serial.print("day of week: ");
  Serial.print(future.dayOfWeek(), DEC);
  Serial.print(", ");
  Serial.print(getDayOfWeekName(future.dayOfWeek()));

  Serial.println();


  BTSerial.print(now.year(), DEC);

  BTSerial.print('/');
  BTSerial.print(now.month(), DEC);
  BTSerial.print('/');
  BTSerial.print(now.day(), DEC);
  BTSerial.print(' ');
  BTSerial.print(now.hour(), DEC);
  BTSerial.print(':');
  BTSerial.print(now.minute(), DEC);
  BTSerial.print(':');
  BTSerial.print(now.second(), DEC);
  BTSerial.println();
  BTSerial.print("current day of week: ");
  BTSerial.print(now.dayOfWeek(), DEC);
  BTSerial.print(", ");
  BTSerial.print(getDayOfWeekName(now.dayOfWeek()));
  BTSerial.println();

  BTSerial.print("since midnight 1/1/1970 = ");
  BTSerial.print(now.unixtime());
  BTSerial.print("s = ");
  BTSerial.print(now.unixtime() / 86400L);
  BTSerial.println("d");

  // calculate a date in future days and 30 seconds into the future

  BTSerial.print(" now + 1d + 30s: ");
  BTSerial.print(" now + ");
  BTSerial.print( daysInFuture );
  BTSerial.print( "days");

  BTSerial.print(future.year(), DEC);
  BTSerial.print('/');
  BTSerial.print(future.month(), DEC);
  BTSerial.print('/');
  BTSerial.print(future.day(), DEC);
  BTSerial.print(' ');
  BTSerial.print(future.hour(), DEC);
  BTSerial.print(':');
  BTSerial.print(future.minute(), DEC);
  BTSerial.print(':');
  BTSerial.print(future.second(), DEC);
  BTSerial.println();
  BTSerial.print("day of week: ");
  BTSerial.print(future.dayOfWeek(), DEC);
  BTSerial.print(", ");
  BTSerial.print(getDayOfWeekName(future.dayOfWeek()));
  BTSerial.println();
  Serial.print("brightness: ");
  Serial.println(brightness, DEC);
  delay(duration);

}





