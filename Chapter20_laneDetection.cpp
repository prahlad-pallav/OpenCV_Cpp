#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void draw_lines_on_image(Mat& image, vector<Vec4i>& lines) {

    // create a distinct image for the lines [0, 255] 
    Mat lines_image = Mat::zeros(image.size(), CV_8UC3);

    // (x1, x2) -> starting and end point of the line
    // (y1, y2) -> starting and end point of the line
    for (const Vec4i& line : lines) {
        int x1 = line[0];
        int y1 = line[1];
        int x2 = line[2];
        int y2 = line[3];

        // CV_EXPORTS_W void line(InputOutputArray img, Point pt1, Point pt2, const Scalar& color, int thickness = 1, int lineType = LINE_8, int shift = 0);
        cv::line(lines_image, Point(x1, y1), Point(x2, y2), Scalar(0, 0, 255), 3);
    }

    // merge the image with the lines
    // CV_EXPORTS_W void addWeighted(InputArray src1, double alpha, InputArray src2, double beta, double gamma, OutputArray dst, int dtype = -1);
    addWeighted(image, 1.0, lines_image, 1, 0.0, image);
}

Mat region_of_interest(const Mat& image, const vector<Point>& region_points) {
    Mat mask = Mat::zeros(image.size(), CV_8U);
    // CV_EXPORTS_W void fillPoly(InputOutputArray img, InputArrayOfArrays pts, const Scalar& color, int lineType = LINE_8, int shift = 0, Point offset = Point() );
    fillPoly(mask, vector<vector<Point>>{region_points}, Scalar(255));

    Mat masked_image;

    // CV_EXPORTS_W void bitwise_and(InputArray src1, InputArray src2, OutputArray dst, InputArray mask = noArray());
    bitwise_and(image, image, masked_image, mask);
    return masked_image;
}

Mat get_detected_lanes(const Mat& image) {
    
    Mat gray_image, canny_image;

    // Turn each frame into grayscale format
    cvtColor(image, gray_image, COLOR_BGR2GRAY);
    
    // Edge detection kernel -> Canny's algorithm
    // CV_EXPORTS_W void Canny( InputArray image, OutputArray edges, double threshold1, double threshold2, int apertureSize = 3, bool L2gradient = false );
    Canny(gray_image, canny_image, 90, 120);

   // return canny_image;

    // height of each frame
    int height = image.rows;
    // width of each frame
    int width = image.cols;


    // only interested in the lower region of the image -> driving lanes.
    // triangular regions -> 3 points -> bottom left, middle, bottom right.
    vector<Point> region_of_interest_vertices = {
        Point(0, height),
        Point(width / 2, height * 0.6),
        Point(width, height)
    };

    Mat cropped_image = region_of_interest(canny_image, region_of_interest_vertices);
    //return cropped_image;


    vector<Vec4i> lines;
    // lines detection algorithms -> Hough Transformation
    // CV_EXPORTS_W void HoughLinesP( InputArray image, OutputArray lines, double rho, double theta, int threshold, double minLineLength = 0, double maxLineGap = 0 );
   
    /*dst: Output of the edge detector.It should be a grayscale image(although in fact it is a binary one)
    lines : A vector that will store the parameters(xstart, ystart, xend, yend) of the detected lines
    rho : The resolution of the parameter r in pixels.We use 1 pixel.
    theta : The resolution of the parameter θ in radians.We use 1 degree(CV_PI / 180)
    threshold : The minimum number of intersections to "*detect*" a line
    minLineLength : The minimum number of points that can form a line.Lines with less than this number of points are disregarded.
    maxLineGap : The maximum gap between two points to be considered in the same line.*/

    HoughLinesP(cropped_image, lines, 1, CV_PI / 180, 50, 40, 150);

    // draw the lines on image
    draw_lines_on_image(const_cast<Mat&>(image), lines);

    return image;
}

int main() {
    // capturing of video
    VideoCapture video("Resources/lane_detection_video.mp4");

    // till the end of the video
    while (video.isOpened()) {
        Mat frame;
        bool is_grabbed = video.read(frame);

        // frame is grabbed or not
        if (!is_grabbed) {
            break;
        }

        frame = get_detected_lanes(frame);

        // shows the frame one by one
        imshow("Lane Detection Video", frame);
        waitKey(10);
    }

    video.release();
    destroyAllWindows();

    return 0;
}
