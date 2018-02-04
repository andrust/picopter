#include "Imu.h"

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <chrono>
#include <thread>

Imu::Imu()
: _dev(wiringPiI2CSetup (0x28))
{
    reset();
    setMode(Mode::CONFIG);
    setupUnits();
    setupTemp();
    setMode(Mode::NDOF);
}

void Imu::refresh() {
    int16_t pitch = wiringPiI2CReadReg16(_dev, 0x1f);
    int16_t roll = wiringPiI2CReadReg16(_dev, 0x1d);
    int16_t yaw = wiringPiI2CReadReg16(_dev, 0x1b);
    int8_t temp = wiringPiI2CReadReg8(_dev, 0x34);

    _pitch = static_cast<double>(pitch) / 16.0;
    _roll = static_cast<double>(roll) / 16.0;
    _yaw = static_cast<double>(yaw) / 16.0;
    _temp = static_cast<double>(temp);
}

void Imu::reset() {
    wiringPiI2CWriteReg8(_dev, 0x3f, 0x20);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    while(0xa0 != wiringPiI2CReadReg8(_dev, 0x00)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void Imu::setMode(Mode m) {
    wiringPiI2CWriteReg8(_dev, 0x3d, static_cast<std::underlying_type<Mode>::type>(m));
    std::this_thread::sleep_for(std::chrono::milliseconds(25));
}

void Imu::setupUnits() {
    wiringPiI2CWriteReg8(_dev, 0x3b, 0x80);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void Imu::setupTemp() {
    wiringPiI2CWriteReg8(_dev, 0x40, 0x00);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}
