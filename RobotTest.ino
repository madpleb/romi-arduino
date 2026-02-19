
#include "Robot.h"

Motion motion;

void setup() {
  motion.wait();
  motion.calibrate();
  int arr[] = {1, 2, 25, 50, 0, 0};
  motion.startRobot(arr, 6);
  // motion.moveForward(100, 100, 1000);
  // motion.moveBackward(100, 100, 1000);
  // motion.turnRight();
  // motion.turnLeft();
  // motion.stop();
}

void loop() {
}