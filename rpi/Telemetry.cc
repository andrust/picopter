#include "Telemetry.h"

#include <sstream>
#include "telemetry.pb.h"

constexpr std::chrono::milliseconds Telemetry::DEFAULT_TELEMETRY_INTERVAL;

Telemetry::Telemetry()
: _pubsocket(ZmqHelper::create(zmq::socket_type::pub))
{
    _pubsocket.bind("tcp://0.0.0.0:2000");
    _senderThread = std::thread(std::bind(&Telemetry::senderThread, this));
}

Telemetry::~Telemetry() {
    _stopFlag = true;
    if (_senderThread.joinable() ) {
        _senderThread.join();
    }
}

void Telemetry::updateOrientation(int32_t pitch, int32_t roll, int32_t yaw) {
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
        auto update = createMsg();
        zmq::message_t msg(update.c_str(), update.size());
        _pubsocket.send(msg);
        std::this_thread::sleep_for(DEFAULT_TELEMETRY_INTERVAL);
    }
}

std::string Telemetry::createMsg() {
    fc::TelemetryRecord rec;
    rec.set_timestamp(_ts);
    rec.set_pitch(_pitch);
    rec.set_roll(_roll);
    rec.set_yaw(_yaw);
    std::string ret;
    rec.SerializeToString(&ret);
    return ret;
}
