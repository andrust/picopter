#include <iostream>
#include <csignal>
#include <thread>
#include <cstdint>
#include <google/protobuf/stubs/common.h>

#include "Telemetry.h"
#include "Imu.h"

bool should_exit = false;

void sig_handler(int sig) {
    switch(sig) {
        case SIGINT:
        case SIGTERM:
            should_exit = true;
            break;
        default:
            break;
    };
}

int main(int argc, char* argv[]) {
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);

    Imu imu;

    Telemetry telemetry;
    std::chrono::system_clock::time_point now;

    while(!should_exit) {
        imu.refresh();
        now = std::chrono::system_clock::now();
        telemetry.updateOrientation(imu.pitch(), imu.roll(), imu.yaw());
        telemetry.updateTemp(imu.temp());
        telemetry.updateTime(now);

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    std::cout << "Exiting..." << std::endl;

    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
