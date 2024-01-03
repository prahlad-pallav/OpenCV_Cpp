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
		Mat imgResize;

		cout << "Size of the image: " << img.size() << endl;

		// CV_EXPORTS_W void resize( InputArray src, OutputArray dst, Size dsize, double fx = 0, double fy = 0, int interpolation = INTER_LINEAR );
		resize(img, imgResize, Size(420, 420));

		cout << "Size of resized image: " << imgResize.size() << endl;

		imshow("Image", img);
		imshow("Resized Imgae", imgResize);

		waitKey(0);

		return 0;
	}
