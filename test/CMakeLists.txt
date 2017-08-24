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

        ../src/measurement.h
        ../src/measurement.cpp

        ../src/cost.h
        ../src/cost.cpp

        ../src/vehicle.h
        ../src/vehicle.cpp

        cost_tests.cpp
        machine_tests.cpp

        vehicle_tests.cpp

        ../src/road.cpp ../src/road.h
        tools/data.cpp tools/data.h ../src/controller.cpp ../src/controller.h ../src/state/states/following_state.cpp ../src/state/states/following_state.h)

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

