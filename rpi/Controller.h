#pragma once

#include "Pwm.h"
#include "PID.h"
#include "Motor.h"

#include <chrono>
#include <array>

class Controller {
public:
    Controller(Pwm& pwm);

public:
    void update(double pitch, double roll, double yaw, const std::chrono::system_clock::time_point& now);
    void setOrientation(double pitch, double roll, double yaw);
    void setThrottle(double throttle);

private:
    Pwm& _pwm;

    PID _pidRoll{5.0, 3.0, 3.0};
    PID _pidPitch{5.0, 3.0, 3.0};
    PID _pidYaw{5.0, 3.0, 3.0};

    std::array<Motor, 4> _motors = { MotorPosition::FRONT_LEFT, MotorPosition::FRONT_RIGHT, MotorPosition::REAR_LEFT, MotorPosition::REAR_RIGHT };
};
