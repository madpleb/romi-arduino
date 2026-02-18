#include "Robot.h"

Motion motion;

void setup() {
  Serial.begin(9600);
  motion.calibrate();
}

float sum = 0;

void loop() {
  float x, y, z;
  IMU.readGyroscope(x, y, z);
  sum += (z - motion.getz0()) * 0.001;
  Serial.println(sum);
  delay(1);
}
