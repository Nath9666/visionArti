#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

const string windowName = "Hough Circle Detection Demo";
const string cannyThresholdTrackbarName = "Canny threshold";
const string accumulatorThresholdTrackbarName = "Accumulator Threshold";

const int cannyThresholdInitialValue = 200;
const int accumulatorThresholdInitialValue = 50;
const int maxAccumulatorThreshold = 200;
const int maxCannyThreshold = 255;

void HoughDetection(const Mat& src_gray, const Mat& src_display, int cannyThreshold, int accumulatorThreshold)
{
    std::vector<Vec3f> circles;
    //Detecte les cercles
    HoughCircles( src_gray, circles, HOUGH_GRADIENT, 1, src_gray.rows/8, cannyThreshold, accumulatorThreshold, 0, 0 );

    Mat display = src_display.clone();
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        //Centre de cercle
        circle( display, center, 3, Scalar(0,255,0), -1, 8, 0 );
        //Cercle
        circle( display, center, radius, Scalar(0,0,255), 3, 8, 0 );
    }

    // shows the results
    imshow( windowName, display);
}

int main(int argc, char** argv)
{
    Mat src, src_gray;
    
    if (argc != 2)
    {
      fprintf(stderr,"USAGE : HoughCircle image\n");
      exit(0);
    }
    src = imread( *++argv, 1 );

    if( src.empty() )
    {
        fprintf(stderr, "Image non chargee \n");
        return -1;
    }
    //Convertir en gris
    cvtColor( src, src_gray, COLOR_BGR2GRAY );

    //Filtre gaussien
    GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );

    int cannyThreshold = cannyThresholdInitialValue;
    int accumulatorThreshold = accumulatorThresholdInitialValue;

    namedWindow( windowName, WINDOW_AUTOSIZE );
    createTrackbar(cannyThresholdTrackbarName, windowName, &cannyThreshold,maxCannyThreshold);
    createTrackbar(accumulatorThresholdTrackbarName, windowName, &accumulatorThreshold, maxAccumulatorThreshold);

    int key = 0;
    while(key != 'q' && key != 'Q')
    {
        cannyThreshold = std::max(cannyThreshold, 1);
        accumulatorThreshold = std::max(accumulatorThreshold, 1);

        HoughDetection(src_gray, src, cannyThreshold, accumulatorThreshold);

        key = waitKey(10);
    }

    return 0;
}
