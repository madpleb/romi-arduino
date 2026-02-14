
#include "Robot.h"


void setup() {
  Serial.begin(9600);

  pinMode(lPin, OUTPUT);
  pinMode(rPin, OUTPUT);
  // Play startup sound.
  calibrate(freq);


}

void loop() {
  int arr[] {50, 25, 2, 2, 0};
  startRobot(arr);
}