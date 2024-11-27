/* -----------------------------------------------------*/
/* Fichier  : DisplayVideoInRangeBW.cpp                 */
/* Role     : Acquisition Video d'Images + Seuillage Hat*/
/*          : avec reglages parametres                  */
/* Auteur   : Patrick Bonnin,         */
/*          : Cours OpenCV 2022 - OpenCV4               */
/* -----------------------------------------------------*/
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int high = 255;
int low = 4;

void Low (int, void* );
void High (int, void* );

/**  @function main */
int main( int argc, char** argv )
{
  Mat frame, frameBW, frameres;
  VideoCapture cap(0); // 0 pour une seule camera
  if(!cap.isOpened())
  {
      return -1;
  }
  // Display Image
  namedWindow( "Image", WINDOW_AUTOSIZE );
  namedWindow( "InRange", WINDOW_AUTOSIZE );
  createTrackbar( "LOW", "Image", &low, 255, Low );
  createTrackbar( "HIGH", "Image", &high, 255, High );
  setTrackbarMax ("LOW", "Image", 255);
  setTrackbarMin ("LOW", "Image", 0);
  setTrackbarPos ("LOW", "Image", 0);
  setTrackbarMax ("HIGH", "Image", 255);
  setTrackbarMin ("HIGH", "Image", 0);
  setTrackbarPos ("HIGH", "Image", 255);
  cap.set(CAP_PROP_FRAME_WIDTH, 640);
  cap.set(CAP_PROP_FRAME_HEIGHT, 480);
  
  for(;;) // Boucle d'Acquisition
  {
    cap >> frame; // Obtenir une image de la camera        
    imshow( "Image", frame );
    cvtColor( frame, frameBW, COLOR_BGR2GRAY );
    inRange(frameBW,low,high,frameres);
    imshow( "InRange", frameres);
    
    if(waitKey(1) >= 0) break;
  }
  // Wait until user exits the program
  waitKey(0);
  return 0;
}
void Low (int, void* )
{
  if (low > high)
  {
    high = low;
    setTrackbarPos ("HIGH", "Image", high);
  }
}
void High (int, void* )
{
  if (high < low)
  {
    low = high;
    setTrackbarPos ("LOW", "Image", low);
  }
}

