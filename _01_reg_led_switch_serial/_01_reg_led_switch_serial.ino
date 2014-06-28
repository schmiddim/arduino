/*
  DigitalReadSerial
 Reads a digital input on pin 2, prints the result to the serial monitor 
 
 This example code is in the public domain.
 */

// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 2;

//digial pin 13 onBoard LED
int onBoardLed=13;

int ledBlue=10;
int ledRed=11;
int ledGreen=12;

int ctr=0;
int brightness=0;
int fadeAmount=5;


volatile int enabled=HIGH;


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  pinMode(onBoardLed, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  
  attachInterrupt(0, turnOff, HIGH);
}

void turnOff(){
    digitalWrite(onBoardLed,HIGH);
    ctr=0;
    turnLightOff(ledRed);
    turnLightOff(ledGreen);
    turnLightOff(ledBlue);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(pushButton);
 
   if(buttonState){
     digitalWrite(onBoardLed,buttonState);
    /*  brightness=0; 
      ctr=0;
      Serial.println("REsET");*/
   }
   if(enabled){
      
   if(ctr /255==0){
    //Red
     turnLightOn(ledRed);
     turnLightOff(ledGreen);
     turnLightOff(ledBlue);
    
   }else if(ctr/255==1){
     //Green
     turnLightOff(ledRed);
     turnLightOn(ledGreen);
     turnLightOff(ledBlue);
      
   }else if (ctr / 255==2){
     //Blue
     turnLightOff(ledRed);
     turnLightOff(ledGreen);
     turnLightOn(ledBlue);

   }else{
     ctr=0;
     Serial.println("ZERO");
   }
   
   ctr+=fadeAmount;
   }
   
  // analogWrite(ledRed, brightness);  
   
  
  delay(30);        // delay in between reads for stability
}
void turnLightOn(int pin){
      digitalWrite(pin, HIGH);
}
void turnLightOff(int pin){
      digitalWrite(pin, LOW);
}

