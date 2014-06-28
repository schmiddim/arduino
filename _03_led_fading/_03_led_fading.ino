
int onBoardLed=13;  //digial pin 13 onBoard LED

int ledBlue=10;
int ledRed=11;
int ledGreen=12;


void setup(){
  pinMode(ledRed, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledGreen, OUTPUT);  
  
}

void loop(){
  int delayTime=30;

  fade(ledRed, delayTime); 
  fade(ledGreen, delayTime);
  fade(ledBlue, delayTime);
}


void fade(int ledPin, unsigned int delayTime){
    
     for(int fadeValue=0; fadeValue<=255; fadeValue+=5){
      analogWrite(ledPin, fadeValue);
      
      delay(delayTime);
} 
   
   for(int fadeValue=255; fadeValue>=0;fadeValue-=5){
       analogWrite(ledPin, fadeValue);
      
      delay(delayTime);
   }
}

void fadeIn(int ledPin, int delayTime){
      for(int fadeValue=0; fadeValue<=255; fadeValue+=5){
      analogWrite(ledPin, fadeValue);
      
      delay(delayTime);
    
   } 
  
}

void fadeOut(int ledPin, int delayTime){
    for(int fadeValue=255; fadeValue>=20;fadeValue-=5){
       analogWrite(ledPin, fadeValue);
      
      delay(delayTime);
   } 
  
}
