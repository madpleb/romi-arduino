// Class with all the Raspberry Pi functionality but moved to the Arduino

#include "Robot.h"
// #include <Vector.h> 

float readSpeed = 0.001;
float distFact = 6767; // conversion factor, cm traveled to encoder counts
const int lPin = 9;  // left motor speed
const int rPin = 10;  // right motor speed
const int freq = 1000; 


float convertAngle(float angle) {
  return (angle * 8.75/245 * 90/255);
}

void adjust(bool flip = false) { // set flip to true to adjust when robot is backwards
  float x, y, z;
  int MIN, MAX;
  if (!flip) {
     MIN = 50; 
     MAX = 120;
  }
  else {
     MIN = -120;
     MAX = -50;
  }

  IMU.readGyroscope(x, y, z);
  angleSum += convertAngle(z - z0) * readSpeed;

  if (abs(angleSum) > 2) {
    if (angleSum > 0) {
      currentLeft = min(MAX, max(currentLeft + 2, MIN));
      currentRight = min(MAX, max(currentLeft - 2, MIN));
      motors.setSpeeds(currentLeft, currentRight);
    }
    else {
      currentLeft = min(MAX, max(currentLeft - 2, MIN));
      currentRight = min(MAX, max(currentLeft + 2, MIN));
      motors.setSpeeds(currentLeft, currentRight);
    }
  }

  delay(readSpeed * 1000);

}

void moveForward(int ls, int rs, int dist) { // left speed, right speed, distance
  float encoderDist;
  startingLeft = currentLeft = ls;
  startingRight = currentRight = rs; 
  angleSum = 0; // reset angle sum 

  motors.setSpeeds(ls, rs);
  while (encoderDist <= distFact * dist) {
    lEncoder = pulseIn(lPin, HIGH);
    rEncoder = pulseIn(rPin, HIGH);
    encoderDist += (lEncoder + rEncoder)/2;
    adjust();
  }
  motors.setSpeeds(0, 0);
}

void moveBackward(int ls, int rs, int dist) {
  float encoderDist;
  startingLeft = currentLeft = -ls;
  startingRight = currentRight = -rs; 
  angleSum = 0;

  motors.setSpeeds(-ls, -rs);
  while (encoderDist <= distFact * dist) {
    lEncoder = pulseIn(lPin, HIGH);
    rEncoder = pulseIn(rPin, HIGH);
    encoderDist += (lEncoder + rEncoder)/2;
    adjust(true);
  }
  motors.setSpeeds(0, 0);
}

void turnLeft() {
  float x, y, z;
        angleSum = 0;
        motors.setSpeeds(64, 0);
        while (true)
        {
          IMU.readGyroscope(x, y, z);
            angleSum += (convertAngle(z- z0)) * freq; 
            if (angleSum <= -87)
            {
                motors.setSpeeds(0,0);
                break;
            }
            delay(freq);
        }
}

void turnRight() {
        float x, y, z;
        angleSum = 0;
        motors.setSpeeds(64, 0);
        while (true)
        {
          IMU.readGyroscope(x, y, z);
            angleSum += (convertAngle(z- z0)) * freq; 
            if (angleSum <= -87)
            {
                motors.setSpeeds(0,0);
                break;
            }
            delay(freq);
        }
}

void stop() {
  startingLeft = currentLeft = 0;
  startingRight = currentRight = 0; 
  angleSum = 0;

  motors.setSpeeds(0, 0);
}

void startRobot(int arr[]) {
  int size = sizeof(arr) / sizeof(arr[0]);
  for (int i = 0; i < size; i++) {
    int value = arr[i];
    if (value == 0) 
      stop();
    else if (value == 25)
      moveForward(77, 75, 25);
    else if (value == 50)
      moveForward(77, 75, 50);
    else if (value == 1)
      turnLeft();
    else if (value == 2)
      turnRight();

    delay(freq);
  }

}

void calibrate(int freq) {
  float x, y, z;
  float sum = 0; 
  for (int i = 0; i < freq; i++) {
    IMU.readGyroscope(x, y, z);
    sum += z;
  }
  z0 = sum/freq; 
  delay(1);
}


