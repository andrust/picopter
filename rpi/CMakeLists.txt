add_definitions(-DZMQ_HAS_RVALUE_REFS=1)

add_executable( flight-control
    main.cc
    Telemetry.cc
    Imu.cc
    I2C.cc
    ZmqHelper.cc
)

target_link_libraries( flight-control
    pthread
    zmq
    telemetry_proto
)
