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

	// CV_EXPORTS_W void GaussianBlur( InputArray src, OutputArray dst, Size ksize, double sigmaX, double sigmaY = 0, int borderType = BORDER_DEFAULT );
	GaussianBlur(img, imgBlur, Size(7, 7), 5, 0);

	imshow("Image", img);
	imshow("GaussianBlur Image", imgBlur);

	waitKey(0);

	return 0;
}
