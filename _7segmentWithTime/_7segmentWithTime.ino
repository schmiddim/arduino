#include <Charliplexing.h>
#include <led7Segment.h>
#include <Time.h>  
#include <EEPROM.h>

/*
Get current germany timestap:
date -d +2hours +T%s > /dev/ttyACM0 

*/
//---------------- time stuff ----------------------------

#define BRIGHTNESS_HEADER "B"  //Header tag for serial brightness message
#define TIME_HEADER  "T"   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 



const unsigned long DEFAULT_TIME = 1357041600; // defaulttime


int currentHour=0;
int currentMinute= 0;
int brightness=7;
int cmdBrightness=-1;

//This function will write a 4 byte (32bit) long to the eeprom at
//the specified address to adress + 3.
void EEPROMWritelong(int address, long value) {
      //Decomposition from a long to 4 bytes by using bitshift.
      //One = Most significant -> Four = Least significant byte
      byte four = (value & 0xFF);
      byte three = ((value >> 8) & 0xFF);
      byte two = ((value >> 16) & 0xFF);
      byte one = ((value >> 24) & 0xFF);

      //Write the 4 bytes into the eeprom memory.
      EEPROM.write(address, four);
      EEPROM.write(address + 1, three);
      EEPROM.write(address + 2, two);
      EEPROM.write(address + 3, one);
}
long EEPROMReadlong(long address) {
      //Read the 4 bytes from the eeprom memory.
      long four = EEPROM.read(address);
      long three = EEPROM.read(address + 1);
      long two = EEPROM.read(address + 2);
      long one = EEPROM.read(address + 3);

      //Return the recomposed long by using bitshift.
      return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}



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
  Serial.print(" brightness: ");
  Serial.print(brightness);
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
  unsigned int pcBrightness;
   if(Serial.find("B")) {
     
        pcBrightness = Serial.parseInt();
    	Serial.print("CMD: Set Brightness ");
	Serial.print(pcBrightness);   
	Serial.println();   
        if(pcBrightness >=0 && pcBrightness <8){
           cmdBrightness= pcBrightness; 
        }
                               
  
    }else{
      Serial.print("No valid Command found"); 
      Serial.println();   
    }
    //@todo Serial.find kills the String
   if(Serial.find(TIME_HEADER)) {
     
	pctime = Serial.parseInt();
	if( pctime >= DEFAULT_TIME) { // check the integer is a valid time (greater than Jan 1 2013)
		Serial.print("CMD: Set Time to ");
		Serial.print(pctime);   
		Serial.println();   
		setTime(pctime); // Sync Arduino clock to the time received on the serial port
		EEPROMWritelong(0, pctime); //Write timestamp to EEPROM
        }else{
               Serial.print("Crappy CMD"); 
        }
   }
  
  
  
}

time_t requestSync()
{
  Serial.write(TIME_REQUEST);  
  return 0; // the time will be sent later in response to serial mesg
}


void setup(){
  //LedSign::Init();
  LedSign::Init( GRAYSCALE);
  
  //set time by EEPROM
  unsigned long eePromTime ;
  eePromTime = EEPROMReadlong(0);    //Red initial time from EEPROM
  if( eePromTime >= DEFAULT_TIME) { // check the integer is a valid time (greater than Jan 1 2013)
       setTime(eePromTime); // Sync Arduino clock to the time received on the serial port
     
  }
  
  Serial.begin(9600);
  while (!Serial) ; // Needed for Leonardo only
  pinMode(13, OUTPUT);
  setSyncProvider( requestSync);  //set function to call when sync required
  Serial.println("Waiting for sync message");

}



void loop() {
  
  if (Serial.available()) {
    processSyncMessage();
  }
  if (timeStatus()!= timeNotSet) {
    digitalClockDisplay();  
  }


 // delay(1000);
  if(cmdBrightness== -1){
    if(hour() >= 23){
     brightness = 1; 
      
    }else if (hour() >=0 && hour() <7){
       brightness=1; 
    }else{
      
    }
  } else {
     //There's a command to override brightness
    brightness= cmdBrightness; 
    
  }

  
     showTime(hour(),minute(), brightness);  
     //@todo position as param
     //displayProgress(10);
     if(currentHour != hour() || currentMinute != minute()){         
         currentHour = hour();
         currentMinute= minute();         
         LedSign::Clear();
     }






}
