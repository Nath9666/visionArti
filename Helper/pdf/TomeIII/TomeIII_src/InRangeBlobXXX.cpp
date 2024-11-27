/* -----------------------------------------------------*/
/* Fichier  : InRangeBlobXXX.cpp                        */
/* Role     : Seuillage parallelepipedique N&B, RVB,    */ 
/*          : HSV, HLS                                  */
/*          : Decomposition en Composantes Connexes     */
/*          : FindContour ... OpenCV                    */
/* Auteur   : Patrick Bonnin                            */
/*          : Cours OpenCV 2023 - OpenCV4               */
/*          : Traitements Evolués                       */
/* -----------------------------------------------------*/
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

#define SURFMIN 2500

using namespace cv;
using namespace std;

int high_1 = 179, low_1 = 0;
int high_2 = 255, low_2 = 0;
int high_3 = 255, low_3 = 0;

Mat src, src_xxx, select_pts;
Mat K ; // Kernel : element structurant;

void inRangeDemoXXX( int, void* );
void Low_1 (int, void* );
void High_1 (int, void* );

void Low_2 (int, void* );
void High_2 (int, void* );

void Low_3 (int, void* );
void High_3 (int, void* );

/* --- Blobs --- */
int area_min = 100;
vector <vector <Point> > contours;
vector <Vec4i> hierarchy;

Mat edges, polygones;
void BlobUpgrade( int, void* );
int code;

