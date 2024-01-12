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
	Mat imgGray;

  // convert BGR to GRAY
	cvtColor(img, imgGray, COLOR_BGR2GRAY);

	imshow("Image", img);
	imshow("GrayScale Image", imgGray);

	waitKey(0);

	return 0;
}
