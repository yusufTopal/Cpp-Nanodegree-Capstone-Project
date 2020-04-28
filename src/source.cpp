#include <iostream>
#include <sstream>
#include <fstream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>

#include<thread>
#include <mutex>
#include "Vehicles.h"

using namespace std;
using namespace cv;
using namespace cv::dnn;

int imageWidth = 416;
int imageHeight = 416;
float confidenceThreshold =0.5, nmsThreshold=0.4;
vector<string> yoloClassNames;

const string yolo_classes = "yolov3/coco.names";
const string yoloConfig ="yolov3/yolov3.cfg";
const string yoloWeights ="yolov3/yolov3.weights";

const string originalImageWindow = "Input media";
const string imageUnderProcessWindow = "Media under process";
mutex mut;


vector <string> getOutputsNames(const Net& net){
    static vector<string> names;
    if(names.empty())
    {   
        vector<int> outLayers = net.getUnconnectedOutLayers();
        vector<string>  layersNames= net.getLayerNames();
        names.resize(outLayers.size());
        for(int i=0; i< outLayers.size();++i){
            names[i]=layersNames[outLayers[i]-1];
        }
        return names;
    }

    return names;
}

void displayWindow(Mat inputImage){
    mut.lock();
    ifstream classFile(yolo_classes.c_str());
    string clInstance;
    while (getline(classFile,clInstance))
    {
        yoloClassNames.emplace_back(clInstance);
    }
    
    Net net = readNetFromDarknet(yoloConfig,yoloWeights);
    net.setPreferableBackend(DNN_BACKEND_OPENCV);
    net.setPreferableTarget(DNN_TARGET_CPU);
    vector<int> classIds;
    vector<float> confidences;
    vector<Rect> boxes;
    vector<Mat> outs;
    Mat inputBlob;
    blobFromImage(inputImage,inputBlob,1/255.0,Size(imageWidth,imageHeight),Scalar(0,0,0),true,false);
    net.setInput(inputBlob);
    net.forward(outs, getOutputsNames(net));

    for(int i=0;i< outs.size();++i)
    {
        // scan all bounding boxes output from the network and keep higher conf.
    float *data =(float *) outs[i].data;
        for(int j =0;j< outs[i].rows;++j,data+=outs[i].cols)
            {
                Mat scores = outs[i].row(j).colRange(5,outs[i].cols);
                Point classIdPoint;
                double confidence;
                minMaxLoc(scores,0,&confidence,0,&classIdPoint);
                if(confidence > confidenceThreshold)
                    {
                        int centerX= (int)(data[0]*inputImage.cols);
                        int centerY= (int)(data[1]*inputImage.rows);
                        int width = (int) (data[2]*inputImage.cols);
                        int height = (int)(data[3]*inputImage.rows);
                        int left = centerX - width/2;
                        int top = centerY -height/2;
                        classIds.emplace_back(classIdPoint.x);
                        confidences.emplace_back((float)confidence);
                        boxes.emplace_back(Rect(left,top,width,height));
                    }
            }
    }
    vector<int> indices;
    vector<Vehicles> vehicles;
    string objectName;
    int baseLine;
    NMSBoxes(boxes,confidences,confidenceThreshold,nmsThreshold,indices);
    for(int i=0; i<indices.size();++i){
        int idx= indices[i];
        Rect box = boxes[idx];
        objectName = yoloClassNames[classIds[idx]];
        if(objectName == "car" || objectName =="truck" || objectName =="bus" || objectName == "motorbike")
       {                
            vehicles.emplace_back(Vehicles(idx,objectName,inputImage,box));
       }
    }
    for(int i =0; i<vehicles.size();i++){
        vehicles[i].saveDetectedVehicle();
    }
    mut.unlock();
}

int main(int argc, char **argv)
{  
    cout<< "Please press 'S' to save detected vehicle's images.." << endl;
    cout << "Press ESC to escape" << endl;
    Mat inputImage;
    string videoFile = "../run.mp4";
    const string originalWindow= "Input Video";
    if(argc > 1)
        videoFile = argv[1];      

    VideoCapture cap (videoFile);
    namedWindow(originalWindow,1);
    bool frameCheck;
    while(true)
{
    frameCheck = cap.read(inputImage);
    if(!frameCheck) {
        std::cout<< "End of file"<<std::endl;
        break;
    }
    string t = "Please press S to save detected trucks/cars or ESC to escape";
    cv::putText(inputImage,t,Point(0,20),1,1,Scalar(0,0,255));
    imshow(originalWindow,inputImage);
    auto s = waitKey(30);
   
   if(s==27){
			std::cout<<"Aborting..." <<std::endl;
            destroyWindow(originalWindow);
			return 0;
	}
    if(s=='s')
    {
            thread myThread(displayWindow,inputImage);
            myThread.join();
    }
   
}
 return 0;

}
