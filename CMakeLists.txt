cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
SET(OpenCV_DIR /usr/local/lib/cmake/opencv4)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

project(VehicleDetector)

find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)


include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})

add_executable(vehicleDetector src/source.cpp src/Vehicles.cpp)

target_link_libraries(vehicleDetector PRIVATE ${OpenCV_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

