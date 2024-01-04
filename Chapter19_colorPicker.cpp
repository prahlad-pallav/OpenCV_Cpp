// importing header files
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main() {

	VideoCapture cap(0);
	Mat img;

	Mat imgHSV, mask;

	int hmin = 0, smin = 0, vmin = 0;
	int hmax = 0, smax = 0, vmax = 0;

	namedWindow("Trackbars", (640, 200));

	createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	createTrackbar("Sat Min", "Trackbars", &smin, 255);
	createTrackbar("Sat Max", "Trackbars", &smax, 255);
	createTrackbar("Val Min", "Trackbars", &vmin, 255);
	createTrackbar("Val Max", "Trackbars", &vmax, 255);

	while (true) {

		cap.read(img);
		cvtColor(img, imgHSV, COLOR_BGR2HSV);

		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);

		//CV_EXPORTS_W void inRange(InputArray src, InputArray lowerb, InputArray upperb, OutputArray dst);
		inRange(imgHSV, lower, upper, mask);

		imshow("Image", img);
		imshow("HSV Image", imgHSV);
		imshow("Color Picker", mask);
		waitKey(1);
	}

	return 0;
}
