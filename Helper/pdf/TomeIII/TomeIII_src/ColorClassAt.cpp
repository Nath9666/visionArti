/* -----------------------------------------------------*/
/* Fichier  : ColorClassAt.cpp                          */
/*          : Classification Couleur avec fonction at ..*/
/* Role     : généralisation duSeuillage Hat            */
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
  Mat src, dst;
  int High, Low;
  unsigned char uHighB, uLowB, uHighG, uLowG, uHighR, uLowR;
  int x, y;
  
  if (argc != 8)
  {
    fprintf(stderr,"InRange image HighB LowB .. G, R\n");
    exit(0);
  }
  src = imread( *++argv, 1 );
  High = atoi (*++argv);
  Low = atoi(*++argv);
  uLowB = (unsigned char)Low;
  uHighB = (unsigned char)High;
  
  High = atoi (*++argv);
  Low = atoi(*++argv);
  uLowG = (unsigned char)Low;
  uHighG = (unsigned char)High;
  
  High = atoi (*++argv);
  Low = atoi(*++argv);
  uLowR = (unsigned char)Low;
  uHighR = (unsigned char)High;

  namedWindow( "Image", WINDOW_AUTOSIZE );
  namedWindow( "Seuillage", WINDOW_AUTOSIZE );
  
  // Refaire : inRange(src_gray,Low,High,dst);
  dst.create(src.rows, src.cols, CV_8U);
  
  for(y = 0; y < src.rows; y++)
  for(x = 0; x < src.cols; x++)
  {
    if((src.at<cv::Vec3b>(y,x)[0] >= uLowB) && (src.at<cv::Vec3b>(y,x)[0] <= uHighB)
        && (src.at<cv::Vec3b>(y,x)[1] >= uLowG) && (src.at<cv::Vec3b>(y,x)[1] <= uHighG)
        && (src.at<cv::Vec3b>(y,x)[2] >= uLowR) && (src.at<cv::Vec3b>(y,x)[2] <= uHighR))
      dst.at<uchar>(y,x) = 255;
    else
      dst.at<uchar>(y,x) = 0;
  }
  
  
  imshow("Image", src);
  imshow("Seuillage", dst);
  waitKey();

}


