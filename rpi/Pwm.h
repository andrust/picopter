#pragma once

#include "MotorPosition.h"

class Pwm {
public:
    Pwm();

public:
    void set(const MotorPosition p, double value);
};
