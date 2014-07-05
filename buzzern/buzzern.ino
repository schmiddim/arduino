/***
Buzzer Vcc to 11
GND to GND
*/

// constants won't change. They're used here to 

// set pin numbers:
const int buttonPin = 8;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
const int buzzer = 11;       //the buzzer
const int potiPin= 0;



// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int potiValue = 0;            //value from Poti

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);     
}



void loop(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  potiValue = analogRead(potiValue);
  
  digitalWrite(ledPin, HIGH);
  delay(potiValue);
  digitalWrite(ledPin, LOW);
  delay(potiValue);
  
  Serial.println("jiji" + (String) potiValue); 
  
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
    beep();
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
    
    digitalWrite( buzzer, LOW);
  }
}

void beep(){
    analogWrite(buzzer,128);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);
}

