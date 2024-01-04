// importing header files
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;	

int main() {

	// path of the image
	string path = "Resources/lambo.png";

	// Mat -> matrix datatype introduced by opencv to handle images
	Mat img = imread(path);

	// imshow -> to show our image
	imshow("Image", img);

	// add delay, 0 for infinite
	waitKey(0);
	return 0;
}
