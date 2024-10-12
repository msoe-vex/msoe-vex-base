#include "main.h"

/////
// For installation, upgrading, documentations and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 110;  
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

///
// Constants
///
void default_constants() {
  ezChassis.pid_heading_constants_set(3, 0, 20);
  ezChassis.pid_drive_constants_set(14.3, 0, 0);
  ezChassis.pid_turn_constants_set(2.3, 0, 8.25);
  ezChassis.pid_swing_constants_set(5, 0, 30);

  ezChassis.pid_turn_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  ezChassis.pid_swing_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  ezChassis.pid_drive_exit_condition_set(300_ms, 1_in, 500_ms, 3_in, 750_ms, 750_ms);

  ezChassis.slew_drive_constants_set(7_in, 50);
}

void competition_auton() {

  //example move forward
  ezChassis.pid_drive_set(10_in, DRIVE_SPEED);
  ezChassis.pid_wait();

  //example move backwards
  ezChassis.pid_drive_set(10_in, DRIVE_SPEED);
  ezChassis.pid_wait();

  //example turn right
  ezChassis.pid_turn_set(90_deg, TURN_SPEED);
  ezChassis.pid_wait();

  //example turn left
  ezChassis.pid_turn_set(-90_deg, TURN_SPEED);
  ezChassis.pid_wait();
}

void test_auton() {
  ezChassis.pid_drive_set(60_in, DRIVE_SPEED);
  ezChassis.pid_wait();

  ezChassis.pid_turn_set(-90_deg, TURN_SPEED);
  ezChassis.pid_wait();

  ezChassis.pid_drive_set(60_in, DRIVE_SPEED);
  ezChassis.pid_wait();
}