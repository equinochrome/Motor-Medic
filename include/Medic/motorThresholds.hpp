#pragma once

namespace motor_medic {
//      All of these can be tuned later

    inline constexpr double WARN_TEMP = 50.0; // degrees Celsius
    inline constexpr double FAIL_TEMP = 70.0; // degrees Celsius



//  current (in mA)

    inline constexpr int WARN_CURRENT = 2000;
    inline constexpr int FAIL_CURRENT = 2500;

// Velocity (rpm)
    
inline constexpr double MIN_VELOCITY = 5.0;

}