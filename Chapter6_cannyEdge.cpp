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
	Mat imgBlur;
	Mat imgCanny;

	// CV_EXPORTS_W void GaussianBlur( InputArray src, OutputArray dst, Size ksize, double sigmaX, double sigmaY = 0, int borderType = BORDER_DEFAULT );
	GaussianBlur(img, imgBlur, Size(7, 7), 5, 0);

	// Before using Canny edge detector, it is common practise to use blur effect before it.
	// CV_EXPORTS_W void Canny( InputArray image, OutputArray edges, double threshold1, double threshold2, int apertureSize = 3, bool L2gradient = false );
	Canny(imgBlur, imgCanny, 50, 150);

	imshow("Image", img);
	imshow("GaussianBlur Image", imgBlur);
	imshow("Canny Edge Detector Image", imgCanny);

	waitKey(0);

	return 0;
}
