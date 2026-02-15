
#include "Robot.h"

Motion motion;

void setup() {

  Serial.begin(9600);
  pinMode(L_PIN, OUTPUT);
  pinMode(R_PIN, OUTPUT);
  // Play startup sound.
  motion.calibrate(); 

}

void loop() {
  int arr[] {50, 25, 2, 2, 0};
  int size = sizeof(arr) / sizeof(arr[0]);

  motion.startRobot(arr, size);
}
