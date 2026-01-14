#pragma once
#include "pros/motors.hpp"

enum class MotorStatus {
    OK,
    WARNING,
    FAIL
};

struct MotorReport {
    int port;
    double temperature;
    int current;
    double velocity;
    bool over_temp;
    bool over_current;
    MotorStatus status;
  };
