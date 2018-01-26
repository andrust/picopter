project(FligtControl CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")

add_executable( flight-control
    main.cc
    Telemetry.cc
    Imu.cc
    I2C.cc
)

target_link_libraries( flight-control
    pthread
)
