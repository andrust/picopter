#include "PID.h"

PID::PID()
: _lastTs(std::chrono::system_clock::now())
{}

int32_t PID::update(int32_t currentValue, std::chrono::system_clock::time_point ts) {
    auto dt = std::chrono::duration_cast<std::chrono::microseconds>(_lastTs - ts).count();
    auto error = _target - static_cast<double>(currentValue);
    auto derivative = (error - _lastErr) / dt;

    _integral += error * dt;
    _lastErr = error;
    _lastTs = ts;

    return static_cast<int32_t>(P_GAIN * error + I_GAIN * _integral + D_GAIN * derivative);
}
