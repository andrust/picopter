#include "Controller.h"

Controller::Controller(Pwm& pwm)
: _pwm(pwm)
{}

void Controller::update(double pitch, double roll, double yaw, const std::chrono::system_clock::time_point& now) {
    auto r = _pidRoll.update(roll, now);
    auto p = _pidPitch.update(pitch, now);
    auto y = _pidYaw.update(yaw, now);

    for(auto&& m : _motors) {
        _pwm.set(m.getPosition(), m.getThrottle(r, p, y));
    }
}

void Controller::setOrientation(double pitch, double roll, double yaw) {
    _pidRoll.set(roll);
    _pidPitch.set(pitch);
    _pidYaw.set(yaw);
}

void Controller::setThrottle(double throttle) {
    for(auto&& m : _motors) {
        m.setThrottle(throttle);
    }
}