int main( int argc, char** argv )
{
  if (argc != 3)
  {
    fprintf(stderr,"InRange image code\n");
    fprintf(stderr," code : 0 : N&B, 1 : RVB, 2 : HSV, 3 : HLS\n");
    exit(0);
  }
  src = imread( *++argv, 1 );
  code = atoi (*++argv);

  /* --- Conversion de l'Image --- */  
  if (code == 0)
    cvtColor(src, src_xxx, COLOR_BGR2GRAY);
  else if (code == 1)
  {
    src_xxx = src.clone();
  }
  else if (code == 2)
    cvtColor(src, src_xxx, COLOR_BGR2HSV);
  else if (code == 3)
    cvtColor(src, src_xxx, COLOR_BGR2HLS);
  else
  {
    fprintf(stderr,"Code non conforme\n");
    exit(0);
  }
  

  namedWindow( "Image", WINDOW_AUTOSIZE );
  namedWindow( "Reglage", WINDOW_AUTOSIZE );
  namedWindow( "Seuillage", WINDOW_AUTOSIZE );

  /* --- Creation Reglages --- */
  if (code == 0) // N&B
  {
    createTrackbar( "BW low",
                    "Reglage", &low_1,
                     255, Low_1 );

    createTrackbar( "BW high",
                    "Reglage", &high_1,
                    255, High_1 );
    setTrackbarMin ("BW low", "Reglage", 0);
    setTrackbarPos ("BW low", "Reglage", 0);
    setTrackbarMin ("BW high", "Reglage", 0);
    setTrackbarPos ("BW high", "Reglage", 255);
  }  
  else if (code == 1) // BGR
  {
    createTrackbar( "BLUE low",
                    "Reglage", &low_1,
                     255, Low_1 );

    createTrackbar( "BLUE high",
                    "Reglage", &high_1,
                    255, High_1 );
        
    createTrackbar( "GREEN low",
                    "Reglage", &low_2,
                    255, Low_2 );

    createTrackbar( "GREEN high",
                  "Reglage", &high_2,
                   255, High_2 );
  
    createTrackbar( "RED low",
                    "Reglage", &low_3,
                    255, Low_3 );

    createTrackbar( "RED high",
                    "Reglage", &high_3,
                    255, High_3 );
                  
    setTrackbarMin ("BLUE low", "Reglage", 0);
    setTrackbarPos ("BLUE low", "Reglage", 0);
    setTrackbarMin ("BLUE high", "Reglage", 0);
    setTrackbarPos ("BLUE high", "Reglage", 255);
  
    setTrackbarMin ("GREEN low", "Reglage", 0);
    setTrackbarPos ("GREEN low", "Reglage", 0);
    setTrackbarMin ("GREEN high", "Reglage", 0);
    setTrackbarPos ("GREEN high", "Reglage", 255);
  
    setTrackbarMin ("RED low", "Reglage", 0);
    setTrackbarPos ("RED low", "Reglage", 0);
    setTrackbarMin ("RED high", "Reglage", 0);
    setTrackbarPos ("RED high", "Reglage", 255);  
  }
  else if (code == 2) // HSV
  {
    createTrackbar( "HUE low",
                    "Reglage", &low_1,
                     179, Low_1 );

    createTrackbar( "HUE high",
                    "Reglage", &high_1,
                    179, High_1 );
        
    createTrackbar( "SATURATION low",
                    "Reglage", &low_2,
                    255, Low_2 );

    createTrackbar( "SATURATION high",
                  "Reglage", &high_2,
                   255, High_2 );
  
    createTrackbar( "VALUE low",
                    "Reglage", &low_3,
                    255, Low_3 );

    createTrackbar( "VALUE high",
                    "Reglage", &high_3,
                    255, High_3 );
                  
    setTrackbarMin ("HUE low", "Reglage", 0);
    setTrackbarPos ("HUE low", "Reglage", 0);
    setTrackbarMin ("HUE high", "Reglage", 0);
    setTrackbarPos ("HUE high", "Reglage", 179);
  
    setTrackbarMin ("SATURATION low", "Reglage", 0);
    setTrackbarPos ("SATURATION low", "Reglage", 0);
    setTrackbarMin ("SATURATION high", "Reglage", 0);
    setTrackbarPos ("SATURATION high", "Reglage", 255);
  
    setTrackbarMin ("VALUE low", "Reglage", 0);
    setTrackbarPos ("VALUE low", "Reglage", 0);
    setTrackbarMin ("VALUE high", "Reglage", 0);
    setTrackbarPos ("VALUE high", "Reglage", 255); 
  }
  else if (code == 3) // HLS
  {
  createTrackbar( "HUE low",
                    "Reglage", &low_1,
                     179, Low_1 );

    createTrackbar( "HUE high",
                    "Reglage", &high_1,
                    179, High_1 );
        
    createTrackbar( "LUMINANCE low",
                    "Reglage", &low_2,
                    255, Low_2 );

    createTrackbar( "LUMINANCE high",
                  "Reglage", &high_2,
                   255, High_2 );
  
    createTrackbar( "SATURATION low",
                    "Reglage", &low_3,
                    255, Low_3 );

    createTrackbar( "SATURATION high",
                    "Reglage", &high_3,
                    255, High_3 );
                  
    setTrackbarMin ("HUE low", "Reglage", 0);
    setTrackbarPos ("HUE low", "Reglage", 0);
    setTrackbarMin ("HUE high", "Reglage", 0);
    setTrackbarPos ("HUE high", "Reglage", 179);
  
    setTrackbarMin ("LUMINANCE low", "Reglage", 0);
    setTrackbarPos ("LUMINANCE low", "Reglage", 0);
    setTrackbarMin ("LUMINANCE high", "Reglage", 0);
    setTrackbarPos ("LUMINANCE high", "Reglage", 255);
  
    setTrackbarMin ("SATURATION low", "Reglage", 0);
    setTrackbarPos ("SATURATION low", "Reglage", 0);
    setTrackbarMin ("SATURATION high", "Reglage", 0);
    setTrackbarPos ("SATURATION high", "Reglage", 255); 
  }
    
  
  
  K = getStructuringElement(MORPH_RECT, Size(3,3));
  if (code == 0)
    imshow( "Image", src_xxx );
  else
    imshow( "Image", src );
  
  inRangeDemoXXX( 0, 0 );
  waitKey();
  
  destroyWindow("Seuillage");
  destroyWindow("Reglage");
  
  findContours (select_pts, contours, hierarchy,RETR_CCOMP , CHAIN_APPROX_NONE); //
  edges.create (src.rows, src.cols, CV_8UC3);
  edges.setTo(0);
  polygones.create (src.rows, src.cols, CV_8UC3);
  polygones.setTo(0);
  
  namedWindow("Edges",WINDOW_AUTOSIZE);
  createTrackbar("Surf Min", "Edges", &area_min,
                  SURFMIN, BlobUpgrade);
  setTrackbarMax ("Surf Min", "Edges", SURFMIN);
  setTrackbarMin ("Surf Min", "Edges", 10);
  
  namedWindow("Polygones",WINDOW_AUTOSIZE);
  
  BlobUpgrade( 0, 0 );
  waitKey();
  /* --- Sauvegardes --- */
  imwrite("PixelSelection.jpg",select_pts);
  imwrite("BlobDetection.jpg",edges);

}

void Low_1 (int, void* )
{
  if (low_1 > high_1)
  {
    high_1 = low_1;
    
    if (code == 1)
      setTrackbarPos ("BLUE high", "Reglage", high_1);
    else if ((code == 2)||(code == 3))
      setTrackbarPos ("HUE high", "Reglage", high_1);
    else if (code == 0)
      setTrackbarPos ("BW high", "Reglage", high_1);
  }
  inRangeDemoXXX( 0, 0 );
}
void High_1 (int, void* )
{
  if (high_1 < low_1 )
  {
    low_1 = high_1;
    if (code == 1)
      setTrackbarPos ("BLUE low", "Reglage", low_1);
    else if ((code == 2)||(code == 3))
      setTrackbarPos ("HUE low", "Reglage", low_1);
    else if (code == 0)
      setTrackbarPos ("BW low", "Reglage", low_1);
   
  }
  inRangeDemoXXX( 0, 0 );
}

