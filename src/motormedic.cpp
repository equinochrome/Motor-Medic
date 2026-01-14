#include "Medic/motor_medic.hpp"
#include "Medic/motorThresholds.hpp"
#include <cmath>

namespace motor_medic {

MotorReport check(pros::Motor& motor) {
  MotorReport r;

  r.port        = motor.get_port();
  r.temperature = motor.get_temperature();      // °C
  r.current     = motor.get_current_draw();     // mA
  r.velocity    = motor.get_actual_velocity();  // rpm

  r.over_temp    = motor.is_over_temp();
  r.over_current = motor.is_over_current();

  // Default state
  r.status = MotorStatus::OK;

  // fail conditions
  if (r.over_temp ||
      r.over_current ||
      r.temperature >= FAIL_TEMP ||
      r.current >= FAIL_CURRENT ||
      std::abs(r.velocity) < MIN_VELOCITY) {
    r.status = MotorStatus::FAIL;
  }
  // warning  conditions (warm motors)
  else if (r.temperature >= WARN_TEMP ||
           r.current >= WARN_CURRENT) {
    r.status = MotorStatus::WARNING;
  }

  return r;
}

} // namespace motor_medic
