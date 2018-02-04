project(FligtControl CXX)

cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always --std=c++14")

include_directories(${CMAKE_BINARY_DIR}/proto)

if (NOT PYTHON)
add_subdirectory(rpi)
endif()
add_subdirectory(proto)
#add_subdirectory(python)

