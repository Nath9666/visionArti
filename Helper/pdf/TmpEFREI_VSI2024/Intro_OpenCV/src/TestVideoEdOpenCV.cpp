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
#include <stdlib.h>

#include "EdStructures.h"
#include "EdLibMeanFiltering.h"
#include "DSCCvUtilities.h"

using namespace cv;
using namespace std;

int flagFirst = TRUE;

/**  @function main */
int main( int argc, char** argv )
{
  Mat frame, frame_gray, frameDst;
  EdIMAGE *EdFrame, *EdFrameDst;
  int ret;
    
  VideoCapture cap(0); // 0 pour une seule camera
  if(!cap.isOpened())
  {
      return -1;
  }
  // Display Image
  namedWindow( "Image", WINDOW_AUTOSIZE );
  namedWindow( "Image_Gray", WINDOW_AUTOSIZE );
  namedWindow( "Resultat", WINDOW_AUTOSIZE );
  cap.set(CAP_PROP_FRAME_WIDTH, 640);
  cap.set(CAP_PROP_FRAME_HEIGHT, 480);
  
  for(;;) // Boucle d'Acquisition
  {
    cap >> frame; // Obtenir une image de la camera        
    imshow( "Image", frame );
    
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    imshow( "Image_Gray", frame_gray );

    if (flagFirst)
    {
      flagFirst = FALSE;
      
      /* --- Creation Mat resultat --- */
      frameDst.create(frame.rows, frame.cols, CV_8U);
  
      /* --- Creation des EdIMAGE s --- */
      if (crea_IMAGE(EdFrame) == NULL)	/* creation of Image Header  */
      {
        fprintf(stderr,"Error of Memory Allocation  \n");
        exit (0);
      }
  
      if (crea_IMAGE(EdFrameDst) == NULL)	/* creation of Image Header  */
      {
        fprintf(stderr,"Error of Memory Allocation  \n");
        exit (0);
      }
  
      EdImagefromMat (EdFrame, frame_gray);
      EdImagefromMat (EdFrameDst, frameDst);
    } /* end of firts image */
    /* --- Mean Filtering using 3 by 3 neighbourhood --- */
    ret = MeanFiltering (EdFrame, EdFrameDst);
    if (ret)
    {
      fprintf(stderr,"Problem of Memory Allocation in Mean Filtering \n");
      exit(0);
    }
    imshow( "Resultat", frameDst );   
    if(waitKey(1) >= 0) break;
  }
  // Wait until user exits the program
  waitKey(0);
  return 0;
}

