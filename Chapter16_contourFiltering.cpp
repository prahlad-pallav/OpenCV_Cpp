	// importing header files
	#include <opencv2/imgcodecs.hpp>
	#include <opencv2/highgui.hpp>
	#include <opencv2/imgproc.hpp>
	#include <iostream>

	using namespace cv;
	using namespace std;	

	void getContours(Mat imgDilate, Mat img) {

		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;

		// CV_EXPORTS_W void findContours( InputArray image, OutputArrayOfArrays contours, OutputArray hierarchy, int mode, int method, Point offset = Point());
		findContours(imgDilate, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

		// Filtering of noise based on Area, if Area < Threshold -> ignore
		for (int i = 0; i < contours.size(); i++) {
			int area = contourArea(contours[i]);
			//cout << area << endl;

			if (area > 1000) {
				// CV_EXPORTS_W void drawContours( InputOutputArray image, InputArrayOfArrays contours, int contourIdx, const Scalar& color, int thickness = 1, int lineType = LINE_8, InputArray hierarchy = noArray(), int maxLevel = INT_MAX, Point offset = Point() );
				drawContours(img, contours, i, Scalar(255, 0, 255), 3);
			}
		}

	}

	int main() {

		string path = "Resources/shapes.png";
		Mat img = imread(path);
		Mat imgGray, imgBlur, imgCanny, imgDilate;

		// Image Preprocessing
		cvtColor(img, imgGray, COLOR_BGR2GRAY);
		GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
		Canny(imgBlur, imgCanny, 25, 75);
		Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
		dilate(imgCanny, imgDilate, kernel);

		getContours(imgDilate, img);

		imshow("Image", img);
		/*imshow("GrayScale Image", imgGray);
		imshow("Blurred Image", imgBlur);
		imshow("Canny Image", imgCanny);
		imshow("Dilate Image", imgDilate);*/
		waitKey(0);

		return 0;
	}
