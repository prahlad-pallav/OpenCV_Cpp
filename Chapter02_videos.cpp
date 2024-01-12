// importing header files
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;	

int main() {

  // path of the video
  string path = "Resources/test_video.mp4";
	
  // videoCapture object
  VideoCapture cap(path);

	Mat img;

	while (true) {
		cap.read(img);
		imshow("Image", img);
		// add delay of 20 milliseconds
    waitKey(20);
	}

	return 0;
}
