// importing header files
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;	

int main() {

	// 0 -> camera id -> single camera
	VideoCapture cap(0);
	Mat img;

	while (true) {

		cap.read(img);
		imshow("Image", img);
		waitKey(1);
	}

	return 0;
}
