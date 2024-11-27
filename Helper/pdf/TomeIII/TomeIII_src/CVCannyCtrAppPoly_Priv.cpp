/* -----------------------------------------------------*/
/* Fichier  : CVCannyCtrAppPoly.cpp                  */
/* Role     : Image en Fichier                */
/*          : Canny Contours Approximation Polygonale   */
/* Auteur   : Patrick Bonnin                            */
/*          : Formation Captronique 2017                */
/* -----------------------------------------------------*/
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int high = 300, low = 100;
int long_min = 10;

void MajHigh (int, void *);
void MajLow (int, void *);
void UpDateResults( int, void* ); 

Mat frame, pts_edge, frameBW, edges, polygones;
vector <vector <Point> > contours;
vector <Vec4i> hierarchy;


/**  @function main */
int main( int argc, char** argv )
{
  
  if (argc != 2)
  {
      cout <<"CVCannyCtrAppPoly image.XXX"<<endl;
      cout <<"image.XXX : image a afficher "<<endl;
      cout <<"Affichage d'une image"<<endl;
      exit(0);
  }
  
  frame = imread( *++argv);
  if(frame.empty())
  {
       cout <<"Image Non Chargee"<<endl;
       return -1;
  }
  
  // Display Images
  namedWindow("image",WINDOW_AUTOSIZE);
  namedWindow("pts_edge",WINDOW_AUTOSIZE);
  namedWindow("Edges",WINDOW_AUTOSIZE);
  namedWindow("polygones",WINDOW_AUTOSIZE);

  // General Inits : creations
  createTrackbar( "LOW",
                  "pts_edge", &low,
                  500, MajLow );

  createTrackbar( "HIGH",
                  "pts_edge", &high,
                  500, MajHigh );
  
  createTrackbar( "Long Min",
                  "Edges", &long_min,
                  200, UpDateResults);
 
  // Wait until user exits the program
  
  imshow("image",frame);
  
  
  
  UpDateResults( 0,0); 
  waitKey(0);
  // Save Results
  imwrite ("../../ImRes/SourceNB.jpg",frameBW);
  imwrite ("../../ImRes/EdgPts.jpg",pts_edge);
  imwrite ("../../ImRes/Edges.jpg",edges);
  imwrite ("../../ImRes/Segments.jpg",polygones);
  return 0;
}

void MajHigh (int, void *)
{
    if (high < low)
    {
        low = high;
        setTrackbarPos("LOW", "pts_edge",low);
    }
    UpDateResults( 0,0); 
}

void MajLow (int, void *)
{
    if (high < low)
    {
        high = low;
        setTrackbarPos("HIGH", "pts_edge",high);
    }
    UpDateResults( 0,0); 
}

void UpDateResults( int, void* )
{
  polygones.create (frame.rows, frame.cols, CV_8UC3);
  edges.create (frame.rows, frame.cols, CV_8UC3);
  pts_edge.setTo(0);
  edges.setTo(0);
  polygones.setTo(0);
    
  cvtColor(frame,frameBW,COLOR_BGR2GRAY);
  GaussianBlur(frameBW, pts_edge, Size(7,7), 1.5, 1.5);
  Canny(pts_edge, pts_edge, low, high, 3);

  findContours (pts_edge, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_NONE);
  
  /* --- Affichage des Contours de Taille Minimale --- */
  double length;
  for (unsigned int nb_ctr = 0; nb_ctr < contours.size(); nb_ctr++)
  {

    length = arcLength(contours[nb_ctr], true);

    if (length >= long_min)

    {    

      Scalar colour(rand()&0xFF,rand()&0xFF,rand()&0xFF);
      drawContours(edges, contours, nb_ctr, colour, 1, 8, hierarchy);
    }

  }

  /* ---  Polygonal Approximation --- */
  vector <vector<Point> > app_poly(contours.size());

  for (unsigned int nb_ctr = 0; nb_ctr < contours.size(); nb_ctr++)

  {
    length = arcLength(contours[nb_ctr], true);
    if (length >= long_min)
    {    
      approxPolyDP(Mat(contours[nb_ctr]),app_poly[nb_ctr], 3, true); // 
      Scalar colour(rand()&0xFF,rand()&0xFF,rand()&0xFF);
      drawContours(polygones, app_poly, nb_ctr, colour, 1, 8, vector <Vec4i>(),0,  
        Point());
    }
  } 
  
  /* --- Update Results   --- */
  // imshow("image",frame);
  imshow("pts_edge", pts_edge);
  imshow("Edges", edges); 
  imshow("polygones", polygones);
}

