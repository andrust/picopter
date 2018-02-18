#pragma once

#include <cstdint>
#include <stdexcept>
#include "I2C.h"

class imu_error : public std::runtime_error {
public:
    imu_error(const std::string& text, const std::string& reason) : runtime_error("IMU: " + text + reason) {}
};

class Imu {
public:
    Imu();

public:
    void refresh();
    double roll()  const { return _roll;  }
    double pitch() const { return _pitch; }
    double yaw()   const { return _yaw;   }
    double temp() const  { return _temp;  }

private:
    enum class Mode : uint8_t {
        CONFIG = 0x0,
        NDOF = 0x0c
    };

private:
    void reset();
    void setMode(Mode m);
    void setupUnits();
    void setupTemp();
    double readAxis(uint8_t reg_start);
    double readAxis(uint8_t reg_start, int16_t reg_lb, int16_t reg_ub, const char* axis_name);
    double readTemp();

private:
    double _roll = -1.0;
    double _pitch = 1.0;
    double _yaw = 2.0;
    double _temp = 0.0;

    I2CDevice _dev;
};
