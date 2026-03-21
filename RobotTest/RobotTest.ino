
#include "Robot.h"

Motion motion;

void setup() {
  Serial.begin(9600);
  motion.wait();
  motion.calibrate();
  motion.setStartSpeeds(100, 100);
  // motion.moveForward(102, 100, 150);
  // motion.moveBackward(100, 100, 200);
  // motion.turnRight();
  // motion.turnLeft();
  // motion.stop();

  // int arr1[] = {1, 2, 50, 50, 0, 0};
  int arr2[] = {125, 2, 50, 1, 50, 2, 50, 0};
  // motion.startRobot(arr1, 6);
  motion.startRobot(arr2, 8);
}

void loop() {
} 