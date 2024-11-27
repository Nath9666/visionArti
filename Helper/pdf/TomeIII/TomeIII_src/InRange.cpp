/* -----------------------------------------------------*/
/* Fichier  : InRange.cpp                               */
/* Role     : Seuillage Hat d'une Image NB              */
/* Auteur   : Patrick Bonnin                            */
/*          : Cours OpenCV 2022 - OpenCV4               */
/*          : Doc OpenCV + Adaptations personnelles     */
/*          : Traitements Elementaires                  */
/* -----------------------------------------------------*/
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

int high = 255;
int low = 4;

Mat src, src_gray, dst;
void inRangeDemo( int, void* );
void Low (int, void* );
void High (int, void* );

int main( int argc, char** argv )
{
  if (argc != 2)
  {
    fprintf(stderr,"InRange image\n");
    exit(0);
  }
  src = imread( *++argv, 1 );
  cvtColor( src, src_gray, COLOR_BGR2GRAY );

  namedWindow( "Image", WINDOW_AUTOSIZE );
  namedWindow( "Seuillage", WINDOW_AUTOSIZE );
 
  createTrackbar( "LOW", "Image", &low, 255, Low );
  createTrackbar( "HIGH", "Image", &high, 255, High );
  setTrackbarMax ("LOW", "Image", 255);
  setTrackbarMin ("LOW", "Image", 0);
  setTrackbarPos ("LOW", "Image", 0);
  setTrackbarMax ("HIGH", "Image", 255);
  setTrackbarMin ("HIGH", "Image", 0);
  setTrackbarPos ("HIGH", "Image", 255);
  imshow( "Image", src );
  inRangeDemo( 0, 0 );
  waitKey();
}

void Low (int, void* )
{
  if (low > high)
  {
    high = low;
    setTrackbarPos ("HIGH", "Image", high);
  }
  inRangeDemo( 0, 0 );
}
void High (int, void* )
{
  if (high < low)
  {
    low = high;
    setTrackbarPos ("LOW", "Image", low);
  }
  inRangeDemo( 0, 0 );
}
void inRangeDemo( int, void* )
{
    inRange(src_gray,low,high,dst);
    imshow("Seuillage", dst);
}

