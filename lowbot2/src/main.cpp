/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       noahl                                                     */
/*    Created:      1/4/2024, 1:47:58 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "autonomous_controller.h"
#include "autonomous_parser.h"

// A global instance of competition
vex::competition Competition;

// define your global instances of motors and other devices here

using namespace ls;

vex::motor m1(0);
vex::motor m2(1);
vex::motor m3(2);

vex::motor_group right(m1, m2, m3);

vex::motor m4(10, true);
vex::motor m5(11, true);
vex::motor m6(12, true);

vex::motor_group left(m4, m5, m6);

vex::controller contr;
vex::brain brain;

vex::digital_out wing1(brain.ThreeWirePort.A);
vex::digital_out wing2(brain.ThreeWirePort.B);

vex::motor elevator(19);
vex::motor intake(3);

vex::motor_group all(m1, m2, m3, m4, m5, m6);

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

bool pressedA = false;

void autonomous(void) {


// all.spinFor(vex::directionType::fwd, 3, vex::timeUnits::sec, 100, vex::velocityUnits::pct);
// switchState(wing1, wing2);
// all.spinFor(vex::directionType::rev, 1, vex::timeUnits::sec, 100, vex::velocityUnits::pct);

  using namespace ls;


  double in = 31;
  int speed = 90;

  const static double magicConstant = 0.3f;
  {
  vex::directionType dir = vex::directionType::fwd;

  if (in < 0) {
      in = -in;
      dir = vex::directionType::rev;
  }

  double dist = (double)in / 3.5 * M_PI;
  double revolutions = dist / 5;
  double rot = revolutions * 360;
  rot *= magicConstant;

  all.spinFor(dir, rot, vex::rotationUnits::deg, speed, vex::velocityUnits::pct);
  }

  all.stop(vex::brakeType::brake);

  speed = 30;

  // intake.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  // vex::task::sleep(1000);
  // intake.stop(vex::brakeType::brake);

  {
  in = -32;

  vex::directionType dir = vex::directionType::fwd;

  if (in < 0) {
      in = -in;
      dir = vex::directionType::rev;
  }

  double dist = (double)in / 3.5 * M_PI;
  double revolutions = dist / 5;
  double rot = revolutions * 360;
  rot *= magicConstant;

  all.spinFor(dir, rot, vex::rotationUnits::deg, speed, vex::velocityUnits::pct);
  }

  left.spinFor(vex::directionType::rev, 0.78f, vex::timeUnits::sec, speed, vex::velocityUnits::pct);

  {
  in = -27;
  speed = 60;

  vex::directionType dir = vex::directionType::fwd;

  if (in < 0) {
      in = -in;
      dir = vex::directionType::rev;
  }

  double dist = (double)in / 3.5 * M_PI;
  double revolutions = dist / 5;
  double rot = revolutions * 360;
  rot *= magicConstant;

  all.spinFor(dir, rot, vex::rotationUnits::deg, speed, vex::velocityUnits::pct);
  }

  all.stop(vex::brakeType::hold);
  elevator.stop(vex::brakeType::hold);


}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

bool r1Pressed = false;
bool intakeSpinning = false;

void spin_motor(vex::motor_group& motor, double voltage) {

  if (voltage < 0)
    motor.spin(vex::directionType::rev, -voltage, vex::voltageUnits::mV);
  else
    motor.spin(vex::directionType::fwd, voltage, vex::voltageUnits::mV);

}

void spin_motor(vex::motor_group& motor, double val, vex::velocityUnits vel) {

  if (val < 0)
    motor.spin(vex::directionType::rev, -val, vel);
  else
    motor.spin(vex::directionType::fwd, val, vel);

}

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

#define TANK 1
#define ARCADE 2
#define TANK_INTERP 3

#define MOV_PROF ARCADE

#if MOV_PROF == TANK

  //movement
  if (contr.Axis2.value() >= threshold) {
    right.spin(vex::directionType::fwd, pct,vex::velocityUnits::pct);
  }
  else if (contr.Axis2.value() <= -threshold) {
    right.spin(vex::directionType::rev, pct,vex::velocityUnits::pct);
  }
  else {
    right.stop(vex::brakeType::brake);
  }
  

  if (contr.Axis3.value() >= threshold) {
    left.spin(vex::directionType::rev, pct,vex::velocityUnits::pct);
  }
  else if (contr.Axis3.value() <= -threshold) {
    left.spin(vex::directionType::fwd, pct,vex::velocityUnits::pct);
  }
  else {
    left.stop(vex::brakeType::brake);
  }

#elif MOV_PROF == ARCADE
  //turning

  int forward = contr.Axis3.position(); //-100 to 100
  int sideways = 0.55 * contr.Axis1.position() + 0.35 * contr.Axis4.position(); // 90% of -100 to 90% of 100

  spin_motor(left, forward + sideways, vex::velocityUnits::pct);
  spin_motor(right, forward - sideways, vex::velocityUnits::pct);


#elif MOV_PROF == TANK_INTERP

  //movement
  if (contr.Axis2.value() >= threshold) {
    right.spin(vex::directionType::fwd, clamp((int)abs(contr.Axis3.value()), 0, 100),vex::velocityUnits::pct);
  }
  else if (contr.Axis2.value() <= -threshold) {
    right.spin(vex::directionType::rev, clamp((int)abs(contr.Axis3.value()), 0, 100),vex::velocityUnits::pct);
  }
  else {
    right.stop(vex::brakeType::brake);
  }
  

  if (contr.Axis3.value() >= threshold) {
    left.spin(vex::directionType::rev, clamp((int)abs(contr.Axis4.value()), 0, 100),vex::velocityUnits::pct);
  }
  else if (contr.Axis3.value() <= -threshold) {
    left.spin(vex::directionType::fwd, clamp((int)abs(contr.Axis4.value()), 0, 100),vex::velocityUnits::pct);
  }
  else {
    left.stop(vex::brakeType::brake);
  }

#endif



  //elevation

  if (contr.ButtonL2.pressing()) {
    elevator.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
  }
  else if (contr.ButtonL1.pressing()) {
    elevator.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
  }
  else {
    elevator.stop(vex::brakeType::hold);
  }

#if 1

  //intake
  if (contr.ButtonR1.pressing()) {
    intake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  }
  else if (contr.ButtonR2.pressing()) {
    intake.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  }
  else {
    intake.stop(vex::brakeType::brake);
  }

#elif 1

  if (contr.ButtonR1.pressing() && !r1Pressed) {
    r1Pressed = true;
  }

  if (!contr.ButtonR1.pressing() && r1Pressed) {
    r1Pressed = false;

    if (!intakeSpinning) {
      intake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      intakeSpinning = true;
    }
    else {
      intake.stop(vex::brakeType::brake);
      intakeSpinning = false;
    }
  }


#endif


  //wings
  if (contr.ButtonA.pressing()) {
    pressedA = true;
  }

  if (pressedA && !contr.ButtonA.pressing()) {
    switchState(wing1, wing2);
    pressedA = false;
  }


  vex::wait(20, vex::msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.

  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    vex::wait(10, vex::msec);
  }
}
