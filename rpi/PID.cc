#include "PID.h"

PID::PID(double kp, double ki, double kd)
: _kP(kp)
, _kI(ki)
, _kD(kd)
, _lastTs(std::chrono::system_clock::now())
{}

double PID::update(double currentValue, std::chrono::system_clock::time_point ts) {
    auto dt = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(_lastTs - ts).count()) / 1.0e6;
    auto error = _target - currentValue;
    auto derivative = (error - _lastErr) / dt;

    _integral += error * dt;
    _lastErr = error;
    _lastTs = ts;

    return _kP * error + _kI * _integral + _kD * derivative;
}
