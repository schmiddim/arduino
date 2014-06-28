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

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);


#define MAX_SPEED 1000.0
#define ACCELEREATION 100.0
#define SPEED 200
#define MOVE_TO 20000

void setup() {
  stepper1.setMaxSpeed(MAX_SPEED);
  stepper1.setAcceleration(ACCELEREATION);
  stepper1.setSpeed(SPEED);
  stepper1.moveTo(MOVE_TO);

}//--(end setup )---

void loop() {

  //Change direction when the stepper reaches the target position
  if (stepper1.distanceToGo() == 0) {
    stepper1.moveTo(-stepper1.currentPosition());
  }
  stepper1.run();
}
