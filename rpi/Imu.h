#pragma once

#include <cstdint>

#include "I2C.h"

class Imu {
public:
    explicit Imu(I2C& bus);

public:
    void refresh();
    uint32_t roll()  const { return _roll;  }
    uint32_t pitch() const { return _pitch; }
    uint32_t yaw()   const { return _yaw;   }

private:
    I2C& _bus;
    uint32_t _roll = 0;
    uint32_t _pitch = 0;
    uint32_t _yaw = 0;
};
