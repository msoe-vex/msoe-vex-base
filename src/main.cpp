#include "main.h"

/////
// For installation, upgrading, documentations and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

//Drivetrain constants

/*
const vector<int> leftMotorPorts = {-5,8,-9};
const vector<int> rightMotorPorts = {-3,4,-11};
const int motorRPM = 600;
const pros::motor_gearset_e_t motorGearSet = pros::motor_gearset_e_t::E_MOTOR_GEAR_600;
const int imuPort = 16;
const float driveWheelDiameter = 3.25;
const float trackingWheelDiameter = 2;
const float driveRPM = 360;
const float driveTrackWidth = 10.75;
const float verticalTrackingWheelOffset = 1.625;
const float horizontalTrackingWheelOffset = 2.75;
const int verticalEncoderPortTop = 'D'; //C/D //TODO
const int verticalEncoderPortBottom = 'C'; //C/D TODO
const int horizontalEncoderPortTop = 'B'; //A/B //TODO
const int horizontalEncoderPortBottom = 'A'; //A/B //TODO
*/

const vector<int> leftMotorPorts = {-11,-12,-13};
const vector<int> rightMotorPorts = {8,9,10};
const int motorRPM = 600;
const pros::motor_gearset_e_t motorGearSet = pros::motor_gearset_e_t::E_MOTOR_GEAR_600;
const int imuPort = 6;
const float driveWheelDiameter = 2.75;
const float trackingWheelDiameter = 2;
const float driveRPM = 360;
const float driveTrackWidth = 10.75;
const float verticalTrackingWheelOffset = 1.625;
const float horizontalTrackingWheelOffset = 2.75;
const int verticalEncoderPortTop = 7; //C/D //TODO
const int verticalEncoderPortBottom = 8; //C/D TODO
const int horizontalEncoderPortTop = 5; //A/B //TODO
const int horizontalEncoderPortBottom = 6; //A/B //TODO


// EZ Template Chassis constructor
ez::Drive ezChassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  leftMotorPorts

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  ,rightMotorPorts

  // IMU Port
  ,imuPort

  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
  ,driveWheelDiameter

  // Cartridge RPM
  ,motorRPM

  // External Gear Ratio (MUST BE DECIMAL) This is WHEEL GEAR / MOTOR GEAR
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 84/36 which is 2.333
  // eg. if your drive is 60:36 where the 36t is powered, your RATIO would be 60/36 which is 0.6
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 36/60 which is 0.6
  ,motorRPM/driveRPM
);



//LemLib Setup

pros::MotorGroup left_motors(initializer_list<pros::Motor>{
  pros::Motor(leftMotorPorts[0], motorGearSet),
  pros::Motor(leftMotorPorts[1], motorGearSet),
  pros::Motor(leftMotorPorts[2], motorGearSet)
} );

pros::MotorGroup right_motors(initializer_list<pros::Motor>{
  pros::Motor(rightMotorPorts[0], motorGearSet),
  pros::Motor(rightMotorPorts[1], motorGearSet),
  pros::Motor(rightMotorPorts[2], motorGearSet)
} );

lemlib::Drivetrain_t drivetrain{
  &left_motors, // left motor group
  &right_motors, // right motor group
  driveTrackWidth, // track width
  driveWheelDiameter, // wheel diameter
  driveRPM // drivetrain rpm
};

pros::Imu imu(imuPort);

pros::ADIEncoder horizontal_encoder(horizontalEncoderPortTop, horizontalEncoderPortBottom);
pros::ADIEncoder vertical_encoder(verticalEncoderPortTop, verticalEncoderPortBottom);

//pros::Rotation horizontal_sensor(1);
//pros::Rotation vertical_sensor(2);

lemlib::TrackingWheel vertical_tracking_wheel(
  &vertical_encoder,
  trackingWheelDiameter, 
  verticalTrackingWheelOffset
);

lemlib::TrackingWheel horizontal_tracking_wheel(
  &horizontal_encoder,
  trackingWheelDiameter, 
  horizontalTrackingWheelOffset
);

lemlib::OdomSensors_t sensors{
  &vertical_tracking_wheel, nullptr, //2nd tracking wheel, null since using IMU
  &horizontal_tracking_wheel, nullptr, //2nd tracking wheel, null since using IMU
  &imu
};

