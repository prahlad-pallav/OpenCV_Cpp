	// importing header files
	#include <opencv2/imgcodecs.hpp>
	#include <opencv2/highgui.hpp>
	#include <opencv2/imgproc.hpp>
	#include <opencv2/objdetect.hpp>
	#include <iostream>

	using namespace cv;
	using namespace std;	


	int main() {

		string path = "Resources/portrait.jpg";
		Mat img = imread(path);

		// Viola Jones Method and Haar Cascade -> Face Detection

		CascadeClassifier faceCascade;

		// Trained model for Face Detection
		faceCascade.load("Resources/haarcascade_frontalface_default.xml");
		
		// Cross check for trained xml file
		if (faceCascade.empty()) {
			cout << "XML file not found" << endl;
		}
			
		vector<Rect> faces;
		// CV_WRAP void detectMultiScale( InputArray image, CV_OUT std::vector<Rect>& objects, double scaleFactor = 1.1, int minNeighbors = 3, int flags = 0, Size minSize = Size(), Size maxSize = Size() );
		faceCascade.detectMultiScale(img, faces, 1.1, 10);

		for (int i = 0; i < faces.size(); i++) {
			rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);
		}

		imshow("Image", img);

		waitKey(0);

		return 0;
	}
