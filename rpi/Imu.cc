#include "Imu.h"

#include <chrono>
#include <thread>
#include <iostream>
#include <iomanip>

Imu::Imu()
: _dev(0x28)
{
    _dev.setWriteDelay(20000);
    _dev.setReadDelay(10000);
    try {
        reset();
        setMode(Mode::CONFIG);
        setupUnits();
        setupTemp();
        setMode(Mode::NDOF);
    }
    catch(const i2c_error& e) {
        throw imu_error("Failed to initialize IMU: ", e.what());
    }
}

void Imu::refresh() {
    try {
        _yaw =   readAxis(0x1a, 0,       360*16, "yaw  ");
        _roll =  readAxis(0x1c, -90*16,  90*16,  "roll ");
        _pitch = readAxis(0x1e, -180*16, 180*16, "pitch");
        _temp = readTemp();
    }
    catch(const i2c_error& e) {
        std::cerr << e.what() << std::endl;
    }
}

double Imu::readAxis(uint8_t reg_start, int16_t reg_lb, int16_t reg_ub, const char* axis_name) {
    int16_t res = _dev.read16Signed(reg_start);
    if (res < reg_lb || res > reg_ub) {
        std::cerr << "invalid " << axis_name << " value: " << std::hex << res << std::endl;
        res = 0;
    }
    return static_cast<double>(res) / 16.0;
}

double Imu::readTemp() {
    return static_cast<double>(_dev.read8Signed(0x34));
}

void Imu::reset() {
    try {
        _dev.write8(0x3f, 0x20);
        std::this_thread::sleep_for(std::chrono::milliseconds(600));
    }
    catch(const std::exception& e) {
        throw imu_error("failed to issue reset comand: ", e.what());
    }
    uint8_t res = 0;
    while(0xa0 != res) {
        try {
            res = _dev.read8(0x00);
        }
        catch(const std::exception& e) {
            std::cerr << "Failed to read ChipId: " << e.what() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
}

void Imu::setMode(Mode m) {
    try {
        _dev.write8(0x3d, static_cast<std::underlying_type<Mode>::type>(m));
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    catch(const std::exception& e) {
        throw imu_error("SetMode failed: ", e.what());
    }
}

void Imu::setupUnits() {
    try {
        _dev.write8(0x3b, 0x80);
    }
    catch(const std::exception& e) {
        throw imu_error("SetupUnits failed: ", e.what());
    }
}

void Imu::setupTemp() {
    try {
        _dev.write8(0x40, 0x01);
    }
    catch(const std::exception& e) {
        throw imu_error("SetupTemp failed: ", e.what());
    }
}
