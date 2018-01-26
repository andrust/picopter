#pragma once

#include <cstdint>
#include <chrono>
#include <atomic>
#include <thread>

class Telemetry {
public:
    Telemetry();
    ~Telemetry();

private:
    static constexpr std::chrono::milliseconds DEFAULT_TELEMETRY_INTERVAL{200};

public:
    void updateOrientation(uint32_t pitch, uint32_t roll, uint32_t yaw);
    void updateTime(const std::chrono::system_clock::time_point& now);

private:
    void senderThread();

private:
    bool _stopFlag;
    std::thread _senderThread;
    std::atomic_uint _pitch;
    std::atomic_uint _roll;
    std::atomic_uint _yaw;
    std::atomic_uint _ts;
};
