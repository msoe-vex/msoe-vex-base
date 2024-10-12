#include "main.h" 
//Non Drive Motor Set up here (Naming each non-drive motor and declaring their port number).
//Pneumatic Set up here as well.
//Remember to define each motor in globals.hpp as well, otherwise code wont work.

//Subsystem Motors


//Pneumatics
//doing this instead of using ADIDigitalOut gives access to
//get_value(), making turning this into a 1 button toggle a lot easier
pros::ADIPort Claw1('b', pros::E_ADI_DIGITAL_OUT);
pros::ADIPort Claw2('a', pros::E_ADI_DIGITAL_OUT);