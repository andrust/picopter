#include "Telemetry.h"

constexpr std::chrono::milliseconds Telemetry::DEFAULT_TELEMETRY_INTERVAL;

Telemetry::Telemetry() {
    _senderThread = std::thread(std::bind(&Telemetry::senderThread, this));
}

Telemetry::~Telemetry() {
    _stopFlag = true;
    if (_senderThread.joinable() ) {
        _senderThread.join();
    }
}

void Telemetry::updateOrientation(uint32_t pitch, uint32_t roll, uint32_t yaw) {
    _pitch = pitch;
    _roll = roll;
    _yaw = yaw;
}

void Telemetry::updateTime(const std::chrono::system_clock::time_point& now) {
    using namespace std::chrono;
    _ts = duration_cast<microseconds>(now.time_since_epoch()).count();
}

void Telemetry::senderThread() {
    while (!_stopFlag) {
        std::this_thread::sleep_for(DEFAULT_TELEMETRY_INTERVAL);
    }
}
