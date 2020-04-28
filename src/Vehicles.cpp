#include "Vehicles.h"
#include <sys/types.h>
#include <sys/stat.h>

void Vehicles::saveDetectedVehicle(){

    if(roi.x >= 0 && roi.y >= 0 && roi.width + roi.x < scene.cols && roi.height + roi.y < scene.rows)//Check for proper ROI
    {
        cv::Mat imageTobeSaved = scene(roi);
        std::string imageName = vehicleClass.append("_").append(std::to_string(vehicleID)).append(".jpg");
        if(imageTobeSaved.empty()){
            std::cout<< "Error while reading the image file of vehicle..." << std::endl;
            return;
    }
    cv::imwrite(imageName,imageTobeSaved); //Save the vehicle image
    
    }
}