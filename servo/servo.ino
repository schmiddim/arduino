#include <Servo.h>

//http://www.mariolukas.de/2011/08/arduino-servo-tutorial/
// Erzeugen eines Servo Objekts zur Servo Steuerung
Servo myservo;

// Variable zum Speichern der Position
int pos = 0;

// Initialisierung der Pins
void setup(){
   myservo.attach(9);
}
// Hauptprogramm
void loop(){
   for(pos = 0; pos < 180; pos++){
     myservo.write(pos);
     delay(30);
   }
}
