// MultiStepper.pde
// -*- mode: C++ -*-
// Use MultiStepper class to manage multiple steppers and make them all move to 
// the same position at the same time for linear 2d (or 3d) motion.

#include <AccelStepper.h>
#include <MultiStepper.h>

// EG X-Y position bed driven by 2 steppers
// Alas its not possible to build an array of these with different pins for each :-(
AccelStepper stepper1(1,6,7);
AccelStepper stepper2(1,9,8);

// Up to 10 steppers can be handled as a group by MultiStepper
MultiStepper steppers;

void setup() {
  Serial.begin(9600);

  // Configure each stepper
  stepper1.setMaxSpeed(200);
  stepper1.setAcceleration(100.0);
  stepper2.setMaxSpeed(400);
  stepper2.setAcceleration(100.0);

  // Then give them to MultiStepper to manage
  steppers.addStepper(stepper1);
  steppers.addStepper(stepper2);

  long positions[2]; // Array of desired stepper positions

positions[0] = 1000;
  positions[1] = -5000;
  steppers.moveTo(positions);
  steppers.runSpeedToPosition(); // Blocks until all are in position
  delay(1000);
  
  positions[0] = -0;
  positions[1] = 0;
  steppers.moveTo(positions);
  steppers.runSpeedToPosition(); // Blocks until all are in position
  delay(1000);
}

void loop() {
  
  
  
}
