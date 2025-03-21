#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor leftDriveMotorA = motor(PORT5, ratio18_1, false);
motor leftDriveMotorB = motor(PORT6, ratio18_1, false);
motor_group leftDrive = motor_group(leftDriveMotorA, leftDriveMotorB);
motor rightDriveMotorA = motor(PORT4, ratio18_1, true);
motor rightDriveMotorB = motor(PORT7, ratio18_1, true);
motor_group rightDrive = motor_group(rightDriveMotorA, rightDriveMotorB);
inertial Inertial = inertial(PORT8);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}