// lateral PID controller
lemlib::ChassisController_t lateral_controller{
  10, // proportional gain (kP)
  3, // derivative gain (kD)
  1, // small error range, in inches
  100, // small error range timeout, in milliseconds
  3, // large error range, in inches
  500, // large error range timeout, in milliseconds
  20 // maximum acceleration (slew)
};

// angular PID controller
lemlib::ChassisController_t angular_controller{
  2, // proportional gain (kP)
  10, // derivative gain (kD)
  1, // small error range, in degrees
  100, // small error range timeout, in milliseconds
  3, // large error range, in degrees
  500, // large error range timeout, in milliseconds
  0 // maximum acceleration (slew)
};

// create the chassis
lemlib::Chassis lemlibChassis(
  drivetrain, // drivetrain settings
  lateral_controller, // lateral PID settings
  angular_controller, // angular PID settings
  sensors // odometry sensors
);

bool clawOn = false;
void toggleClaw(){
  if(clawOn){
    Claw2.set_value(0);
    pros::delay(100);
    Claw1.set_value(0);
  }else{
    Claw1.set_value(1);
    pros::delay(100);
    Claw2.set_value(1);
  }
  clawOn = !clawOn;
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  //ez::ez_template_print();
  
  pros::delay(500); // Stop the user from doing anything while legacy ports configure

  // Configure your chassis controls
  ezChassis.opcontrol_curve_buttons_toggle(true); // Enables modifying the controller curve with buttons on the joysticks
  ezChassis.opcontrol_drive_activebrake_set(0); // Sets the active brake kP. We recommend 0.1.
  ezChassis.opcontrol_curve_default_set(8, 10); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!

  //LemLib initialize
  lemlibChassis.calibrate();
  lemlibChassis.setPose(0, 0, 0);

  pros::Task screen_task([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", lemlibChassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", lemlibChassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", lemlibChassis.getPose().theta); // heading
            // delay to save resources
            pros::delay(20);
        }
    });

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // ezChassis.opcontrol_curve_buttons_left_set (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // ezChassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.autons_add({
    Auton("Competition Auton", competition_auton),
    Auton("Test", test_auton)
  });

  // Initialize chassis and auton selector
  ezChassis.initialize();
  ez::as::initialize();
  master.rumble(".");

  // pros::delay(50);
  // pros::Task imuValues(getIMU);
}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}



/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}



/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  ezChassis.pid_targets_reset(); // Resets PID targets to 0
  ezChassis.drive_imu_reset(); // Reset gyro position to 0
  ezChassis.drive_sensor_reset(); // Reset drive sensors to 0
  ezChassis.drive_brake_set(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency

  ez::as::auton_selector.selected_auton_call(); // Calls selected auton from autonomous selector
  
}



/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

/*
void getIMU() {
  while (true) {
    master.print(0,0, "imu:%.2f",ezChassis.drive_imu_get());
  }
}
*/

void opcontrol() {
  // This is preference to what you like to drive on
  ezChassis.drive_brake_set(MOTOR_BRAKE_COAST);

  master.clear_line(0);

  while (true) {
    // (0,0, "imu:%.2f",ezChassis.drive_imu_get());
    
    // PID Tuner
    // After you find values that you're happy with, you'll have to set them in auton.cpp
    // if (!pros::competition::is_connected()) { 
    //   // Enable / Disable PID Tuner
    //   //  When enabled: 
    //   //  * use A and Y to increment / decrement the constants
    //   //  * use the arrow keys to navigate the constants
    //   if (master.get_digital_new_press(DIGITAL_X)) 
    //     ezChassis.pid_tuner_toggle();
        
    //   // Trigger the selected autonomous routine
       if (master.get_digital_new_press(DIGITAL_B)) 
         autonomous();

      if (master.get_digital_new_press(DIGITAL_A))
        pros::Task toggleClawTask(toggleClaw);

    //   ezChassis.pid_tuner_iterate(); // Allow PID Tuner to iterate
    // } 

    //ezChassis.opcontrol_tank(); // Tank control
    ezChassis.opcontrol_arcade_standard(ez::SPLIT); // Standard split arcade
    // ezChassis.opcontrol_arcade_standard(ez::SINGLE); // Standard single arcade
    // ezChassis.opcontrol_arcade_flipped(ez::SPLIT); // Flipped split arcade
    // ezChassis.opcontrol_arcade_flipped(ez::SINGLE); // Flipped single arcade

    // . . .
    // Put more user control code here!
    // . . .




    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
