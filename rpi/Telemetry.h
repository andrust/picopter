#pragma once

#include <cstdint>
#include <chrono>

class Telemetry {
public:
    explicit Telemetry() = default;

public:
    void updateOrientation(uint32_t pitch, uint32_t roll, uint32_t yaw);
    void updateTime(const std::chrono::system_clock::time_point& now);
};
