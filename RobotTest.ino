// Class with all the Raspberry Pi functionality but moved to the Arduino
#include <Servo.h>
#include <AStar32U4.h>
#include <Arduino_LSM6DS3.h>
#include <stdio.h>

float readSpeed = 0.001;
int startingLeft, startingRight;
int currentLeft, currentRight; // current motor speeds

int lEncoder, rEncoder;
float distFact = 6767; // conversion factor, cm traveled to encoder counts
const int lPin = 9;  // left motor speed
const int rPin = 10;  // right motor speed

float angleSum; 
float z0;

PololuBuzzer buzzer;
AStar32U4Motors motors;
AStar32U4ButtonA buttonA;
AStar32U4ButtonB buttonB;
AStar32U4ButtonC buttonC;

int main() {
  stop();
  moveForward(int, int, int);
  turnLeft();
  turnRight();

  return 0;
}
void setup() {
  Serial.begin(9600);

  pinMode(lPin, OUTPUT);
  pinMode(rPin, OUTPUT);
  // Play startup sound.
  // buzzer.play("v10>>g16>>>c16"); 

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
  }
}

void adjust(bool flip = false) { // set flip to true to adjust when robot is backwards
  float x, y, z;
  int MIN, MAX;
  if (!flip) {
    int MIN = 50; 
    int MAX = 120;
  }
  else {
    int MIN = -120;
    int MAX = -50;
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
  
}

void turnRight() {
  
}

void stop() {
  startingLeft = currentLeft = 0;
  startingRight = currentRight = 0; 
  angleSum = 0;

  motors.setSpeeds(0, 0);
}

float convertAngle(float angle) {
  return 0;
}

void calibrate(int iter = 1000) {
  float x, y, z;
  float sum = 0; 
  for (int i = 0; i < iter; i++) {
    IMU.readGyroscope(x, y, z);
    sum += z;
  }
  z0 = sum/iter; 
  delay(1);
}

void loop() {
  float x, y, z;
  IMU.readGyroscope(x, y, z);
  Serial.println(z);
}
