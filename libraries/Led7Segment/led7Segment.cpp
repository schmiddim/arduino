#include "Arduino.h"
#include "Charliplexing.h"

#define BRIGHTNESS_MAX 7

void displayProgress(int percent){
	int brightness=1;
//	displayDigit(0,0,8,4);  
	int posX=0;
	int posY=0;

  posX*=-1;
  posX+=8;
	LedSign::Set(posY ,posX  , brightness+4);   
	LedSign::Set(posY ,posX-1, brightness+4);   
	LedSign::Set(posY ,posX-2, brightness+4);
	LedSign::Set(posY ,posX-3, brightness+4); 

	LedSign::Set(posY+1,posX  , brightness+4);   
	LedSign::Set(posY+1,posX-1, brightness+4);   
	LedSign::Set(posY+1,posX-2, brightness+4);
	LedSign::Set(posY+1,posX-3, brightness+4); 

	LedSign::Set(posY+2,posX  , brightness+3);   
	LedSign::Set(posY+2,posX-1, brightness+3);   
	LedSign::Set(posY+2,posX-2, brightness+3);
	LedSign::Set(posY+2,posX-3, brightness+3);  	

	LedSign::Set(posY+3,posX  , brightness+2);   
	LedSign::Set(posY+3,posX-1, brightness+2);   
	LedSign::Set(posY+3,posX-2, brightness+2);
	LedSign::Set(posY+3,posX-3, brightness+2);  	

	LedSign::Set(posY+4,posX  , brightness+1);   
	LedSign::Set(posY+4,posX-1, brightness+1);   
	LedSign::Set(posY+4,posX-2, brightness+1);
	LedSign::Set(posY+4,posX-3, brightness+1); 

	LedSign::Set(posY+5,posX  , brightness);   
	LedSign::Set(posY+5,posX-1, brightness);   
	LedSign::Set(posY+5,posX-2, brightness);
	LedSign::Set(posY+5,posX-3, brightness);  	 	
	
}

void displayA(int posX, int posY, int brightness ){
  	if(brightness > BRIGHTNESS_MAX){
		brightness=BRIGHTNESS_MAX;
	}
	LedSign::Set(posY,posX, brightness);   
	LedSign::Set(posY,posX-1, brightness);   
	LedSign::Set(posY,posX-2 ,brightness);
	LedSign::Set(posY,posX-3, brightness);
}
void displayB(int posX, int posY, int brightness ){
  	if(brightness > BRIGHTNESS_MAX){
		brightness=BRIGHTNESS_MAX;
	}
	LedSign::Set(posY,posX-3,  brightness);    
	LedSign::Set(posY+1,posX-3, brightness);   
	LedSign::Set(posY+2,posX-3,  brightness);    
}
void displayC(int posX, int posY, int brightness ){  
  	if(brightness > BRIGHTNESS_MAX){
		brightness=BRIGHTNESS_MAX;
	}
	LedSign::Set(posY+3,posX-3, brightness);
	LedSign::Set(posY+4,posX-3, brightness);  
	LedSign::Set(posY+5,posX-3, brightness);  
}
void displayD(int posX, int posY, int brightness ){
  	if(brightness > BRIGHTNESS_MAX){
		brightness=BRIGHTNESS_MAX;
	}
	LedSign::Set(posY+5,posX, brightness);   
	LedSign::Set(posY+5,posX-1, brightness);   
	LedSign::Set(posY+5,posX-2, brightness);
	LedSign::Set(posY+5,posX-3, brightness);
}
void displayE(int posX, int posY, int brightness ){ 
  	if(brightness > BRIGHTNESS_MAX){
		brightness=BRIGHTNESS_MAX;
	}
	LedSign::Set(posY+3,posX, brightness);
	LedSign::Set(posY+4,posX, brightness);  
}
void displayF(int posX, int posY, int brightness ){
  	if(brightness > BRIGHTNESS_MAX){
		brightness=BRIGHTNESS_MAX;
	}
	LedSign::Set(posY,posX, brightness);   
	LedSign::Set(posY+1,posX, brightness);   
	LedSign::Set(posY+2,posX, brightness);    
}
void displayG(int posX, int posY, int brightness ){
  	if(brightness > BRIGHTNESS_MAX){
		brightness=BRIGHTNESS_MAX;
	}
	LedSign::Set(posY+3,posX, brightness);   
	LedSign::Set(posY+3,posX-1, brightness);   
	LedSign::Set(posY+3,posX-2, brightness);
	LedSign::Set(posY+3,posX-3, brightness);  
}

void displayDigit(int posX, int posY, int number, int brightness ){
  posX*=-1;
  posX+=8;
    
  switch(number){
	case 0:
		displayA(posX, posY, brightness);
		displayB(posX, posY, brightness);
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

//Display a single number
void displayNumber(int number, int brightness){
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
     //   LedSign::Clear();
   // if(digits[0] >0)
    displayDigit(0,0, digits[0],brightness);  
   // if(digits[1] >0)
      displayDigit(5,0, digits[1],brightness);
   //  if(digits[2] >0)  
      displayDigit(0,8, digits[2],brightness);
   //  if(digits[3] >0)
    displayDigit(5,8, digits[3],brightness);     
            
  
}


//Countdown from a startnumber
void countDown(int from, int delayTime){
	int brightness=2;

    for(int y = from; y >=0; y--){
      LedSign::Clear();
      if(y!=0){     
         displayNumber(y, brightness);
        delay(delayTime); 
      }else{
        LedSign::Clear();
        displayNumber(0000, brightness);
        delay(delayTime); 
        LedSign::Clear();
        delay(delayTime);   
        displayNumber(0000, brightness);
        delay(delayTime); 
        LedSign::Clear();
        delay(delayTime);   
        displayNumber(0000, brightness);
        delay(delayTime); 
      }      
    }  
}

void showTime(int hour, int minute, int brightness){
  
  if(hour>24 || minute > 60){
    displayDigit(0,0, 0, brightness);
    displayDigit(5,0, 0, brightness);  
    displayDigit(0,8, 0, brightness);
    displayDigit(5,8, 0, brightness);
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

	if(digitsHour[0] !=0){
		displayDigit(0,0, digitsHour[0], brightness);
	}
	displayDigit(5,0, digitsHour[1], brightness);  
	displayDigit(0,8, digitsMinute[0], brightness);
	displayDigit(5,8, digitsMinute[1], brightness);
}

