/* -----------------------------------------------------*/
/* Fichier  : HatThrAt.cpp                              */
/*          : Seuillage Hat avec fonction at ...        */
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

int main( int argc, char** argv )
{
  Mat src, src_gray, dst;
  int High, Low;
  unsigned char uHigh, uLow;
  int x, y;
  
  if (argc != 4)
  {
    fprintf(stderr,"InRange image High Low\n");
    exit(0);
  }
  src = imread( *++argv, 1 );
  High = atoi (*++argv);
  Low = atoi(*++argv);
  uLow = (unsigned char)Low;
  uHigh = (unsigned char)High;

  cvtColor( src, src_gray, COLOR_BGR2GRAY );

  namedWindow( "Image", WINDOW_AUTOSIZE );
  namedWindow( "Seuillage", WINDOW_AUTOSIZE );
  
  // Refaire : inRange(src_gray,Low,High,dst);
  dst.create(src.rows, src.cols, CV_8U);
  
  for(y = 0; y < src.rows; y++)
  for(x = 0; x < src.cols; x++)
  {
    if((src_gray.at<uchar>(y,x) >= uLow) && (src_gray.at<uchar>(y,x) <= uHigh))
      dst.at<uchar>(y,x) = 255;
    else
      dst.at<uchar>(y,x) = 0;
  }
  
  
  imshow("Image", src);
  imshow("Seuillage", dst);
  waitKey();

}


