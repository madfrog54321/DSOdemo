#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main() {
  VideoCapture stream1(0);   //0 is the id of video device.0 if you have only one camera.

  if (!stream1.isOpened()) { //check if video device has been initialised
    cout << "cannot open camera";
  }

  stream1.set(CV_CAP_PROP_FRAME_WIDTH, 640);
  stream1.set(CV_CAP_PROP_FRAME_WIDTH, 480);

  //unconditional loops
  while (true) {
    Mat colorMat, grayMat;
    std::cout << "New Frame" << std::endl;
//    stream1.retrieve(cameraFrame);
    stream1 >> colorMat;
    cvtColor(colorMat, grayMat, COLOR_BGR2GRAY);
    imshow("cam", grayMat);
    if (waitKey(30) >= 0)
      break;
  }
  return 0;
}
