// Class with all the Raspberry Pi functionality but moved to the Arduino
#pragma once
#include <Servo.h>
#include <Romi32U4.h>
// #include <AStar32U4.h>
#include <Arduino_LSM6DS3.h>
#include <Arduino.h>
#include <stdio.h>
#include <math.h> // i need pi
// #include <Vector.h>

class Motion 
{
  // AStar32U4Motors motors;
  Romi32U4Motors motors;
  Romi32U4Encoders encoders;
  
  public: 
    void moveForward(int ls, int rs, int dist);
    void moveBackward(int ls, int rs, int dist);
    void turnLeft();
    void turnRight();
    void stop();
    void startRobot(int arr[], int size);
    void calibrate();
    float convertAngle(float angle);
    float getz0();

  private: 
    void adjust(bool flip = false);
    int startingLeft, startingRight;
    int currentLeft, currentRight; // current motor speeds
    int lEncoder, rEncoder;
    float angleSum; 
    float z0;
    float distFact = (M_PI * 16.5) * 1437.09; // conversion factor: cm -> rotations -> encoder counts 
    float READ_SPEED = 0.001;
    int L_PIN = 9;  // left motor speed
    int R_PIN = 10;  // right motor speed
    int FREQ = 100; // take 100 readings to calibrate gyro
};

