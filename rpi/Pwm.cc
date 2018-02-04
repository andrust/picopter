#include "Pwm.h"

#include <cstdlib>

Pwm::Pwm()
{}

void Pwm::set(const MotorPosition p, double value) {
    switch(p) {
        case MotorPosition::FRONT_LEFT:
            break;
        case MotorPosition::FRONT_RIGHT:
            break;
        case MotorPosition::REAR_LEFT:
            break;
        case MotorPosition::REAR_RIGHT:
            break;
        default:
            std::abort();
            break;
    }
}
