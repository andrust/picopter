#pragma once

#include <cstdint>

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

private:
    typedef int device_id_t;
    double _roll = -1.0;
    double _pitch = 1.0;
    double _yaw = 2.0;
    double _temp = 0.0;

    device_id_t _dev;
};
