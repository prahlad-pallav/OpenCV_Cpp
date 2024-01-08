// importing header files
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main() {

	VideoCapture cap(0);
	Mat img;
	// Viola Jones Method and Haar Cascade -> Face Detection

	CascadeClassifier plateCascade;

	// Trained model for Face Detection
	plateCascade.load("Resources/haarcascade_russian_plate_number.xml");

	// Cross check for trained xml file
	if (plateCascade.empty()) {
		cout << "XML file not found" << endl;
	}

	vector<Rect> plates;

	while (true) {
		cap.read(img);

		// CV_WRAP void detectMultiScale( InputArray image, CV_OUT std::vector<Rect>& objects, double scaleFactor = 1.1, int minNeighbors = 3, int flags = 0, Size minSize = Size(), Size maxSize = Size() );
		plateCascade.detectMultiScale(img, plates, 1.1, 10);

		for (int i = 0; i < plates.size(); i++) {
			Mat imgCrop = img(plates[i]);
			//imshow(to_string(i), imgCrop);
			imwrite("Resources/Plates/" + to_string(i)+".png", imgCrop);
			rectangle(img, plates[i].tl(), plates[i].br(), Scalar(255, 0, 255), 3);

		}

		imshow("Image", img);

		waitKey(1);
	}
	return 0;
}	
