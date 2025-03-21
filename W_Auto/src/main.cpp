/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// leftDrive            motor_group   5, 6            
// rightDrive           motor_group   3, 4            
// Inertial             inertial      7               
// ---- END VEXCODE CONFIGURED DEVICES ----

// Version: 1.2.0
// Credits to Parker & Mia :)

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
double wheelDiameter = 4;
double oneInch = (360)/(wheelDiameter*M_PI);
double oneTile = 24*oneInch;

float robotPosX ;
float robotPosY;
float robotRotation = 0;

void setStarting(int startingX, int startingY) {
  robotPosX = startingX;
  robotPosY = startingY;
}

void rotateBot(double theta) {
  double turningSpeed = Inertial.rotation(degrees) - theta;
  while(fabs(turningSpeed) >= 1.5){
    turningSpeed = (Inertial.rotation(degrees) - theta)/2;
    leftDrive.spin(reverse, turningSpeed, percent);
    rightDrive.spin(forward, turningSpeed, percent);
  }
  robotRotation += Inertial.rotation(degrees);
}

double toDegrees(double radians)
{
  return(radians*180/M_PI);
}

double findC(double a, double b)
{
  return(sqrt(pow(a,2)+pow(b,2)));
}

double findAngle(double a, double b)
{
  return(toDegrees(atan2(a,b)));
}

void moveTo(double valueX, double valueY) {
	double a = (valueX - robotPosX);
	double b = (valueY - robotPosY);
	double c = findC(a,b);
  double theta = findAngle(a,b);
	rotateBot(theta);
  leftDrive.setVelocity(50, percent);
  rightDrive.setVelocity(50, percent);
	leftDrive.spinFor(forward, c*oneTile, degrees, false);
	rightDrive.spinFor(forward, c*oneTile, degrees);
  robotPosX = valueX;
  robotPosY = valueY;
}

void lookAt(double valueX, double valueY) {
	double a = (valueX - robotPosX);
	double b = (valueY - robotPosY);
  double theta = findAngle(a,b);
	rotateBot(theta);
}

void leftDriveControl() {
  leftDrive.setVelocity(Controller1.Axis3.position(percent), percent);
  leftDrive.spin(forward);
}

void rightDriveControl() {
  rightDrive.setVelocity(Controller1.Axis2.position(percent), percent);
  rightDrive.spin(forward);
}

void pre_auton(void) {
  vexcodeInit();
  leftDrive.setStopping(brake);
  rightDrive.setStopping(brake);
  Inertial.calibrate();
  setStarting(2,0);
}



void autonomous(void) {
    moveTo(2,1);
    moveTo(3,1);
    moveTo(4,2);
    moveTo(3,1);
    moveTo(2,1);
    moveTo(2,0);
    lookAt(2,1);
}

//For personal testing
void noLimitAuton() {
    moveTo(2,1);
    moveTo(3,1);
    moveTo(4,2);
    moveTo(3,1);
    moveTo(2,1);
    moveTo(2,0);
    lookAt(2,1);
}

void usercontrol(void) {
  Controller1.Axis3.changed(leftDriveControl);
  Controller1.Axis2.changed(rightDriveControl);
  Controller1.ButtonA.pressed(noLimitAuton);
  while (1) {

    wait(20, msec);
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();

  while (true) {
    wait(100, msec);
  }
}
