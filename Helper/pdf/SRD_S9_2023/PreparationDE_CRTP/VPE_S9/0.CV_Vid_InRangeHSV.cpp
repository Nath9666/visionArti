/* -----------------------------------------------------*/
/* Fichier  : InRangeHSV.cpp                            */
/* Role     : Seuillage parallelepipedique HSV          */
/* Auteur   : Patrick Bonnin                            */
/*          : Cours OpenCV 2022 - OpenCV4               */
/*          : Traitements Elementaires                  */
/* -----------------------------------------------------*/
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

int high_h = 179, low_h = 0;
int high_s = 255, low_s = 0;
int high_v = 255, low_v = 0;

Mat src, src_hls, dst;

void inRangeDemo( int, void* );
void Low_h (int, void* );
void High_h (int, void* );

void Low_s (int, void* );
void High_s (int, void* );

void Low_v (int, void* );
void High_v (int, void* );



int main( int argc, char** argv )
{
  
  namedWindow( "Image", WINDOW_AUTOSIZE );
  namedWindow( "Seuillage", WINDOW_AUTOSIZE );

  createTrackbar( "HUE low",
                  "Image", &low_h,
                  179, Low_h );

  createTrackbar( "HUE high",
                  "Image", &high_h,
                  179, High_h );
        
  createTrackbar( "SATURATION low",
                  "Image", &low_s,
                  255, Low_s );

  createTrackbar( "SATURATION high",
                  "Image", &high_s,
                  255, High_s );
  
  createTrackbar( "VALUE low",
                  "Image", &low_v,
                  255, Low_v );

  createTrackbar( "VALUE high",
                  "Image", &high_v,
                  255, High_v );
                  
  setTrackbarMax ("HUE low", "Image", 179);
  setTrackbarMin ("HUE low", "Image", 0);
  setTrackbarPos ("HUE low", "Image", 0);
  setTrackbarMax ("HUE high", "Image", 179);
  setTrackbarMin ("HUE high", "Image", 0);
  setTrackbarPos ("HUE high", "Image", 255);
  
  setTrackbarMax ("SATURATION low", "Image", 255);
  setTrackbarMin ("SATURATION low", "Image", 0);
  setTrackbarPos ("SATURATION low", "Image", 0);
  setTrackbarMax ("SATURATION high", "Image", 255);
  setTrackbarMin ("SATURATION high", "Image", 0);
  setTrackbarPos ("SATURATION high", "Image", 255);
  
  setTrackbarMax ("VALUE low", "Image", 255);
  setTrackbarMin ("VALUE low", "Image", 0);
  setTrackbarPos ("VALUE low", "Image", 0);
  setTrackbarMax ("VALUE high", "Image", 255);
  setTrackbarMin ("VALUE high", "Image", 0);
  setTrackbarPos ("VALUE high", "Image", 255);
  
  VideoCapture cap(0); // 0 pour une seule camera
  if(!cap.isOpened())
  {
      return -1;
  }
  
  for(;;) // Boucle d'Acquisition
  {
    cap >> src; // Obtenir une image de la camera 
    cvtColor(src, src_hls, COLOR_BGR2HSV);       
    inRangeDemo( 0, 0 );
    if(waitKey(1) >= 0) break;
  }
  
  waitKey();

}

void Low_h (int, void* )
{
  if (low_h > high_h)
  {
    high_h = low_h;
    setTrackbarPos ("HUE high", "Image", high_h);
  }
  
}
void High_h (int, void* )
{
  if (high_h < low_h)
  {
    low_h = high_h;
    setTrackbarPos ("HUE low", "Image", low_h);
  }
  
}

void Low_s(int, void* )
{
  if (low_s > high_s)
  {
    high_s = low_s;
    setTrackbarPos ("SATURATION high", "Image", high_s);
  }
  
}
void High_s (int, void* )
{
  if (high_s < low_s)
  {
    low_s = high_s;
    setTrackbarPos ("SATURATION low", "Image", low_s);
  }
  
}

void Low_v (int, void* )
{
  if (low_v > high_v)
  {
    high_v = low_v;
    setTrackbarPos ("VALUE high", "Image", high_v);
  }
  
}
void High_v (int, void* )
{
  if (high_v < low_v)
  {
    low_v = high_v;
    setTrackbarPos ("VALUE low", "Image", low_v);
  }
  
}


void inRangeDemo( int, void* )
{
    inRange(src_hls,Scalar(low_h, low_s, low_v),Scalar(high_h, high_s, high_v),dst);
    imshow( "Image", src );
    imshow("Seuillage", dst);
}
