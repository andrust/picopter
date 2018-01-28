#pragma once

#include <cstdint>
#include <chrono>
#include <atomic>
#include <thread>

#include "ZmqHelper.h"

class Telemetry {
public:
    Telemetry();
    ~Telemetry();

private:
    static constexpr std::chrono::milliseconds DEFAULT_TELEMETRY_INTERVAL{300};

public:
    void updateOrientation(int32_t pitch, int32_t roll, int32_t yaw);
    void updateTime(const std::chrono::system_clock::time_point& now);

private:
    void senderThread();
    std::string createMsg();

private:
    bool _stopFlag = false;
    std::thread _senderThread;
    std::atomic_int _pitch;
    std::atomic_int _roll;
    std::atomic_int _yaw;
    std::atomic_int _ts;

    zmq::socket_t _pubsocket;
};
