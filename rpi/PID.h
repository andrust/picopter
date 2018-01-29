#pragma once

#include <chrono>

#include <atomic>

class PID {
public:
    PID();
    int32_t update(int32_t currentValue, std::chrono::system_clock::time_point ts);
    void set(int32_t value) { _target = static_cast<double>(value); }

private:

    static constexpr double P_GAIN = 5.0;
    static constexpr double I_GAIN = 3.0;
    static constexpr double D_GAIN = 3.0;

    double _lastErr = 0.0;
    std::chrono::system_clock::time_point _lastTs;
    std::atomic<double> _target{0.0};
    double _integral = 0.0;
};
