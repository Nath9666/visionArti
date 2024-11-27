/* -----------------------------------------------------*/
/* Fichier  : DisplayVideoInRangeBW.cpp                 */
/* Role     : Acquisition Video d'Images + class HSV    */
/*          : avec reglages parametres                  */
/* Auteur   : Patrick Bonnin,                           */
/*          : Cours OpenCV 2022 - OpenCV4               */
/* -----------------------------------------------------*/
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int highH, highS, highV ;
int lowH, lowS, lowV;

void LowH (int, void* );
void HighH (int, void* );
void LowS (int, void* );
void HighS (int, void* );
void LowV (int, void* );
void HighV (int, void* );

/**  @function main */
int main( int argc, char** argv )
{
  Mat frame, frameHSV, frameres;
  VideoCapture cap(0); // 0 pour une seule camera
  if(!cap.isOpened())
  {
      return -1;
  }
  // Display Image
  namedWindow( "Image", WINDOW_AUTOSIZE );
  namedWindow( "InRangeHSV", WINDOW_AUTOSIZE );
  namedWindow( "Reglage", WINDOW_AUTOSIZE );

  createTrackbar( "LOW_H", "Reglage", &lowH, 255, LowH );
  createTrackbar( "HIGH_H", "Reglage", &highH, 255, HighH );
  setTrackbarMax ("LOW_H", "Reglage", 255);
  setTrackbarMin ("LOW_H", "Reglage", 0);
  setTrackbarPos ("LOW_H", "Reglage", 0);
  setTrackbarMax ("HIGH_H", "Reglage", 255);
  setTrackbarMin ("HIGH_H", "Reglage", 0);
  setTrackbarPos ("HIGH_H", "Reglage", 255);

  createTrackbar( "LOW_S", "Reglage", &lowS, 255, LowS );
  createTrackbar( "HIGH_S", "Reglage", &highS, 255, HighS );
  setTrackbarMax ("LOW_S", "Reglage", 255);
  setTrackbarMin ("LOW_S", "Reglage", 0);
  setTrackbarPos ("LOW_S", "Reglage", 0);
  setTrackbarMax ("HIGH_S", "Reglage", 255);
  setTrackbarMin ("HIGH_S", "Reglage", 0);
  setTrackbarPos ("HIGH_S", "Reglage", 255);

createTrackbar( "LOW_V", "Reglage", &lowV, 255, LowV );
  createTrackbar( "HIGH_V", "Reglage", &highV, 255, HighV );
  setTrackbarMax ("LOW_V", "Reglage", 255);
  setTrackbarMin ("LOW_V", "Reglage", 0);
  setTrackbarPos ("LOW_V", "Reglage", 0);
  setTrackbarMax ("HIGH_V", "Reglage", 255);
  setTrackbarMin ("HIGH_V", "Reglage", 0);
  setTrackbarPos ("HIGH_V", "Reglage", 255);


  cap.set(CAP_PROP_FRAME_WIDTH, 640);
  cap.set(CAP_PROP_FRAME_HEIGHT, 480);
  
  for(;;) // Boucle d'Acquisition
  {
    cap >> frame; // Obtenir une image de la camera        
    imshow( "Image", frame );
    cvtColor( frame, frameHSV, COLOR_BGR2HSV );
    inRange(frameHSV,Scalar(lowH, lowS, lowV), Scalar(highH,highS, highV), frameres);
    imshow( "InRangeHSV", frameres);
    
    if(waitKey(1) >= 0) break;
  }
  // Wait until user exits the program
  waitKey(0);
  return 0;
}

/* --- HUE--- */
void LowH (int, void* )
{
  if (lowH > highH)
  {
    highH = lowH;
    setTrackbarPos ("HIGH_H", "Reglage", highH);
  }
}
void HighH (int, void* )
{
  if (highH < lowH)
  {
    lowH = highH;
    setTrackbarPos ("LOW_H", "Reglage", lowH);
  }
}
/* --- SATURATION --- */
void LowS (int, void* )
{
  if (lowS > highS)
  {
    highS = lowS;
    setTrackbarPos ("HIGH_S", "Reglage", highS);
  }
}
void HighS (int, void* )
{
  if (highS < lowS)
  {
    lowS = highS;
    setTrackbarPos ("LOW_S", "Reglage", lowS);
  }
}
/* --- VALUE--- */
void LowV (int, void* )
{
  if (lowV > highV)
  {
    highV = lowV;
    setTrackbarPos ("HIGH_V", "Reglage", highV);
  }
}
void HighV (int, void* )
{
  if (highV < lowV)
  {
    lowV = highV;
    setTrackbarPos ("LOW_V", "Reglage", lowV);
  }
}



