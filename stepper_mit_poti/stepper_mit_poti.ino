#include <AccelStepper.h>

/*
Einleitung
http://42bots.com/tutorials/28byj-48-stepper-motor-with-uln2003-driver-and-arduino-uno/
http://de.wikipedia.org/wiki/Schrittmotor
libaray http://www.airspayce.com/mikem/arduino/AccelStepper/
*/

#define HALFSTEP 8

// Motor pin definitions
#define motorPin1  3     // IN1 on the ULN2003 driver 1
#define motorPin2  4     // IN2 on the ULN2003 driver 1
#define motorPin3  5     // IN3 on the ULN2003 driver 1
#define motorPin4  6     // IN4 on the ULN2003 driver 1


// Poti
#define potiPin 0

//Button
#define PIN_BUTTON 8

#define PIN_LED 7

//Beeper
#define PIN_BEEPER 9

//Motor Constants
#define MAX_SPEED 1000.0
#define ACCELEREATION 100.0
#define SPEED 200
#define MOVE_TO 20000


// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);


int potiValue = 0;            //value from Poti
int buttonState = 0;         // variable for reading the pushbutton status

void beep(){
    analogWrite(PIN_BEEPER,128);
    delay(500);
    digitalWrite(PIN_BEEPER, LOW);
    delay(500);
}


void setup() {
    
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_LED, OUTPUT);     

  Serial.begin(9600);  // initialize serial communication at 9600 bits per second:
   
  stepper1.setMaxSpeed(MAX_SPEED);        //motor
  stepper1.setAcceleration(ACCELEREATION);//motor
  stepper1.setSpeed(SPEED);               //motor
  stepper1.moveTo(MOVE_TO);                //motor
  
  
  

}//--(end setup )---

void loop() {
  digitalWrite(PIN_LED, HIGH);
  
  
  //Change direction when the stepper reaches the target position
  if (stepper1.distanceToGo() == 0) {
    stepper1.moveTo(-stepper1.currentPosition());
  }
  stepper1.run();
    potiValue = analogRead(potiValue);
   buttonState = digitalRead(PIN_BUTTON);
  if(buttonState == HIGH){
    Serial.println("pofuckcufcucuti" + (String) potiValue); 
    beep();
  }else{
       digitalWrite( PIN_BEEPER, LOW);
 
  }
  
  
   

 //@todo: this  line are the performance issue in my setup
 //Serial.println("poti" + (String) potiValue); 

  
}
