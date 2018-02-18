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
    void updateOrientation(double pitch, double roll, double yaw);
    void updateTime(const std::chrono::system_clock::time_point& now);
    void updateTemp(double temp);

private:
    void senderThread();
    std::string createMsg();

private:
    bool _stopFlag = false;
    std::thread _senderThread;
    std::atomic<double> _pitch;
    std::atomic<double> _roll;
    std::atomic<double> _yaw;
    std::atomic<double> _temp;
    std::atomic<uint64_t> _ts;

    zmq::socket_t _pubsocket;
};
