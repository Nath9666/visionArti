/* -----------------------------------------------------*/
/* Fichier  : DisplayVide.cpp                           */
/* Role     : Acquisition Video d'Images                */
/* Auteur   : Patrick Bonnin, (repris de la doc)        */
/*          : Cours OpenCV 2022 - OpenCV4               */
/* -----------------------------------------------------*/
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

/**  @function main */
int main( int argc, char** argv )
{
  Mat frame;
  VideoCapture cap(0); // 0 pour une seule camera
  if(!cap.isOpened())
  {
      return -1;
  }
  // Display Image
  namedWindow( "Image", WINDOW_AUTOSIZE );
  cap.set(CAP_PROP_FRAME_WIDTH, 640);
  cap.set(CAP_PROP_FRAME_HEIGHT, 480);
  
  for(;;) // Boucle d'Acquisition
  {
    cap >> frame; // Obtenir une image de la camera        
    imshow( "Image", frame );
    if(waitKey(1) >= 0) break;
  }
  // Wait until user exits the program
  waitKey(0);
  return 0;
}

