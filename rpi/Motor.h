#pragma once

#include "MotorPosition.h"

#include <atomic>
#include <algorithm>

class Motor {
public:
    Motor(MotorPosition position);
    Motor(Motor&& o);

public:
    void setThrottle(double throttle_) { _throttle = std::min(throttle_, 1.0); }
    double getThrottle(double roll, double pitch, double yaw);
    MotorPosition getPosition() const { return _position; }

private:
    const MotorPosition _position;
    std::atomic<double> _throttle{0.0};
    double _roll = 0.0;
    double _pitch = 0.0;
    double _yaw = 0.0;
};

