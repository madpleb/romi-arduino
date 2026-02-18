
#include "Robot.h"

Motion motion;

void setup() {
  motion.calibrate();
  motion.moveForward(60, 60, 100);
  motion.stop();
}

void loop() {
}