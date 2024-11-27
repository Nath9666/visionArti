// Complements de HoughLine First
// Possibilite de Reglage du Canny
// Amelioration de la Visualisation
// Patrick Bonnin 15/11/2019
//
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

Mat src, edges;
Mat src_gray;
Mat standard_hough, probabilistic_hough;

int min_threshold = 10;
int max_trackbar = 150;
int minCanny = 50;
int maxCanny = 350;

const char* standard_name = "Standard Hough Lines Demo";
const char* probabilistic_name = "Probabilistic Hough Lines Demo";

int s_trackbar = max_trackbar;
int p_trackbar = max_trackbar;

void NewCanny( int, void* );
void Standard_Hough( int, void* );
void Probabilistic_Hough( int, void* );

int main( int argc, char** argv )
{
   if (argc != 2)
   {
       fprintf(stderr,"USAGE : HoughLine image \n");
       exit(0);
   }
   /// Read the image
   src = imread( *++argv, 1 );

   if( src.empty() )
     {
       return -1;
     }
   
   /// Pass the image to gray
   cvtColor( src, src_gray, COLOR_RGB2GRAY );

   namedWindow( "Image", WINDOW_AUTOSIZE );
   imshow("Image",src);
   
   namedWindow( "Canny", WINDOW_AUTOSIZE );
   createTrackbar( "MinTh", "Canny", &minCanny, 600, NewCanny);
   createTrackbar( "MaxTh", "Canny", &maxCanny, 600, NewCanny);
   NewCanny(0,0);
   
   waitKey();
   destroyWindow("Canny");
   
   /// Create Trackbars for Thresholds
   char thresh_label[50];
   sprintf( thresh_label, "Thres: %d + input", min_threshold );
   
   namedWindow( standard_name, WINDOW_AUTOSIZE );
   createTrackbar( thresh_label, standard_name, &s_trackbar, max_trackbar, Standard_Hough);

   namedWindow( probabilistic_name, WINDOW_AUTOSIZE );
   createTrackbar( thresh_label, probabilistic_name, &p_trackbar, max_trackbar, Probabilistic_Hough);

   /// Initialize
   Standard_Hough(0, 0);
   Probabilistic_Hough(0, 0);
   
   waitKey(0);
   return 0;
}

void NewCanny( int, void* )
{
    /// Apply Canny edge detector
    Canny( src_gray, edges, minCanny, maxCanny );
    imshow("Canny",edges);
}

void Standard_Hough( int, void* )
{
  vector<Vec2f> s_lines;
  cvtColor( src_gray, standard_hough, COLOR_GRAY2BGR );

  /// 1. Use Standard Hough Transform
  HoughLines( edges, s_lines, 1, CV_PI/180, min_threshold + s_trackbar, 0, 0 );

  /// Show the result
  cout<<"New Houghlines"<<endl;
  for( size_t i = 0; i < s_lines.size(); i++ )
     {
      float r = s_lines[i][0], t = s_lines[i][1];
      double cos_t = cos(t), sin_t = sin(t);
      double x0 = r*cos_t, y0 = r*sin_t;
      double alpha = 1000;

       Point pt1( cvRound(x0 + alpha*(-sin_t)), cvRound(y0 + alpha*cos_t) );
       Point pt2( cvRound(x0 - alpha*(-sin_t)), cvRound(y0 - alpha*cos_t) );
       line( standard_hough, pt1, pt2, Scalar(0,0,255), 1, LINE_AA);
       cout << "r = "<<r<<"   theta = "<<t<<endl;
     }

   imshow( standard_name, standard_hough );
}

void Probabilistic_Hough( int, void* )
{
  vector<Vec4i> p_lines;
  cvtColor( src_gray, probabilistic_hough, COLOR_GRAY2BGR );

  /// 2. Use Probabilistic Hough Transform
  HoughLinesP(edges, p_lines, 1, CV_PI/180, min_threshold + p_trackbar, 30, 10 );

  /// Show the result
  cout<<"New HoughlinesP"<<endl;
  for( size_t i = 0; i < p_lines.size(); i++ )
     {
       Vec4i l = p_lines[i];
       line( probabilistic_hough, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 1, LINE_AA);
       cout << "Ligne "<<i<<endl;
     }

   imshow( probabilistic_name, probabilistic_hough );
}
