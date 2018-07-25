#include "AccelStepper.h" 

AccelStepper stepperX(1, 9, 8);

long Distance = 100000;
int move_finished = 1;
long initial_homing = 0;

int BUTTON_PIN = 2;

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  stepperX.setCurrentPosition(0);  // Set the current position as zero for now
  stepperX.setMaxSpeed(500.0);
  stepperX.setAcceleration(100.0); 

  stepperX.runToNewPosition(2500);
  stepperX.setCurrentPosition(0);
  stepperX.runToNewPosition(5000);
  stepperX.setCurrentPosition(0);
  stepperX.runToNewPosition(2500);
  stepperX.setCurrentPosition(0);
  stepperX.runToNewPosition(5000);
  stepperX.setCurrentPosition(0);
  

  //Serial.print("Stepper is Homing . . . . . . . . . . . ");
  
  
  
}

void loop() {
  /*while(initial_homing<Distance){
    stepperX.moveTo(initial_homing);  
    stepperX.run();
    initial_homing++;
  }*/
  
  
  
}
