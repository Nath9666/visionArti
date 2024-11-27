/* -----------------------------------------------------*/
/* Fichier  : CVEdMeanFiltering.cpp                     */
/*          : Cooperation EdEnviTI OpenCV               */
/* Role     : Filtrage Moyen NB                         */
/* Auteur   : Patrick Bonnin                            */
/*          : Cours OpenCV 2022 - OpenCV4               */
/*          : Doc OpenCV + Adaptations personnelles     */
/*          : Traitements Elementaires                  */
/* -----------------------------------------------------*/
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "EdStructures.h"
#include "EdLibMeanFiltering.h"
#include "DSCCvUtilities.h"


using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
  Mat src, res;
  EdIMAGE *imsrc, *imres;
  int ret;
  
  if (argc != 2)
  {
    fprintf(stderr,"CVEdMEanFiltering image \n");
    exit(0);
  }
  
  namedWindow( "Origine", WINDOW_AUTOSIZE );
  namedWindow( "Moyenne", WINDOW_AUTOSIZE );
  
  src = imread( *++argv,0);
  if(src.empty())
    return -1;
  // Au cas ou !
  if (src.isContinuous() != 1)
  {
    cout << "Arret du traitement : Segmentation de l'espace memoire "<<endl;
    exit(0);
  }
  
  imshow("Origine", src);
  
  // Creation de l'image Mat resultat
  res.create(src.rows, src.cols, CV_8U );
  
  /* --- Creation of Images Header  --- */
  if (crea_IMAGE(imsrc) == NULL)	/* creation of Image Header  */
  {
    fprintf(stderr,"Error of Memory Allocation  \n");
    exit (0);
  }
  EdImagefromMat (imsrc, src);
  
  if (crea_IMAGE(imres) == NULL)	/* creation of Image Header  */
  {
    fprintf(stderr,"Error of Memory Allocation  \n");
    exit (0);
  }
  EdImagefromMat (imres, res);
  
  ret = MeanFiltering (imsrc, imres);
  if (ret)
  {
    fprintf(stderr,"Problem of Memory Allocation in Classic Threshold Procedure \n");
    exit(0);
  }
  imshow("Moyenne", res);
  waitKey();

}


