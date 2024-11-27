/* -----------------------------------------------------*/
/* Fichier  : TestEdOpenCV.cpp                          */
/* Role     : Affichage d'une Image                     */
/* Auteur   : Patrick Bonnin, (repris de la doc)        */
/*          : Cours OpenCV 2022 - OpenCV4               */
/* -----------------------------------------------------*/
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>


#include "EdStructures.h"
#include "EdLibMeanFiltering.h"
#include "DSCCvUtilities.h"

using namespace std;
using namespace cv;


int main( int argc, char** argv )
{
  Mat src, dst;
  EdIMAGE *EdSrc, *EdDst;
  int ret;
  
  if (argc == 2)
  {
    src = imread( *++argv,0); // Ouverture N&B
    cout << "Ouverture N&B : "<< *argv <<endl;
  }
  else
  {
      cout <<"DiplayImage image.XXX "<<endl;
      exit(0);
  }
  if(src.empty())
  {
       cout <<"Image Non Chargee"<<endl;
       return -1;
  }
  cout <<"Taille : "<< src.cols <<" colonnes x "<< src.rows << " lignes "<<endl;
  if (src.channels() == 1)
    cout << "Lecture N&B " <<endl;
  else if (src.channels() == 3)
    cout << "Lecture couleur " <<endl;
  else
    cout << "Probleme Lecture " <<endl;
  
  /* --- Affichage --- */
  namedWindow( "Image", WINDOW_AUTOSIZE );
  imshow( "Image", src );
  
  /* --- Creation Mat resultat --- */
  dst.create(src.rows, src.cols, CV_8U);
  
  /* --- Creation des EdIMAGE s --- */
  if (crea_IMAGE(EdSrc) == NULL)	/* creation of Image Header  */
  {
    fprintf(stderr,"Error of Memory Allocation  \n");
    exit (0);
  }
  
  if (crea_IMAGE(EdDst) == NULL)	/* creation of Image Header  */
  {
    fprintf(stderr,"Error of Memory Allocation  \n");
    exit (0);
  }
  
  EdImagefromMat (EdSrc, src);
  EdImagefromMat (EdDst, dst);
  
  /* --- Mean Filtering using 3 by 3 neighbourhood --- */
  ret = MeanFiltering (EdSrc, EdDst);
  if (ret)
  {
    fprintf(stderr,"Problem of Memory Allocation in Mean Filtering \n");
    exit(0);
  }
  
  
  /* --- Affichage --- */
  namedWindow( "Resultat", WINDOW_AUTOSIZE );
  imshow( "Resultat", dst );
  
  /* --- Attente pour fermeture --- */
  waitKey();
}
