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

		// circle
		// CV_EXPORTS_W void circle(InputOutputArray img, Point center, int radius, const Scalar& color, int thickness = 1, int lineType = LINE_8, int shift = 0);
		circle(img, Point(256, 256), 155, Scalar(0, 69, 255), FILLED);

		// rectangle
		// CV_EXPORTS_W void rectangle(InputOutputArray img, Point pt1, Point pt2, const Scalar& color, int thickness = 1, int lineType = LINE_8, int shift = 0);
		rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), FILLED);
		
		// line
		// CV_EXPORTS_W void line(InputOutputArray img, Point pt1, Point pt2, const Scalar& color, int thickness = 1, int lineType = LINE_8, int shift = 0);
		line(img, Point(130, 296), Point(382, 296), Scalar(255, 255, 255), 2);

		imshow("Image", img);

		waitKey(0);

		return 0;
	}
