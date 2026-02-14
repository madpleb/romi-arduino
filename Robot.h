// Class with all the Raspberry Pi functionality but moved to the Arduino
#pragma once
#include <Servo.h>
#include <AStar32U4.h>
#include <Arduino_LSM6DS3.h>
#include <stdio.h>
// #include <Vector.h> 


int startingLeft, startingRight;
int currentLeft, currentRight; // current motor speeds

int lEncoder, rEncoder;


float angleSum; 
float z0;

PololuBuzzer buzzer;
AStar32U4Motors motors;
AStar32U4ButtonA buttonA;
AStar32U4ButtonB buttonB;
AStar32U4ButtonC buttonC;


float convertAngle(float angle);

void adjust(bool flip = false);

void moveForward(int ls, int rs, int dist);

void moveBackward(int ls, int rs, int dist);

void turnLeft();

void turnRight();

void stop();
void startRobot(int arr[]);

void calibrate(int freq);
