#include <locale.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <thread>
#include <iostream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <uWS/uWS.h>
#include "WebOutputWrapper.cpp"

#include "util/settings.h"
#include "FullSystem/FullSystem.h"
#include "util/Undistort.h"
//#include "IOWrapper/Pangolin/PangolinDSOViewer.h"
//#include "IOWrapper/OutputWrapper/SampleOutputWrapper.h"


//#include <ros/ros.h>
//#include <sensor_msgs/image_encodings.h>
//#include <sensor_msgs/Image.h>
//#include <sensor_msgs/CameraInfo.h>
//#include <geometry_msgs/PoseStamped.h>
//#include "cv_bridge/cv_bridge.h"


std::string calib = "";
std::string vignetteFile = "";
std::string gammaFile = "";
bool useSampleOutput=true;

using namespace cv;
using namespace dso;

FullSystem* fullSystem = 0;
Undistort* undistorter = 0;
int frameID = 0;

/*
void vidCb(const sensor_msgs::ImageConstPtr img)
{
	cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(img, sensor_msgs::image_encodings::MONO8);
	assert(cv_ptr->image.type() == CV_8U);
	assert(cv_ptr->image.channels() == 1);


	if(setting_fullResetRequested)
	{
		std::vector<IOWrap::Output3DWrapper*> wraps = fullSystem->outputWrapper;
		delete fullSystem;
		for(IOWrap::Output3DWrapper* ow : wraps) ow->reset();
		fullSystem = new FullSystem();
		fullSystem->linearizeOperation=false;
		fullSystem->outputWrapper = wraps;
	    if(undistorter->photometricUndist != 0)
	    	fullSystem->setGammaFunction(undistorter->photometricUndist->getG());
		setting_fullResetRequested=false;
	}

	MinimalImageB minImg((int)cv_ptr->image.cols, (int)cv_ptr->image.rows,(unsigned char*)cv_ptr->image.data);
	ImageAndExposure* undistImg = undistorter->undistort<unsigned char>(&minImg, 1,0, 1.0f);
	fullSystem->addActiveFrame(undistImg, frameID);
	frameID++;
	delete undistImg;

}
*/

uWS::Hub h;

void startServer()
{
  h.onMessage([](uWS::WebSocket<uWS::SERVER> ws, char *message, size_t length, uWS::OpCode opCode) {
      if (length && message[0] != 'S' && length < 4096) {
          // add this message to the store, cut off old messages
          std::cout << "Message posted: " << std::string(message, length) << std::endl;
      }
      ws.send(message, length, opCode);
  });

  h.onHttpRequest([](uWS::HttpResponse *res, uWS::HttpRequest req, char *data, size_t length, size_t remainingBytes) {
      res->end("", 0);
  });

  h.listen(9090);
  h.run();
}

int main( int argc, char** argv )
{

  VideoCapture stream1(-1);   //0 is the id of video device.0 if you have only one camera.

  if (!stream1.isOpened()) { //check if video device has been initialised
    std::cout << "cannot open camera" << std::endl;
  }

  std::thread server(startServer);
	//ros::init(argc, argv, "dso_live");

  calib = "camera.txt";
  vignetteFile = "";
  gammaFile = "";
  multiThreading = false;
  disableAllDisplay = true;
  setting_logStuff = false;
  setting_debugout_runquiet = true;

	//for(int i=1; i<argc;i++) parseArgument(argv[i]);


	setting_desiredImmatureDensity = 1000;
	setting_desiredPointDensity = 1200;
	setting_minFrames = 5;
	setting_maxFrames = 7;
	setting_maxOptIterations=4;
	setting_minOptIterations=1;
	setting_logStuff = false;
	setting_kfGlobalWeight = 1.3;


	printf("MODE WITH CALIBRATION, but without exposure times!\n");
	setting_photometricCalibration = 0; // 2 for calibration
	setting_affineOptModeA = 0;
	setting_affineOptModeB = 0;



    undistorter = Undistort::getUndistorterForFile(calib, gammaFile, vignetteFile);

    setGlobalCalib(
            (int)undistorter->getSize()[0],
            (int)undistorter->getSize()[1],
            undistorter->getK().cast<float>());


    fullSystem = new FullSystem();
    fullSystem->linearizeOperation=false;

    fullSystem->outputWrapper.push_back(new IOWrap::WebOutputWrapper(&h));


    if(undistorter->photometricUndist != 0)
    	fullSystem->setGammaFunction(undistorter->photometricUndist->getG());

    //ros::NodeHandle nh;
    //ros::Subscriber imgSub = nh.subscribe("image", 1, &vidCb);

    while(true){
      Mat cameraFrame;
      stream1.read(cameraFrame);

      MinimalImageB minImg((int)cameraFrame.cols, (int)cameraFrame.rows,(unsigned char*)cameraFrame.data);
    	ImageAndExposure* undistImg = undistorter->undistort<unsigned char>(&minImg, 1,0, 1.0f);
    	fullSystem->addActiveFrame(undistImg, frameID);
    	frameID++;
    	delete undistImg;

      if(waitKey(30) >= 0)
        break;
    }

    //ros::spin();

    for(IOWrap::Output3DWrapper* ow : fullSystem->outputWrapper)
    {
        ow->join();
        delete ow;
    }

    delete undistorter;
    delete fullSystem;

	return 0;
}
