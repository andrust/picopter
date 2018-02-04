add_definitions(-DZMQ_HAS_RVALUE_REFS=1)

add_executable( flight-control
    main.cc
    Telemetry.cc
    Imu.cc
    PID.cc
    ZmqHelper.cc
    Controller.cc
    Motor.cc
    Pwm.cc
)

target_link_libraries( flight-control
    pthread
    zmq
    telemetry_proto
    wiringPi
)
