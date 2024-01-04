	// importing header files
	#include <opencv2/imgcodecs.hpp>
	#include <opencv2/highgui.hpp>
	#include <opencv2/imgproc.hpp>
	#include <iostream>

	using namespace cv;
	using namespace std;	


	int main() {

		string path = "Resources/lambo.png";
		Mat img = imread(path);

		Mat imgHSV, mask;

		cvtColor(img, imgHSV, COLOR_BGR2HSV);

		int hmin = 0, smin = 110, vmin = 153;
		int hmax = 19, smax = 240, vmax = 255;

		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);

		//CV_EXPORTS_W void inRange(InputArray src, InputArray lowerb, InputArray upperb, OutputArray dst);
		inRange(imgHSV, lower, upper, mask);

		imshow("Image", img);
		imshow("HSV Image", imgHSV);
		imshow("Color Detection", mask);
		waitKey(0);

		return 0;
	}
