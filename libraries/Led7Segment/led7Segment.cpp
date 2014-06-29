#include "Arduino.h"
#include "Charliplexing.h"

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
  
  int brightness=2;
  
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
//Clear the screen
void clear(){
    for(uint8_t y = 0; y < 9; y++){
      for(uint8_t x = 0; x < 14; x++){
         LedSign::Set(x,y,0);    
      } 
  }
}

//Countdown from a startnumber
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

	if(digitsHour[0] !=0){
		displayDigit(0,0, digitsHour[0]);
	}
	displayDigit(5,0, digitsHour[1]);  
	displayDigit(0,8, digitsMinute[0]);
	displayDigit(5,8, digitsMinute[1]);
}

