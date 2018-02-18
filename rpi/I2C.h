#pragma once

#include <stdexcept>

#include <wiringPi.h>
#include <wiringPiI2C.h>

class i2c_error : public std::runtime_error {
    using runtime_error::runtime_error;
};

class I2CDevice {
public:
    explicit I2CDevice(uint8_t addr);

public:
    uint8_t read8(uint8_t reg);
    int8_t  read8Signed(uint8_t reg);
    uint16_t read16(uint8_t reg);
    int16_t  read16Signed(uint8_t reg);
    void write8(uint8_t reg, uint8_t value);
    void setReadDelay(size_t usec) { _readDelay = usec; }
    void setWriteDelay(size_t usec) { _writeDelay = usec; }

private:

    union RawByte {
        uint8_t unsig;
        int8_t sig;
    };

    union RawWord {
        uint16_t unsig;
        int16_t sig;
        uint8_t bytes[2];
    };


    uint8_t validateByte(int byte);
    void sleep(size_t usec);

private:
    int _dev;
    size_t _readDelay = 0;
    size_t _writeDelay = 0;
};
