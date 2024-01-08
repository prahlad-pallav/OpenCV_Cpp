#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <chrono>

using namespace cv;
using namespace std;

Mat imgOriginal, imgGray, imgBlur, imgCanny, imgThreshold, imgDilate, imgErode, imgWarp, imgCrop;
vector<Point> initialPoints;
vector<Point> documentPoints;

float width = 420;
float height = 596;

Mat preprocessing(Mat img) {
    
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
    Canny(imgBlur, imgCanny, 25, 75);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    
    dilate(imgCanny, imgDilate, kernel);

    return imgDilate;
}

vector<Point> getContours(Mat imgMask) {

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    // CV_EXPORTS_W void findContours( InputArray image, OutputArrayOfArrays contours, OutputArray hierarchy, int mode, int method, Point offset = Point());
    findContours(imgMask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundRect(contours.size());

    vector<Point> biggest;
    int maxArea = 0;

    for (int i = 0; i < contours.size(); i++) {
        int area = contourArea(contours[i]);
        //cout << area << endl;

        if (area > 1000) {

            float peri = arcLength(contours[i], true);
            // CV_EXPORTS_W void approxPolyDP( InputArray curve, OutputArray approxCurve, double epsilon, bool closed );
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

            if (area > maxArea && conPoly[i].size() == 4) {
                biggest = { conPoly[i][0], conPoly[i][1], conPoly[i][2], conPoly[i][3] };
                maxArea = area;
                //drawContours(imgOriginal, conPoly, i, Scalar(255, 0, 255), 5);
            }

            //drawContours(imgOriginal, conPoly, i, Scalar(255, 0, 255), 3);
            //rectangle(imgOriginal, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);

        }
    }
    return biggest;

}

void drawPoints(vector<Point> points, Scalar color) {

    for (int i = 0; i < points.size(); i++) {
        circle(imgOriginal, points[i], 8, color, FILLED);
        putText(imgOriginal, to_string(i), points[i], FONT_HERSHEY_PLAIN, 3, color, 3);
    }
}

vector<Point> reorder(vector<Point> points) {
    
    vector<Point> newPoints;
    vector<int> sumPoints, subPoints;

    for (int i = 0; i < 4; i++) {
        sumPoints.push_back(points[i].x + points[i].y);
        subPoints.push_back(points[i].x - points[i].y);
    }

    newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);
    newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);

    newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);
    newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);

    return newPoints;

}

Mat getWarp(Mat img, vector<Point> points, float width, float height) {

    Point2f src[4] = { points[0], points[1], points[2], points[3] };
    Point2f dst[4] = { {0.0f, 0.0f}, {width, 0.0f}, {0.0f, height}, {width, height} };

    Mat matrix = getPerspectiveTransform(src, dst);
    warpPerspective(img, imgWarp, matrix, Point(width, height));

    return imgWarp;
}


int main() {
   
    string path = "Resources/paper.jpg";
    imgOriginal = imread(path);

    //resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);
   
    // Preprocessing -> GrayScale -> Blur -> Canny Edge Detector -> to find all the edges

    imgThreshold = preprocessing(imgOriginal);

    // Get Contours -> Biggest rectangle in the image

    initialPoints = getContours(imgThreshold);
    //drawPoints(initialPoints, Scalar(0, 0, 255));

    // reorder 
    documentPoints = reorder(initialPoints);

    //drawPoints(documentPoints, Scalar(0, 255, 0));

    // Wrap
    imgWarp = getWarp(imgOriginal, documentPoints, width, height);

    // Crop
    int croppedVal = 5;
    Rect roi(croppedVal, croppedVal, width - (2* croppedVal), height - (2* croppedVal));
    imgCrop = imgWarp(roi);

    imshow("Image", imgOriginal);

    imshow("Threshold Image", imgThreshold);

    imshow("Image Warp", imgWarp);

    imshow("Cropped Image", imgCrop);

    waitKey(0);

    return 0;
}
