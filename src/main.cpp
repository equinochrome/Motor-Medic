#include "main.h"

#include "medic/motor_medic_gui.hpp"

// Define motors you want to monitor
pros::Motor leftDrive(1);
pros::Motor rightDrive(2);

void initialize() {
  motor_medic_gui::init({
    &leftDrive,
    &rightDrive
  });
}


void disabled() {}

void competition_initialize() {}


void autonomous() {}


void opcontrol() {
	
}