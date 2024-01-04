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


		vector<vector<Point>> conPoly(contours.size());
		vector<Rect> boundRect(contours.size());
		string objectType;
		
		for (int i = 0; i < contours.size(); i++) {
			int area = contourArea(contours[i]);
			//cout << area << endl;

			if (area > 1000) {
				
				float peri = arcLength(contours[i], true);
				// CV_EXPORTS_W void approxPolyDP( InputArray curve, OutputArray approxCurve, double epsilon, bool closed );
				approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

				cout << conPoly[i].size() << endl;

				boundRect[i] = boundingRect(conPoly[i]);
				

				int objCorner = (int)conPoly[i].size();

				if (objCorner == 3) {
					objectType = "Triangle";
				}
				else if (objCorner == 4) {

					float aspectRatio = (float)boundRect[i].width / (float)boundRect[i].height;
					if (aspectRatio > 0.95 && aspectRatio < 1.05) {
						objectType = "Square";
					}
					else {
						objectType = "Rectangle";
					}
				}
				else {
					objectType = "Circle";
				}

				drawContours(img, conPoly, i, Scalar(255, 0, 255), 3);
				rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);

				putText(img, objectType, { boundRect[i].x, boundRect[i].y - 5 }, FONT_HERSHEY_PLAIN, 1.0, Scalar(0, 69, 255), 1);
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
