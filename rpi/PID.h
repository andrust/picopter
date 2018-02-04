#pragma once

#include <chrono>

#include <atomic>

class PID {
public:
    PID(double kp, double ki, double kd);
    double update(double currentValue, std::chrono::system_clock::time_point ts);
    void set(double value) { _target = value; }

private:
    double _kP = 5.0;
    double _kI = 3.0;
    double _kD = 3.0;

    double _lastErr = 0.0;
    std::chrono::system_clock::time_point _lastTs;
    std::atomic<double> _target{0.0};
    double _integral = 0.0;
};
