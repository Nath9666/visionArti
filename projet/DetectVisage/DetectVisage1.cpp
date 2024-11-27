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

void detectFace(Mat frame); // Prototype de la fonction detectFace

/* Fonction main */

int main(int argc , char** argv)
{
	Mat frame;

  	if( !face_cascade.load( face_cascade_name ) )
	{ 
		printf("Erreur haarcascade pas trouvé\n"); 
		return -1; 
	}
	
	VideoCapture cap(0);
	namedWindow( "Visages", WINDOW_AUTOSIZE );
	
	if(!cap.isOpened())
	{
      		return -1;
	}
	
	for(;;) // Boucle d'Acquisition
	{
    	  cap >> frame; // Obtenir une image de la camera

	  if( !frame.empty() )
          { 
	    detectFace( frame );
	    imshow( "Visages", frame ); 
	  }
          else
          { 
	    printf("Pas de capture d'image"); 
	    break; 
	  }      
    
    	  if(waitKey(1) == 'q') break;
	}
	waitKey(0);
	return 0;
}

/* Corps de notre fonction qui detecte les visages */

void detectFace(Mat frame)
{
  vector<Rect> face;
	
  face_cascade.detectMultiScale(frame, face, 1.1,  
    5,CASCADE_SCALE_IMAGE,Size(30,30));

  cout << "Nombre de Faces : " << face.size() << endl;
  for( size_t i = 0; i < face.size(); i++ )
  {
    Point center(face[i].x + face[i].width/2, face[i].y + 
      face[i].height/2);
    ellipse( frame, center, Size( face[i].width/2, 
      face[i].height/2), 0, 0, 360, 
      Scalar( 0, 0, 255 ), 4, 8, 0 );
    Point upper_left(face[i].x, face[i].y);
    Point lower_right(face[i].x + face[i].width, 
      face[i].y + face[i].height);
    rectangle(frame, upper_left, lower_right, Scalar(0, 255, 0), 2);
  }		 
}
