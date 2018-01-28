#pragma once

#include <cstdint>

#include "I2C.h"

class Imu {
public:
    explicit Imu(I2C& bus);

public:
    void refresh();
    int32_t roll()  const { return _roll;  }
    int32_t pitch() const { return _pitch; }
    int32_t yaw()   const { return _yaw;   }

private:
    I2C& _bus;
    int32_t _roll = -1;
    int32_t _pitch = 1;
    int32_t _yaw = 2;
};
