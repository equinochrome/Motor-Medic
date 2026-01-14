#pragma once
#include "pros/motors.hpp"
#include "Medic/MotorReport.hpp"

namespace motor_medic {

  MotorReport check(pros::Motor& motor);
 
  void print(const MotorReport& report);

}
