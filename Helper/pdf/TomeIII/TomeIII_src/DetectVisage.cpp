// Repris de code de Pepin Donnat
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>

/* Déclaration en global pour éviter de les écrire plusieurs fois*/
using namespace cv; 
using namespace std;

string face_cascade_name = "haarcascade_frontalface_alt.xml"; 

CascadeClassifier face_cascade; // Déclaration de notre variable face de type Cascade

int main(int argc , char** argv)
{
  Mat src;
  vector<Rect> face;
  
  if (argc != 2)
  {
    cout << "USAGE : DetectVisage image : " <<endl;
  }
  if( !face_cascade.load( face_cascade_name ) )
  { 
    printf("Erreur haarcascade pas trouvé\n"); 
    return -1; 
  }
  namedWindow( "Visages", WINDOW_AUTOSIZE );
  src = imread( *++argv); 
  if(src.empty())
  {
    cout <<"Image Non Chargee"<<endl;
    return -1;
  }
  /* --- Detection des Visages --- */
  face_cascade.detectMultiScale(src, face, 1.1,  
    5,CASCADE_SCALE_IMAGE,Size(30,30));

  cout << "Nombre de Faces : " << face.size() << endl;
  /* --- Tracé des Visages Détectés --- */
  for( size_t i = 0; i < face.size(); i++ )
  {
    Point center(face[i].x + face[i].width/2, face[i].y + 
      face[i].height/2);
    ellipse(src, center, Size( face[i].width/2, 
      face[i].height/2), 0, 0, 360, 
      Scalar( 0, 0, 255 ), 4, 8, 0 );
    Point upper_left(face[i].x, face[i].y);
    Point lower_right(face[i].x + face[i].width, 
      face[i].y + face[i].height);
    rectangle(src, upper_left, lower_right, Scalar(0, 255, 0), 2);
  }		 	
  imshow( "Visages", src ); 
  waitKey(0);
  return 0;
}

/* Corps de notre fonction qui detecte les visages */

void detectFace(Mat frame)
{
  
	
  
}
