/*

  Example for Charliplexing library

  

  Alex Wenger <a.wenger@gmx.de> http://arduinobuch.wordpress.com/



  History:

  	30/Dez/09 - V0.0 wrote the first version at 26C3/Berlin



*/

#include "Charliplexing.h"



struct point {

  uint8_t xp;        // Point Position in X direction (multplied by 16)

  uint8_t x_speed;   // Speed

  uint8_t flag;  

} points[9];



void setup(){
  LedSign::Init();

}

void displayA(int posX, int posY ){
  LedSign::Set(posY,posX);   
  LedSign::Set(posY,posX-1);   
  LedSign::Set(posY,posX-2);
  LedSign::Set(posY,posX-3);
}
void displayB(int posX, int posY ){
  
  LedSign::Set(posY,posX-3);    
  LedSign::Set(posY+1,posX-3);   
  LedSign::Set(posY+2,posX-3);    
}
void displayC(int posX, int posY ){
  
  LedSign::Set(posY+3,posX-3);
  LedSign::Set(posY+4,posX-3);  
  LedSign::Set(posY+5,posX-3);  
}
void displayD(int posX, int posY ){
    //d
  LedSign::Set(posY+5,posX);   
  LedSign::Set(posY+5,posX-1);   
  LedSign::Set(posY+5,posX-2);
  LedSign::Set(posY+5,posX-3);
}
void displayE(int posX, int posY ){
  
  LedSign::Set(posY+3,posX);
  LedSign::Set(posY+4,posX);  
}
void displayF(int posX, int posY ){
  LedSign::Set(posY,posX);   
  LedSign::Set(posY+1,posX);   
  LedSign::Set(posY+2,posX);    
}
void displayG(int posX, int posY ){
    //g
  LedSign::Set(posY+3,posX);   
  LedSign::Set(posY+3,posX-1);   
  LedSign::Set(posY+3,posX-2);
  LedSign::Set(posY+3,posX-3);  
}

void displayDigit(int posX, int posY, int number ){
  posX*=-1;
  posX+=8;
 
  switch(number){
    case 0:
    displayA(posX, posY);
    displayB(posX, posY);
    displayC(posX, posY);
    displayD(posX, posY);
    displayE(posX, posY);
    displayF(posX, posY);
    

      break;
    case 1:
    displayB(posX, posY);
    displayC(posX, posY);
  
      break; 
    case 2:
      displayA(posX, posY);
      displayB(posX, posY);
      displayD(posX, posY);
      displayE(posX, posY);
      displayG(posX ,posY);        
      break; 
    case 3:
      displayA(posX, posY);
      displayB(posX, posY);
      displayC(posX, posY);
      displayD(posX, posY);
      displayG(posX ,posY);        
      break; 
    case 4:
      displayB(posX, posY);
      displayC(posX, posY);
      displayF(posX, posY);
      displayG(posX ,posY);    
      break;     
    case 5:
      displayA(posX, posY);
      displayC(posX, posY);
      displayD(posX, posY);
      displayF(posX, posY);
      displayG(posX ,posY);        
      break; 
    case 6:
      displayA(posX, posY);
      displayC(posX, posY);
      displayD(posX, posY);
      displayE(posX, posY);
      displayF(posX, posY);
      displayG(posX ,posY);        
      break; 
    case 7:
      displayA(posX, posY);
      displayB(posX, posY);
      displayC(posX, posY);     
      break; 
    case 8:
      displayA(posX, posY);
      displayB(posX, posY);
      displayC(posX, posY);
      displayD(posX, posY);
      displayE(posX, posY);
      displayF(posX, posY);
      displayG(posX ,posY);    
      break;        
    case 9:
      displayA(posX, posY);
      displayB(posX, posY);
      displayC(posX, posY);
      displayD(posX, posY);
      displayF(posX, posY);
      displayG(posX ,posY);    
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
void loop()                     // run over and over again

{
   //9 x 14

 // showTime(3,20);
 
 showTime(9,20);

 
 // displayNumber(333);
  
 // countDown(100, 500);
  
//displayDigit(0,0, 3);
/*
  displayDigit(5,0, 6);
    
  displayDigit(0,8, 3);

  displayDigit(5,8, 0);
  
  
*/




}
