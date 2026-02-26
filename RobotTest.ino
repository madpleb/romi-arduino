
#include "Robot.h"

Motion motion;

void setup() {
  Serial.begin(9600);
  motion.wait();
  motion.calibrate();
  motion.moveForward(100, 100, 50);
  // motion.moveBackward(100, 100, 1000);
  // motion.turnRight();
  // motion.turnLeft();
  // motion.stop();

  // int arr[] = {1, 2, 25, 50, 0, 0};
  // int arr2[] = {2, 2, 2, 2};
  // motion.startRobot(arr2, 4);
}

void loop() {
}