#include "Motor.h"

Motor::Motor(MotorPosition position)
: _position(position)
{
    switch(position) {
        case MotorPosition::FRONT_LEFT:
            _roll = 1.0;
            _pitch = 1.0;
            _yaw = -1.0;
            break;
        case MotorPosition::FRONT_RIGHT:
            _roll = -1.0;
            _pitch = -1.0;
            _yaw = 1.0;
            break;
        case MotorPosition::REAR_LEFT:
            _roll = 1.0;
            _pitch = 1.0;
            _yaw = 1.0;
            break;
        case MotorPosition::REAR_RIGHT:
            _roll = -1.0;
            _pitch = 1.0;
            _yaw = -1.0;
            break;
        default:
            std::abort();
            break;
    }
}

Motor::Motor(Motor&& o)
: _position(o._position)
, _roll(o._roll)
, _pitch(o._pitch)
, _yaw(o._yaw)
{
    _throttle = o._throttle.load();
}

double Motor::getThrottle(double roll, double pitch, double yaw) {
    return std::min(1.0, _throttle.load() + _roll*roll + _pitch*pitch + _yaw*yaw);
}
