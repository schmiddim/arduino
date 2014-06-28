/*

  Example for Charliplexing library

  

  Alex Wenger <a.wenger@gmx.de> http://arduinobuch.wordpress.com/



  History:

  	30/Dez/09 - V0.0 wrote the first version at 26C3/Berlin

 * Messages consist of the letter T followed by ten digit time (as seconds since Jan 1 1970)
 * you can send the text on the next line using Serial Monitor to set the clock to noon Jan 1 2013
 T1357041600  
 *
 * A Processing example sketch to automatically send the messages is inclided in the download
 * On Linux, you can use "date +T%s > /dev/ttyACM0" (UTC time zone)
@see time example
*/
//---------------- time stuff ----------------------------
#include <Time.h>  

#define TIME_HEADER  "T"   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 


void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
  

}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}


void processSyncMessage() {
  unsigned long pctime;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     if( pctime >= DEFAULT_TIME) { // check the integer is a valid time (greater than Jan 1 2013)
       setTime(pctime); // Sync Arduino clock to the time received on the serial port
     }
  }
}

time_t requestSync()
{
  Serial.write(TIME_REQUEST);  
  return 0; // the time will be sent later in response to serial mesg
}

//---------------- time stuff ----------------------------
#include "Charliplexing.h"


struct point {

  uint8_t xp;        // Point Position in X direction (multplied by 16)

  uint8_t x_speed;   // Speed

  uint8_t flag;  

} points[9];






void setup(){
  //LedSign::Init();
  LedSign::Init( GRAYSCALE);
  
  Serial.begin(9600);
  while (!Serial) ; // Needed for Leonardo only
  pinMode(13, OUTPUT);
  setSyncProvider( requestSync);  //set function to call when sync required
  Serial.println("Waiting for sync message");

}

void displayA(int posX, int posY, int brightness ){
  LedSign::Set(posY,posX, brightness);   
  LedSign::Set(posY,posX-1, brightness);   
  LedSign::Set(posY,posX-2 ,brightness);
  LedSign::Set(posY,posX-3, brightness);
}
void displayB(int posX, int posY, int brightness ){
  
  LedSign::Set(posY,posX-3,  brightness);    
  LedSign::Set(posY+1,posX-3, brightness);   
  LedSign::Set(posY+2,posX-3,  brightness);    
}
void displayC(int posX, int posY, int brightness ){
  
  LedSign::Set(posY+3,posX-3, brightness);
  LedSign::Set(posY+4,posX-3, brightness);  
  LedSign::Set(posY+5,posX-3, brightness);  
}
void displayD(int posX, int posY, int brightness ){
    //d
  LedSign::Set(posY+5,posX, brightness);   
  LedSign::Set(posY+5,posX-1, brightness);   
  LedSign::Set(posY+5,posX-2, brightness);
  LedSign::Set(posY+5,posX-3, brightness);
}
void displayE(int posX, int posY, int brightness ){
  
  LedSign::Set(posY+3,posX, brightness);
  LedSign::Set(posY+4,posX, brightness);  
}
void displayF(int posX, int posY, int brightness ){
  LedSign::Set(posY,posX, brightness);   
  LedSign::Set(posY+1,posX, brightness);   
  LedSign::Set(posY+2,posX, brightness);    
}
void displayG(int posX, int posY, int brightness ){
    //g
  LedSign::Set(posY+3,posX, brightness);   
  LedSign::Set(posY+3,posX-1, brightness);   
  LedSign::Set(posY+3,posX-2, brightness);
  LedSign::Set(posY+3,posX-3, brightness);  
}

