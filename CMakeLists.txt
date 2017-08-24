project(Path_Planning)

cmake_minimum_required (VERSION 3.5)

add_definitions(-std=c++11)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

set(sources
        src/main.cpp
        src/lib/spline.h
        src/tmp/vehicle_tmp.h
        src/tmp/vehicle_tmp.cpp
        src/tmp/cost_tmp.cpp
        src/tmp/cost_tmp.h
        src/state/states/state.cpp
        src/state/states/state.h
        src/state/machine.cpp
        src/state/machine.h
        src/state/states/cruising_state.cpp
        src/state/states/cruising_state.h
        src/state/states/chainging_lane_to_left_state.cpp
        src/state/states/chainging_lane_to_left_state.h
        src/state/states/chainging_lane_to_right_state.cpp
        src/state/states/chainging_lane_to_right_state.h
        src/state/states/ready_state.cpp
        src/state/states/ready_state.h src/measurement.h src/measurement.cpp src/cost.cpp src/cost.h src/vehicle.cpp src/vehicle.h
        src/road.cpp src/road.h src/controller.cpp src/controller.h src/state/states/following_state.cpp src/state/states/following_state.h)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") 

include_directories(/usr/local/include)
include_directories(/usr/local/opt/openssl/include)
link_directories(/usr/local/lib)
link_directories(/usr/local/opt/openssl/lib)
link_directories(/usr/local/Cellar/libuv/1.11.0/lib)

endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") 

add_subdirectory(src)
add_subdirectory(test)

add_executable(path_planning ${sources})

target_link_libraries(path_planning z ssl uv uWS)