void Low_2(int, void* )
{
  if (low_2 > high_2)
  {
    high_2 = low_2;
    if (code == 1)
      setTrackbarPos ("GREEN high", "Reglage", high_2);
    else if (code == 2)
      setTrackbarPos ("SATURATION high", "Reglage", high_2);
    else if (code == 3)
      setTrackbarPos ("LUMINANCE high", "Reglage", high_2);
  }
  inRangeDemoXXX( 0, 0 );
}
void High_2 (int, void* )
{
  if (high_2 < low_2)
  {
    low_2 = high_2;
    if (code == 1)
       setTrackbarPos ("GREEN low", "Reglage", low_2);
    else if (code == 2)
      setTrackbarPos ("SATURATION low", "Reglage", low_2);
    else if (code == 3)
      setTrackbarPos ("LUMINANCE low", "Reglage", low_2);
  }
  inRangeDemoXXX( 0, 0 );
}

void Low_3 (int, void* )
{
  if (low_3 > high_3)
  {
    high_3 = low_3;
    if (code == 1)
      setTrackbarPos ("RED high", "Image", high_3);
    else if (code == 2)
      setTrackbarPos ("VALUE high", "Image", high_3);
    else if (code == 3)
      setTrackbarPos ("SATURATION high", "Image", high_3);
  }
  inRangeDemoXXX( 0, 0 );
}

void High_3 (int, void* )
{
  if (high_3 < low_3)
  {
    low_3 = high_3;
    if (code == 1)
      setTrackbarPos ("RED low", "Image", low_3);
    else if (code == 2)
      setTrackbarPos ("VALUE low", "Image", low_3);
    else if (code == 3)
      setTrackbarPos ("SATURATION low", "Image", low_3); 
  }
  inRangeDemoXXX( 0, 0 );
}

/* --- Classification --- */
void inRangeDemoXXX( int, void* )
{
    if (code == 0)
      inRange(src_xxx,low_1, high_1,select_pts);
    else
      inRange(src_xxx,Scalar(low_1, low_2, low_3),
        Scalar(high_1, high_2, high_3),select_pts);
      
    morphologyEx(select_pts, select_pts, MORPH_OPEN, K);
    morphologyEx(select_pts, select_pts, MORPH_CLOSE, K);
    imshow("Seuillage", select_pts);
}

/* --- Blob --- */
void BlobUpgrade( int, void* )
{
  vector<Moments> mu(contours.size());
  vector<Point2f> mc(contours.size());
  vector<vector<Point> > app_poly(contours.size());
  vector<Rect> boundRect(contours.size());
  double area;
  
  edges.setTo(0);
  polygones.setTo(0);
  fprintf(stderr,"SurfMin = %d\n",area_min);
  
  for (unsigned int nb_ctr = 0; nb_ctr < contours.size(); nb_ctr++)
  {
    mu[nb_ctr] = moments(contours[nb_ctr], false);
    area = mu[nb_ctr].m00;
    if (area >= (double)area_min)
    {    
      mc[nb_ctr] = Point2f(mu[nb_ctr].m10/mu[nb_ctr].m00, mu[nb_ctr].m01/mu[nb_ctr].m00);
      Scalar colour(rand()&0xFF,rand()&0xFF,rand()&0xFF);
      Scalar colourCenter(0x00, 0x00, 0xFF);
      drawContours(edges, contours, nb_ctr, colour, FILLED, 8, hierarchy);
      circle(edges, mc[nb_ctr], 4, colourCenter, -1, 8, 0);
      
      /* --- Approximation Polygonale --- */
      approxPolyDP(Mat(contours[nb_ctr]),app_poly[nb_ctr], 3, true);
      Scalar colourPoly(rand()&0xFF,rand()&0xFF,rand()&0xFF);
      drawContours(polygones, app_poly, nb_ctr, colourPoly, 1, 8, 
         vector <Vec4i>(),0, Point());

      // La boite englobante est realisee a partir de l'approximation polygonale ! 
      boundRect[nb_ctr] = boundingRect(app_poly[nb_ctr]); 
      Scalar colourRect(0x00, 0xFF, 0xFF);
      rectangle(edges, boundRect[nb_ctr].tl(), boundRect[nb_ctr].br(), colourRect, 2);
    }
  }
  imshow("Edges", edges); 
  imshow("Polygones", polygones);
}

