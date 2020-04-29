# CPPND: Final Project
This is the graduation project of [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213)

This project implements ground vehicle(bus, car, truck, motorbike) detection on the background, and saving of detected vehicle images when the user presses 'S' button. Program flow as follows
# Start the program
# Input video window appears
# Press S to save detected vehicle images
# Press ESC to terminate

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
* OpenCV >= 4.3.0
  * Linux: Can be found here [OpenCV 4.3.0](https://github.com/opencv/opencv/tree/4.3.0)
* Yolo-v3 Weights File
  * Linux: wget https://pjreddie.com/media/files/yolov3.weights and locate under yolov3 directory.

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./vehicleDetector`.
