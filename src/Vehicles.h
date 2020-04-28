#include <iostream>
#include <opencv2/opencv.hpp>

class Vehicles{
public:
    Vehicles(int id, std::string vClass,cv::Mat vIm,cv::Rect r) : vehicleID(id),vehicleClass(vClass),scene(vIm),roi(r){}
    Vehicles() : vehicleID(-1),vehicleClass(""),scene(cv::Mat(cv::Mat::zeros(cv::Size(300,300),CV_8UC1))),roi(0,0,0,0) {}
    void saveDetectedVehicle();
private:
    int vehicleID;
    std::string vehicleClass;
    cv::Mat scene;
    cv::Rect roi;
};