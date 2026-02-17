// Class with all the Raspberry Pi functionality but moved to the Arduino
#pragma once
#include <Servo.h>
#include <AStar32U4.h>
#include <Arduino_LSM6DS3.h>
#include <Arduino.h>
#include <stdio.h>
// #include <Vector.h>


const float READ_SPEED = 0.001;
const int L_PIN = 9;  // left motor speed
const int R_PIN = 10;  // right motor speed
const int FREQ = 1;



class Motion 
{
  AStar32U4Motors motors;
  // AStar32U4Encoders encoders
  
  public: 
    void moveForward(int ls, int rs, int dist);
    void moveBackward(int ls, int rs, int dist);
    void turnLeft();
    void turnRight();
    void stop();
    void startRobot(int arr[], int size);
    void calibrate();
    float convertAngle(float angle);

  private: 
    void adjust(bool flip = false);
    int startingLeft, startingRight;
    int currentLeft, currentRight; // current motor speeds
    int lEncoder, rEncoder;
    float angleSum; 
    float z0;
    float distFact = 6767; // conversion factor, cm traveled to encoder counts


};

