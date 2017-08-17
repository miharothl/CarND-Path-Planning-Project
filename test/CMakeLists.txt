cmake_minimum_required(VERSION 2.6)
project(basic_test)


set(sources

        ../src/state/states/state.cpp
        ../src/state/states/state.h
        ../src/state/machine.cpp
        ../src/state/machine.h
        ../src/state/states/cruising_state.h
        ../src/state/states/cruising_state.cpp
        ../src/state/states/ready_state.h
        ../src/state/states/ready_state.cpp
        ../src/state/states/chainging_lane_to_left_state.h
        ../src/state/states/chainging_lane_to_left_state.cpp
        ../src/state/states/chainging_lane_to_right_state.h
        ../src/state/states/chainging_lane_to_right_state.cpp

        ../src/sensor/measurement.h
        ../src/sensor/measurement.cpp

        ../src/cost/cost.h
        ../src/cost/cost.cpp

        ../src/cost/vehicle.h
        ../src/cost/vehicle.cpp

        cost/cost_tests.cpp
        state/machine_tests.cpp

        vehicle_tests.cpp vehicle_tests.h)

################################
# GTest
################################
ADD_SUBDIRECTORY (lib/gtest/googletest)
enable_testing()
include_directories(${gte__st_SOURCE_DIR}/include ${gte__st_SOURCE_DIR})


################################
# Unit Tests
################################
# Add test cpp file
add_executable( runUnitTests ${sources} )
# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTests gtest gtest_main)
add_test( runUnitTests runUnitTests )

