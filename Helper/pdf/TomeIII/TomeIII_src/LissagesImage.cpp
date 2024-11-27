/* -----------------------------------------------------*/
/* Fichier  : LissagesImage.cpp                         */
/* Role     : Lissages d'une Image                      */
/* Auteur   : Patrick Bonnin, (repris de la doc)        */
/*          : Cours OpenCV 2022 - OpenCV4               */
/* -----------------------------------------------------*/
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace std;
using namespace cv;


int main( int argc, char** argv )
{
  Mat src, moy, gauss, med;
  if (argc == 2)
  {
    src = imread( *++argv); // Ouverture Couleur
    cout << "Ouverture couleur : "<< *argv <<endl;
  }
  else if (argc == 3)
  {
    src = imread( *++argv, 0); // Ouverture N&B
    cout << "Ouverture N&B : "<< *argv <<endl;
  }
  else
  {
      cout <<"LissagesImage image.XXX n&b"<<endl;
      cout <<"2 params : Couleur, 3 : N&B = 1, param optionnel "<<endl;
      cout <<"image.XXX : image a afficher "<<endl;
      cout <<"Affichage d'une image en couleur ou N&B et des resultats de lissage"<<endl;
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
  
  namedWindow( "Moyen", WINDOW_AUTOSIZE );
  blur(src, moy,Size(3,3));
  imshow( "Moyen", moy );
  
  namedWindow( "Gaussien", WINDOW_AUTOSIZE );
  GaussianBlur(src, gauss,Size(3,3), 1.5);
  imshow( "Gaussien", gauss );
  
  namedWindow( "Median", WINDOW_AUTOSIZE );
  medianBlur(src, med,3);
  imshow( "Median", med );
  
  /* --- Attente pour fermeture --- */
  waitKey();
  if (src.channels() == 1)
  {
    cout << "Ecriture N&B " <<endl;
    imwrite("MoyenNB.pgm",moy);
  }
  else if (src.channels() == 3)
  {
    cout << "Ecriture RVB " <<endl;
    imwrite("MoyenNB.ppm",moy);
  }
  else
    cout << "Pas d'ecriture " <<endl;
  
  imwrite("MoyenJPG.jpg",moy);
  
}
