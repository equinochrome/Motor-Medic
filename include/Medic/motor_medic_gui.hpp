#pragma once
#include "pros/motors.hpp"
#include <vector>

namespace motor_medic_gui {

// Create the screen and start auto-updating.
// Pass pointers to the motors you want shown.
void init(const std::vector<pros::Motor*>& motors);

// Optional manual refresh (auto-refresh is already running).
void refresh();

} // namespace motor_medic_gui
