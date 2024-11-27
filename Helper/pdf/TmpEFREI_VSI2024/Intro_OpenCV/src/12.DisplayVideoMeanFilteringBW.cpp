/* -----------------------------------------------------*/
/* Fichier  : DisplayVideoMeanFiltering.cpp             */
/* Role     : Acquisition Video d'Images + Lissage Moyen*/
/*          : realise par EdLibMeanFiltering.cpp        */
/* Auteur   : Patrick Bonnin,                           */
/*          : Cours OpenCV 2022 - OpenCV4               */
/* -----------------------------------------------------*/
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "EdStructures.h"
#include "EdLibMeanFiltering.h"
#include "DSCCvUtilities.h"

using namespace cv;
using namespace std;

/**  @function main */
int main( int argc, char** argv )
{
  Mat frame, frameBW, frameres;
  EdIMAGE *imsrc, *imres;
  int flagFirst = 1;
  int ret;
  VideoCapture cap(0); // 0 pour une seule camera
  if(!cap.isOpened())
  {
      return -1;
  }
  // Display Image
  namedWindow( "Image", WINDOW_AUTOSIZE );
  namedWindow( "Lissage", WINDOW_AUTOSIZE );
  cap.set(CAP_PROP_FRAME_WIDTH, 640);
  cap.set(CAP_PROP_FRAME_HEIGHT, 480);
  
  for(;;) // Boucle d'Acquisition
  {
    cap >> frame; // Obtenir une image de la camera
    cvtColor(frame, frameBW, COLOR_BGR2GRAY );
    if (flagFirst == 1)
    {
      flagFirst = 0;
      // Creation de l'image Mat resultat
      frameres.create(frame.rows, frame.cols, CV_8U );
      /* --- Creation of Images Header  --- */
      if (crea_IMAGE(imsrc) == NULL)	/* creation of Image Header  */
      {
        fprintf(stderr,"Error of Memory Allocation  \n");
        exit (0);
      }
      EdImagefromMat (imsrc, frameBW);
  
      if (crea_IMAGE(imres) == NULL)	/* creation of Image Header  */
      {
        fprintf(stderr,"Error of Memory Allocation  \n");
        exit (0);
      }
      EdImagefromMat (imres, frameres);
    } // fin creation strutures       
    imshow( "Image", frame );
    ret = MeanFiltering (imsrc, imres);
    if (ret)
    {
      fprintf(stderr,"Problem of Memory Allocation in Classic Threshold Procedure \n");
      exit(0);
    }
    imshow( "Lissage", frameres);
    
    if(waitKey(1) >= 0) break;
  } /* fin boucle d acquisition */
  // Wait until user exits the program
  waitKey(0);
  return 0;
}

