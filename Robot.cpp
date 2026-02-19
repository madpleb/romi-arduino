// Class with all the Raspberry Pi functionality but moved to the Arduino

#include "Robot.h"
// #include <Vector.h> 

float Motion::convertAngle(float angle) {
  return (angle * 90/32);
}

float Motion::getz0() {
  return z0;
}

void Motion::wait() {
  while (true) {
    if (buttonA.isPressed()) {
      ledRed(1);
      ledGreen(1);
      break;
    }
    delay(1);
  }
}

void Motion::adjust(bool flip = false) { // set flip to true to adjust when robot is backwards
  float x, y, z;
  int MIN, MAX, ADJUST_FACTOR;
  if (!flip) {
     MIN = 50; 
     MAX = 120;
     ADJUST_FACTOR = 1;
  }
  else {
     MIN = -120;
     MAX = -50;
     ADJUST_FACTOR = 1;
  }

  IMU.readGyroscope(x, y, z);
  angleSum += convertAngle(z - z0) * READ_SPEED;
  float now = millis()/1000;

  if (now - lastAdjustTime > 0.01) {
    if (abs(angleSum) > 2) {
      if (angleSum > 0) {
        currentLeft = min(MAX, max(currentLeft + ADJUST_FACTOR, MIN));
        currentRight = min(MAX, max(currentRight - ADJUST_FACTOR, MIN));
        motors.setSpeeds(currentLeft, currentRight);
        Serial.println(currentLeft); 
        Serial.print('\t');
        Serial.print(currentRight);
      }
      else {
        currentLeft = min(MAX, max(currentLeft - ADJUST_FACTOR, MIN));
        currentRight = min(MAX, max(currentRight + ADJUST_FACTOR, MIN));
        motors.setSpeeds(currentLeft, currentRight);
        Serial.println(currentLeft); 
        Serial.print('\t');
        Serial.println(currentRight);
      }
    }
    lastAdjustTime = now;
  }
  delay(READ_SPEED * 1000);
}

void Motion::moveForward(int ls, int rs, int dist) { // left speed, right speed, distance
  float encoderCount = 0;
  startingLeft = currentLeft = ls;
  startingRight = currentRight = rs; 
  angleSum = 0; // reset angle sum 

  motors.setSpeeds(ls, rs);
  while (encoderCount <= distFact * dist) {
    // lEncoder = pulseIn(L_PIN, HIGH);
    // rEncoder = pulseIn(R_PIN, HIGH);
    lEncoder = encoders.getCountsAndResetLeft();
    rEncoder = encoders.getCountsAndResetRight();
    encoderCount += (lEncoder + rEncoder)/2;
    adjust();
  }
  motors.setSpeeds(0, 0);
}

void Motion::moveBackward(int ls, int rs, int dist) {
  float encoderCount = 0;
  startingLeft = currentLeft = -ls;
  startingRight = currentRight = -rs; 
  angleSum = 0;

  motors.setSpeeds(-ls, -rs);
  while (-encoderCount <= distFact * dist) {
    // lEncoder = pulseIn(L_PIN, HIGH);
    // rEncoder = pulseIn(R_PIN, HIGH);
    lEncoder = encoders.getCountsAndResetLeft();
    rEncoder = encoders.getCountsAndResetRight();
    encoderCount += (lEncoder + rEncoder)/2;
    adjust(true);
  }
  motors.setSpeeds(0, 0);
}

void Motion::turnLeft() {
  float x, y, z;
  motors.setSpeeds(0, 61);
  while (true)
  {
    IMU.readGyroscope(x, y, z);
    angleSum += (convertAngle(z - z0)) * READ_SPEED; 
    if (angleSum >= 105)
    {
      motors.setSpeeds(0,0);
      break;
    }
    delay(READ_SPEED * 1000);
  }
}

void Motion::turnRight() {
  float x, y, z;
  motors.setSpeeds(100, 0);
  while (true)
  {
    IMU.readGyroscope(x, y, z);
    angleSum += (convertAngle(z- z0)) * READ_SPEED; 
    if (angleSum <= -105)
    {
      motors.setSpeeds(0,0);
      break;
    }
    delay(READ_SPEED * 1000);
  }
}

void Motion::stop() {
  startingLeft = currentLeft = 0;
  startingRight = currentRight = 0; 
  angleSum = 0;

  motors.setSpeeds(0, 0);
}

void Motion::startRobot(int arr[], int size) {
  // int size = sizeof(arr) / sizeof(arr[0]);
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
    
    angleSum = 0;
    delay(1000); // delay after every action
  }

}

void Motion::calibrate() {
  float x, y, z;
  float sum = 0; 
  IMU.begin();
  for (int i = 0; i < FREQ; i++) {
    IMU.readGyroscope(x, y, z);
    sum += z;
    delay(READ_SPEED * 1000);
  }
  z0 = sum/FREQ; 
  delay(1000); // wait for gyro to stabilize (allegedly)
  ledRed(0);
  ledYellow(0);
  ledGreen(0);
}