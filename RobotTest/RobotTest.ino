
#include "Robot.h"

Motion motion;

void setup() {
  Serial.begin(9600);
  motion.wait();
  motion.calibrate();
  motion.moveForward(50, 50, 150);
  // motion.moveForward(102, 100, 150);
  // motion.moveBackward(100, 100, 200);
  // motion.turnRight();
  // motion.turnLeft();
  // motion.stop();

  // int arr1[] = {1, 2, 50, 50, 0, 0};
  // int arr2[] = {1, 2};
  // motion.startRobot(arr1, 6);
  // motion.startRobot(arr2, 2);
}

void loop() {
} 