void displayDigit(int posX, int posY, int number ){
  posX*=-1;
  posX+=8;
  
  int brightness=7;
  
  switch(number){
    case 0:
    displayA(posX, posY, brightness);
    displayC(posX, posY, brightness);
    displayD(posX, posY, brightness);
    displayE(posX, posY, brightness);
    displayF(posX, posY, brightness);
    

      break;
    case 1:
    displayB(posX, posY, brightness);
    displayC(posX, posY, brightness);
  
      break; 
    case 2:
      displayA(posX, posY, brightness);
      displayB(posX, posY, brightness);
      displayD(posX, posY, brightness);
      displayE(posX, posY, brightness);     
      displayG(posX ,posY, brightness);     
     
      break; 
    case 3:
      displayA(posX, posY, brightness);
      displayB(posX, posY, brightness);
      displayC(posX, posY, brightness);
      displayD(posX, posY, brightness);
      displayG(posX ,posY, brightness);        
      break; 
    case 4:
      displayB(posX, posY, brightness);
      displayC(posX, posY, brightness);
      displayF(posX, posY, brightness);
      displayG(posX ,posY, brightness);    
      break;     
    case 5:
      displayA(posX, posY, brightness);
      displayC(posX, posY, brightness);
      displayD(posX, posY, brightness);
      displayF(posX, posY, brightness);
      displayG(posX ,posY, brightness);        
      break; 
    case 6:
      displayA(posX, posY, brightness);
      displayC(posX, posY, brightness);
      displayD(posX, posY, brightness);
      displayE(posX, posY, brightness);
      displayF(posX, posY, brightness);
      displayG(posX ,posY, brightness);        
      break; 
    case 7:
      displayA(posX, posY, brightness);
      displayB(posX, posY, brightness);
      displayC(posX, posY, brightness);     
      break; 
    case 8:
      displayA(posX, posY, brightness);
      displayB(posX, posY, brightness);
      displayC(posX, posY, brightness);
      displayD(posX, posY, brightness);
      displayE(posX, posY, brightness);
      displayF(posX, posY, brightness);
      displayG(posX ,posY, brightness);    
      break;        
    case 9:
      displayA(posX, posY, brightness);
      displayB(posX, posY, brightness);
      displayC(posX, posY, brightness);
      displayD(posX, posY, brightness);
      displayF(posX, posY, brightness);
      displayG(posX ,posY, brightness);    
      break;        
    
  }

}
void clear(){
    for(uint8_t y = 0; y < 9; y++){

    for(uint8_t x = 0; x < 14; x++)

    {

      LedSign::Set(x,y,0);    

    }

  
  }
  
  
}



void displayNumber(int number){
   if(number>9999){
       return;  
   }
      
   int digits[4] ={0,0,0,0};
   int counter=3;

   while(number>0) {
      int digit = number %10;
      

      digits[counter] = digit; 
        

      counter--;
      number /= 10;
        
   }   
     //   clear();
   // if(digits[0] >0)
    displayDigit(0,0, digits[0]);  
   // if(digits[1] >0)
      displayDigit(5,0, digits[1]);
   //  if(digits[2] >0)  
      displayDigit(0,8, digits[2]);
   //  if(digits[3] >0)
    displayDigit(5,8, digits[3]);     
            
  
}


void countDown(int from, int delayTime){
    for(int y = from; y >=0; y--){
      clear();
      if(y!=0){
      
         displayNumber(y);
        delay(delayTime); 
      }else{
        clear();
        displayNumber(0000);
        delay(delayTime); 
        clear();
        delay(delayTime);   
        displayNumber(0000);
        delay(delayTime); 
        clear();
        delay(delayTime);   
        displayNumber(0000);
        delay(delayTime); 
      }
      
    }  
  
}

void showTime(int hour, int minute){
  
  if(hour>24 || minute > 60){
    displayDigit(0,0, 0);
    displayDigit(5,0, 0);  
    displayDigit(0,8, 0);
    displayDigit(5,8, 0);
    return;
  }
  
  int digitsHour[2] = {0,0};
  int digitsMinute[2] ={0,0};
  
  int counter = 1;
  while( hour > 0){
     int digit = hour%10;
    digitsHour[counter] = digit;
    counter--;
    hour/=10;  
  }
  
  counter = 1;
  while(minute > 0){
     int digit = minute%10;
     digitsMinute[counter] = digit;
     counter--;
     minute/=10; 
    
  }
  
  
  if(digitsHour[0] !=0)
    displayDigit(0,0, digitsHour[0]);
  displayDigit(5,0, digitsHour[1]);  
  displayDigit(0,8, digitsMinute[0]);
  displayDigit(5,8, digitsMinute[1]);
}

int currentHour=0;
int currentMinute= 0;
void loop() {
  
  if (Serial.available()) {
    processSyncMessage();
  }
  if (timeStatus()!= timeNotSet) {
    digitalClockDisplay();  
  }
  if (timeStatus() == timeSet) {
    digitalWrite(13, HIGH); // LED on if synced
  } else {
    digitalWrite(13, LOW);  // LED off if needs refresh
  }
  delay(1000);
   //9 x 14

 // showTime(3,20);
 
// showTime(9,20);

     showTime(hour(),minute());  
     if(currentHour != hour() || currentMinute != minute()){
       
         currentHour = hour();
         currentMinute= minute();
         
         clear();
     }
 // displayNumber(333);
  
 // countDown(100, 500);
  
//displayDigit(0,0, 3);
/*
  displayDigit(5,0, 6);
    
  displayDigit(0,8, 3);

  displayDigit(5,8, 0);
  
  
*/




}
