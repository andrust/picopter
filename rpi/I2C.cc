#include "I2C.h"

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <cerrno>
#include <cstring>
#include <chrono>
#include <thread>
#include <iostream>

I2CDevice::I2CDevice(uint8_t addr)
{
    _dev = wiringPiI2CSetup(addr);
    if (_dev < 0 ) {
        std::string msg = "I2C connect failed, reason: ";
        msg += strerror(errno);
        throw i2c_error(msg);
    }
};

uint8_t I2CDevice::read8(uint8_t reg) {
    return validateByte(wiringPiI2CReadReg8(_dev, reg));
}

int8_t I2CDevice::read8Signed(uint8_t reg) {
    RawByte res;
    res.unsig = read8(reg);
    return res.sig;
}

uint16_t I2CDevice::read16(uint8_t reg) {
    RawWord res;
    res.bytes[0] = read8(reg);
    res.bytes[1] = read8(reg+1);
    return res.unsig;
}

int16_t I2CDevice::read16Signed(uint8_t reg) {
    RawWord res;
    res.unsig = read16(reg);
    return res.sig;
}

uint8_t I2CDevice::validateByte(int byte) {
    if (byte < 0 ) {
        throw i2c_error(strerror(errno));
    }
    if (byte > 255) {
        throw i2c_error("unexpected return value from wiringPi");
    }
    sleep(_readDelay);
    return byte;
}

void I2CDevice::write8(uint8_t reg, uint8_t value) {
    int result = wiringPiI2CWriteReg8(_dev, reg, value);
    if (result < 0 ) {
        throw i2c_error(strerror(errno));
    }
    sleep(_writeDelay);
}

void I2CDevice::sleep(size_t usec) {
    if (usec) {
        std::this_thread::sleep_for(std::chrono::microseconds(usec));
    }
}
