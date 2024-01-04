	// importing header files
	#include <opencv2/imgcodecs.hpp>
	#include <opencv2/highgui.hpp>
	#include <opencv2/imgproc.hpp>
	#include <iostream>

	using namespace cv;
	using namespace std;	

	int main() {

		// (255, 255, 255) -> White
		Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255));

		circle(img, Point(256, 256), 155, Scalar(0, 69, 255), FILLED);
		rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), FILLED);
		line(img, Point(130, 296), Point(382, 296), Scalar(255, 255, 255), 2);

		// text
		putText(img, "Prahlad Pallav", Point(137, 262), FONT_HERSHEY_SCRIPT_COMPLEX, 1.15, Scalar(0, 69, 255), 2);

		imshow("Image", img);

		waitKey(0);

		return 0;
	}
