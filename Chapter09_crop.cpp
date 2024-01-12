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
		Mat imgCrop;

		// Rect -> Rectangle data structure, roi -> Region of interest.
		Rect roi(100, 100, 300, 250);
		imgCrop = img(roi);
		
		imshow("Image", img);
		imshow("Cropped image", imgCrop);

		waitKey(0);

		return 0;
	}
