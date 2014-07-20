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
 HC-05 TX --- Arduino Pin A0 (soft RX)
 HC-05 RX --- Arduino Pin A1 (soft TX)
 HC-05 Key (PIN 34) --- Arduino 5V
 */
// Date and time functions using a DS1307 RTC connected via I2C and Wire lib

#include <Wire.h>
#include <SPI.h>
#include <RTClib.h>
#include <RTC_DS1307.h>
#include <Charliplexing.h>
#include <led7Segment.h>
#include <SoftwareSerial.h>

RTC_DS1307 RTC;


int brightness=7;

int currentHour=0;
int currentMinute= 0;

//Bluetooth stuff
#define BT_RX A1
#define BT_TX A0

SoftwareSerial BTSerial(BT_RX, BT_TX); // RX | TX
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

#define BUZZER A3
#define LED A2

void setup () {

  pinMode(BUZZER, OUTPUT);    //Buzzere
  pinMode(LED, OUTPUT);    //led

  //led stuff 
  LedSign::Init( GRAYSCALE);

  //Bluetooth
  BTSerial.begin(9600);  // HC-05 default speed in AT command more
  BTSerial.println("Enter AT commands:");
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
  if(now.hour() >= 22){
    brightness = 1; 

  }
  else if (now.hour() >=0 && now.hour() <7){
    brightness=1; 
  }
  else{

  }
  showTime(now.hour(),now.minute(), brightness);  
  if(currentHour != now.hour() || currentMinute != now.minute()){         
    currentHour = now.hour();
    currentMinute= now.minute();         
    LedSign::Clear();
  }

  while (BTSerial.available()) {
    // get the new byte:
    char inChar = (char)BTSerial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      //  Serial.println(inputString);
      //  BTSerial.println(inputString);
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

  //test alarm
  if(now.hour() == 15 && now.minute() ==13 && now.second() == 0){
    beep();

    //   beep();


  }

  //only for debug purpose
  serialDisplayTime(3000, 5);    



}

//Handle commands here
//@todo wire up Communication Control here
void processCommand(String from, String command){
  if(command == "led on\n"){
    digitalWrite(LED, HIGH);
  }
  else if(command == "led off\n"){

    digitalWrite(LED, LOW);  
  }
  else if(command=="beep\n"){
    beep(); 

  }
  else if(command=="date\n"){
    serialDisplayTime(3000,  5);
  } 

  else if(command.substring(0) == "beep_d"){

  }
  else if(command=="beep"){
    beep(); 

  } 
  else {
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
  analogWrite(BUZZER,128);
  delay(500);
  digitalWrite(BUZZER, LOW);

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
  delay(duration);

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




