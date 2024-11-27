#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>

// Mesure de Performances :
#include <sys/time.h>

#include "EdStructures.h"
#include "DSCCvUtilities.h"
#include "EdUtilities.h"

#define VERB 0

/* Déclaration en global pour éviter de les écrire plusieurs fois*/
using namespace cv; 
using namespace std;

string face_cascade_name = "haarcascade_frontalface_alt.xml"; 

CascadeClassifier face_cascade; // Déclaration de notre variable face de type Cascade

// Prototype de la fonction detectFace
int detectFace(Mat frame, Mat frameY, Mat frameRes,
        EdIMAGE *Edframe, EdIMAGE *EdframeY, EdIMAGE *EdframeRes,
        EdBOX *boxL, EdBOX *boxR, EdPOINT *pointL, EdPOINT *pointR); 

int detectPupilCenter(EdIMAGE *Edframe, EdIMAGE *EdframeY, 
        EdIMAGE *EdframeRes, EdBOX *box, EdPOINT *point, int *pmin);

// Prototypes du SimpleTracking        
int ColorCorrelation(EdIMAGE *imSrc, EdIMAGE *imTarget, EdBOX *boxPPM,
  int delta_xmax, int delta_ymax, int *pdelta_x, int *pdelta_y, 
  long *pcoutmin);
int TargetAcquisition (EdIMAGE *imSrc, EdIMAGE *imTarget, EdBOX *boxPPM);

// Prototypes du Multiple Target Tracking
int MultipleTargetAcquisition (EdIMAGE *imSrc, EdIMAGE *imTarget, 
      EdBOX *boxPPM, EdPOINT *pointOrg); 
int MultiTargetColorCorrelation(EdIMAGE *imSrc, EdIMAGE *imTarget, 
    EdBOX *boxPPM, EdPOINT *pointOrg, int delta_xmax, int delta_ymax, 
    int *pdelta_x, int *pdelta_y, long *pcoutmin);

/* Fonction main */


int main(int argc , char** argv)
{
  Mat frame, frameY, ImTarget, frameRes;
  EdIMAGE *Edframe, *EdframeY, *EdframeRes;
  EdIMAGE *EdImTarget;
  EdBOX *boxL, *boxR;
  EdPOINT *pointL, *pointR, *pointOrg;
  int ret;
  
  int flagFirst = true;
  int nbvalid = 5; // parametre à régler
  int nb = 0;
  int State = 0; // Acquisition = 0 , Tracking = 1
  
  int delta_xmax = 5; /* deplacement maxi en x : a regler 10 ? */ 
  int delta_ymax = 5; /* deplacement maxi en x : a regler 10 ? */
  int delta_x, delta_y ; /* deplacement trouvé */
  long coutmin ; /* cout de correlation */

  int minL, minR, Res;
  
  // Mesure de Performances
int flagFirstTrack = false;
int ntrt = 0; 
int ntrtMax = 100;
double period, freq; 

struct timeval tv[2];
int flagStop = false;
double dDeb, dFin, dTemps;
    
  if( !face_cascade.load( face_cascade_name ) )
  { 
    printf("Erreur haarcascade pas trouvé\n"); 
    return -1; 
  }
	
  VideoCapture cap(0);
  namedWindow( "Visages", WINDOW_AUTOSIZE );
  namedWindow( "Eyes", WINDOW_AUTOSIZE );
	
  if(!cap.isOpened())
  {
    return -1;
  }
  cap.set(CAP_PROP_FRAME_WIDTH, 640);
  cap.set(CAP_PROP_FRAME_HEIGHT, 480);
  cap.set(CAP_PROP_FPS, 60);
	
  for(;;) // Boucle d'Acquisition
  {
    cap >> frame; // Obtenir une image de la camera
    if (flagFirst == false)
      memcpy(frameRes.ptr<uchar>(0), frame.ptr<uchar>(0),
        3 * frame.rows * frame.cols );
    
    if(frame.empty())
    {
      cout <<"Acquisition non réalisée "<<endl;
      exit (0);
    }
          
    cvtColor( frame, frameY, COLOR_BGR2GRAY );
    
    if (flagFirst == true)
    {
      flagFirst = false;
      ImTarget.create(frame.rows, frame.cols, CV_8UC3 );
      frameRes.create(frame.rows, frame.cols, CV_8UC3 );
      /* --- Edframe, EdframeRes, EdframeY : Shadow --- */
      if (crea_IMAGE(Edframe) == NULL)	/* creation of Image Header  */
      {
        fprintf(stderr,"Error of Memory Allocation  \n");
    	exit (0);
      }
      EdImagefromMat (Edframe, frame);
      
      if (crea_IMAGE(EdframeRes) == NULL)	/* creation of Image Header  */
      {
        fprintf(stderr,"Error of Memory Allocation  \n");
    	exit (0);
      }
      EdImagefromMat (EdframeRes, frameRes);
              
      if (crea_IMAGE(EdframeY) == NULL)	/* creation of Image Header  */
      {
        fprintf(stderr,"Error of Memory Allocation  \n");
    	exit (0);
      }
      EdImagefromMat (EdframeY, frameY);
      
      if (crea_IMAGE(EdImTarget) == NULL)	/* creation of Image Header  */
      {
        fprintf(stderr,"Error of Memory Allocation  \n");
    	exit (0);
      }
      // Creation_Image (EdImTarget, NLIG(Edframe), NCOL(Edframe), 
      //  PROF(Edframe));
      EdImagefromMat (EdImTarget, ImTarget);
      
      /* --- Informations de la détection --- */
      if (crea_BOX(boxL) == NULL)	
      {
        fprintf(stderr,"Error of Memory Allocation : Box  \n");
        exit (0);
      } 
      if (crea_BOX(boxR) == NULL)	
      {
        fprintf(stderr,"Error of Memory Allocation : Box  \n");
        exit (0);
      } 
  
      /* --- Point data structure allocations --- */ 
      if (crea_POINT(pointL) == NULL)	
      {
        fprintf(stderr,"Error of Memory Allocation : Point  \n");
        exit (0);
      } 
      if (crea_POINT(pointR) == NULL)	
      {
        fprintf(stderr,"Error of Memory Allocation : Point  \n");
        exit (0);
      }
      if (crea_POINT(pointOrg) == NULL)	
      {
        fprintf(stderr,"Error of Memory Allocation : Point  \n");
        exit (0);
      } 
    } // fin if flagFirst
 
    /* --- Acquisition du Visage et des Yeux --- */ 
    if (State == 0)
    {          
      ret = detectFace( frame, frameY, frameRes, Edframe, EdframeY, 
        EdframeRes, boxL, boxR, pointL, pointR);
      if (ret == 0)
      {
        fprintf(stderr,"Visage, 2 pupilles horizontales \n");
        nb++;
      }
      else if (ret == 1)
      {
        fprintf(stderr,"Visage, 2 pupilles non horizontales \n");
        nb = 0;
      }
      else if (ret == 2)
      {
        fprintf(stderr,"Visage, MOINS de 2 pupilles  \n");
        nb = 0;
      }  
      // cout << "nombre de validations successives :"<<nb<<endl;
      imshow( "Visages", frameRes );
      if (nb >= nbvalid)
      {
        State = 1; // Acquisition : OK => Tracking
        nb = 0;
        ret = TargetAcquisition (Edframe, EdImTarget, boxL);
        if (ret != 0)
        {
          cout <<"Probleme acquisition eyeL :"<<endl;
          exit (0);
        }

        POINT_X(pointOrg) = BOX_XMAX(boxL) - BOX_XMIN(boxL) + 1 + 2;
        POINT_Y(pointOrg) = 0;
        ret = MultipleTargetAcquisition (Edframe, EdImTarget, boxR, 
                pointOrg);
        if (ret != 0)
        {
          cout <<"Probleme acquisition eyeL :"<<endl;
          exit (0);
        } 
        imshow( "Eyes", ImTarget );
        waitKey(0);
      } /* fin nbvalid */
      
    } /* fin d'acquisition */
    else if (State == 1)
    {
      if (flagFirstTrack == false)
      {
	flagFirstTrack = true;
    	gettimeofday(& (tv[0]), NULL);
    	dDeb = (double)(tv[0].tv_usec) * 0.000001 + 
    	      (double)tv[0].tv_sec;
      } 

   
      nb++;
      ntrt++;
      
      if (ntrt >= ntrtMax)
      {
        
        gettimeofday(& (tv[1]), NULL);
        
        dFin = (double)(tv[1].tv_usec) * 0.000001 + 
              (double)tv[1].tv_sec;
        dTemps = (dFin - dDeb);
        period = dTemps / ntrtMax;
        freq = 1.0/period;
            
        fprintf(stderr,"Periode en ms : %lf, freq : %lf \n",
              period * 1000, freq);
        dDeb = dFin; // nouvelle mesure
        ntrt = 0;
      }
#if VERB      
      cout << "Etat : Tracking image :"<< nb <<endl;
#endif      
      /* --- Left Eye --- */
      ret = ColorCorrelation(Edframe, EdImTarget, boxL,
              delta_xmax, delta_ymax, &delta_x, &delta_y, &coutmin);
      
      BOX_XMIN(boxL) += delta_x;
      BOX_XMAX(boxL) += delta_x; 
      BOX_YMIN(boxL) += delta_y;
      BOX_YMAX(boxL) += delta_y;     
  
      if ((BOX_XMIN(boxL) < 0) || (BOX_YMIN(boxL) < 0)
        || (BOX_XMAX(boxL) >= NCOL(Edframe)) 
        || (BOX_YMAX(boxL) >= NLIG(Edframe)))
      {
        cout <<"EyeL : out of the image "<<endl;
        exit(0);
      }
      Res = detectPupilCenter(Edframe, EdframeY, EdframeRes,
            boxL, pointL, &minL);
         
      // ret = TargetAcquisition (Edframe, EdImTarget, boxL);
      Point LEye_UL (BOX_XMIN(boxL), BOX_YMIN(boxL));
      Point LEye_LR (BOX_XMAX(boxL),BOX_YMAX(boxL));
      rectangle(frameRes, LEye_UL, LEye_LR, Scalar(0, 255, 0), 2); 
 
     
      /* --- Right Eye --- */
      ret = MultiTargetColorCorrelation(Edframe, EdImTarget, boxR,
              pointOrg, delta_xmax, delta_ymax, &delta_x, 
              &delta_y, &coutmin);
      
      BOX_XMIN(boxR) += delta_x;
      BOX_XMAX(boxR) += delta_x; 
      BOX_YMIN(boxR) += delta_y;
      BOX_YMAX(boxR) += delta_y;     
  
      if ((BOX_XMIN(boxR) < 0) || (BOX_YMIN(boxR) < 0)
        || (BOX_XMAX(boxR) >= NCOL(Edframe)) 
        || (BOX_YMAX(boxR) >= NLIG(Edframe)))
      {
        cout <<"EyeR : out of the image "<<endl;
        exit(0);
      }
         
      Res = detectPupilCenter(Edframe, EdframeY, EdframeRes,
            boxR, pointR, &minR);
//      ret = MultipleTargetAcquisition (Edframe, EdImTarget, boxR, 
//          pointOrg);
      
      Point REye_UL (BOX_XMIN(boxR), BOX_YMIN(boxR));
      Point REye_LR (BOX_XMAX(boxR),BOX_YMAX(boxR));
      rectangle(frameRes, REye_UL, REye_LR, Scalar(0, 255, 255), 2); 
      
      
      imshow( "Visages", frameRes );
      
    } /* fin Tracking */
    	  
    if(waitKey(1) == 'q') break;
  }
  waitKey(0);
  return 0;
}

/* Corps de notre fonction qui detecte les visages */

int detectFace(Mat frame, Mat frameY, Mat frameRes,
        EdIMAGE *Edframe, EdIMAGE *EdframeY, EdIMAGE *EdframeRes,
        EdBOX *boxL, EdBOX *boxR, EdPOINT *pointL, EdPOINT *pointR )
{
  vector<Rect> face;
  int minL, minR;
  int ret, Res;

  face_cascade.detectMultiScale(frame, face, 1.1,  
    5,CASCADE_SCALE_IMAGE,Size(30,30));

  cout << "Nombre de Faces : " << face.size() << endl;
  
  if (face.size() > 0)
  {
    Point center(face[0].x + face[0].width/2, face[0].y + 
      face[0].height/2);
    
    Point upper_left(face[0].x, face[0].y);
    Point lower_right(face[0].x + face[0].width, 
      face[0].y + face[0].height);
    rectangle(frameRes, upper_left, lower_right, Scalar(0, 0, 255), 2);
    Point LEye_UL (face[0].x + face[0].width/8, 
      face[0].y + face[0].height/4);
    Point LEye_LR (face[0].x + face[0].width/2 - 1, 
      face[0].y + face[0].height/2);
    Point REye_UL (face[0].x + face[0].width/2, 
      face[0].y + face[0].height/4);
    Point REye_LR (face[0].x + 7 * face[0].width/8, 
      face[0].y + face[0].height/2);

    rectangle(frameRes, LEye_UL, LEye_LR, Scalar(0, 255, 0), 2);
    rectangle(frameRes, REye_UL, REye_LR, Scalar(255,0, 0), 2);
   
    BOX_XMIN (boxL) = LEye_UL.x;
    BOX_YMIN (boxL) = LEye_UL.y; 
    BOX_XMAX (boxL) = LEye_LR.x;
    BOX_YMAX (boxL) = LEye_LR.y;  
    
    BOX_XMIN (boxR) = REye_UL.x;
    BOX_YMIN (boxR) = REye_UL.y; 
    BOX_XMAX (boxR) = REye_LR.x;
    BOX_YMAX (boxR) = REye_LR.y; 
    
    Res = detectPupilCenter(Edframe, EdframeY, EdframeRes,
            boxL, pointL, &minL);
    LEye_UL.x = POINT_X(pointL) - face[0].width/8;
    LEye_UL.y = POINT_Y(pointL) - face[0].height/16;
    LEye_LR.x = POINT_X(pointL) + face[0].width/8;
    LEye_LR.y = POINT_Y(pointL) + face[0].height/16;
    rectangle(frameRes, LEye_UL, LEye_LR, Scalar(0, 0, 255), 1);
    
    // Pour initialisation du tracking
    BOX_XMIN (boxL) = LEye_UL.x;
    BOX_YMIN (boxL) = LEye_UL.y; 
    BOX_XMAX (boxL) = LEye_LR.x;
    BOX_YMAX (boxL) = LEye_LR.y; 
    ////////
    
    Res += detectPupilCenter(Edframe, EdframeY, EdframeRes,
             boxR, pointR, &minR);
    REye_UL.x = POINT_X(pointR) - face[0].width/8;
    REye_UL.y = POINT_Y(pointR) - face[0].height/16;
    REye_LR.x = POINT_X(pointR) + face[0].width/8;
    REye_LR.y = POINT_Y(pointR) + face[0].height/16;
    rectangle(frameRes, REye_UL, REye_LR, Scalar(0, 0, 255), 1);
    
    //////Pour initialisation du tracking
    BOX_XMIN (boxR) = REye_UL.x;
    BOX_YMIN (boxR) = REye_UL.y; 
    BOX_XMAX (boxR) = REye_LR.x;
    BOX_YMAX (boxR) = REye_LR.y; 
    ////////

   
    /* --- Validation de la Détection de Pupilles --- */
    if (Res == 2)
    {  
      int Diff = POINT_Y(pointR) - POINT_Y(pointL);
      Diff = Diff >= 0 ? Diff : -Diff;
      
      if (Diff <= (BOX_YMAX (boxL) - BOX_YMIN (boxL))/3)
      {
        // fprintf(stderr,"Validation de la détection \n");
        ret = 0; // Visage et pupilles : OK
      }
      else
        ret = 1; // Deux pupilles non horizontales
    }
    else  
    ret = 2; // Pas deux pupilles detectees
  } // fin si face detectee
  else
     ret = 3; // pas de face detectee
     
  return ret;		 
}
 /* --------------------------------------------------------- */
 /* --- Seconde Version : Ensemble des Minima --- */
 
 int detectPupilCenter(EdIMAGE *Edframe, EdIMAGE *EdframeY, 
       EdIMAGE *EdframeRes, EdBOX *box, EdPOINT *pointMin, int *pmin)
{
  EdPOINT *point, *pointv;
  EdIMAGE *EdImB, *EdImD;
  int nlig = NLIG(Edframe), ncol = NCOL(Edframe);
  unsigned char prof = 1;
  int ret;
  EdBOX *boxWk, *boxPup; // box Work and Pupil
  int i,j;
  int flagDilat, Diff, nbpt;
  
  if (crea_POINT(point) == NULL)	
  {
    fprintf(stderr,"Error of Memory Allocation : Point  \n");
    exit (0);
  } 
  if (crea_POINT(pointv) == NULL)	
  {
    fprintf(stderr,"Error of Memory Allocation : Point  \n");
    exit (0);
  } 
  /* --- Recherche du minimum de luminance : pupille */
  /* --- Initialisation --- */
  POINT_X(point) = BOX_XMIN(box);
  POINT_Y(point) = BOX_YMIN(box);
  *pmin = PIXEL (EdframeY,point);
  POINT_X(pointMin) = POINT_X(point);
  POINT_Y(pointMin) = POINT_Y(point);
  
  /* --- Recherche de la Valeur Minimale --- */
  for (POINT_Y(point) = BOX_YMIN(box); POINT_Y(point) <= BOX_YMAX(box);
    POINT_Y(point)++)
  for (POINT_X(point) = BOX_XMIN(box); POINT_X(point) <= BOX_XMAX(box);
    POINT_X(point)++)
  {
    if (PIXEL(EdframeY, point) < *pmin)
    {
      *pmin = PIXEL(EdframeY, point);
      POINT_X(pointMin) = POINT_X(point);
      POINT_Y(pointMin) = POINT_Y(point);
    }
  }/* fin parcours video : minimum */
  
  /* --- Extraction de la Pupille --- */
  /* --- Creation des Images de Travail : EdImB, EdImD ---  */
  if (crea_IMAGE(EdImB) == NULL)	/* creation of Image Header  */
  {
    fprintf(stderr,"Error of Memory Allocation  \n");
    exit (0);
  }
  ret = Creation_Image (EdImB, nlig, ncol, prof); // Image Data
  if (!ret)
  {
    fprintf(stderr,"Error of Memory Allocation of Pixels  \n");
    exit (0);
  }
  
  if (crea_IMAGE(EdImD) == NULL)	/* creation of Image Header  */
  {
    fprintf(stderr,"Error of Memory Allocation  \n");
    exit (0);
  }
  ret = Creation_Image (EdImD, nlig, ncol, prof); // Image Data
  if (!ret)
  {
    fprintf(stderr,"Error of Memory Allocation of Pixels  \n");
    exit (0);
  }
  
  if (crea_BOX(boxWk) == NULL)	
  {
    fprintf(stderr,"Error of Memory Allocation : Box  \n");
    exit (0);
  }
  
  if (crea_BOX(boxPup) == NULL)	
  {
    fprintf(stderr,"Error of Memory Allocation : Box  \n");
    exit (0);
  } 
  
  /* --- Init EdImage --- */
  memset (PIOCTET(EdImB), 0, nlig * ncol);
  memset (PIOCTET(EdImD), 0, nlig * ncol);
  
  
  int InitBox = false;
  int nbptinit = 0;
  for (POINT_Y(point) = BOX_YMIN(box); POINT_Y(point) <= BOX_YMAX(box);
    POINT_Y(point)++)
  for (POINT_X(point) = BOX_XMIN(box); POINT_X(point) <= BOX_XMAX(box);
    POINT_X(point)++)
  {
    if (PIXEL(EdframeY, point) == *pmin)
    {
      if (InitBox == false)
      {
        InitBox = true;
        BOX_XMIN(boxPup) = POINT_X(point);
        BOX_XMAX(boxPup) = POINT_X(point);
        BOX_YMIN(boxPup) = POINT_Y(point);
        BOX_YMAX(boxPup) = POINT_Y(point);
        PIXEL(EdImB, point) = 255;
        nbptinit = 1;
      }
      else
      {
        if (POINT_X(point) < BOX_XMIN(boxPup))
          BOX_XMIN(boxPup) = POINT_X(point);
        if (POINT_X(point) > BOX_XMAX(boxPup))
          BOX_XMAX(boxPup) = POINT_X(point);
        if (POINT_Y(point) < BOX_YMIN(boxPup))
          BOX_YMIN(boxPup) = POINT_Y(point);
        if (POINT_Y(point) > BOX_YMAX(boxPup))
          BOX_YMAX(boxPup) = POINT_Y(point);
        PIXEL(EdImB, point) = 255;
        nbptinit++;
      }
    }
  }
#if VERB
  fprintf(stderr,"Pupille Initiale : surface : %d \n",nbptinit);
#endif  
  
  // debug 
  int num = 0;
  do
  {
    nbpt = 0;
    BOX_XMIN(boxWk) = BOX_XMIN(boxPup) - 1;
    BOX_XMAX(boxWk) = BOX_XMAX(boxPup) + 1;
    BOX_YMIN(boxWk) = BOX_YMIN(boxPup) - 1;
    BOX_YMAX(boxWk) = BOX_YMAX(boxPup) + 1;
    
    for (POINT_Y(point) = BOX_YMIN(boxWk); 
      POINT_Y(point) <= BOX_YMAX(boxWk);POINT_Y(point)++)
    for (POINT_X(point) = BOX_XMIN(boxWk); 
      POINT_X(point) <= BOX_XMAX(boxWk);POINT_X(point)++)
    {
      flagDilat = false;
      if (PIXEL(EdImB, point) == 0)
      {
        for (j = 0; j < 3; j++)
        for (i = 0; i < 3; i++)
        {
          if ((i == 1) && (j == 1))
            continue;
          POINT_X(pointv) = POINT_X(point) + i - 1;
          POINT_Y(pointv) = POINT_Y(point) + j - 1;
          Diff = PIXEL(EdframeY, pointv) - PIXEL(EdframeY, pointMin);
          Diff = (Diff >= 0 ? Diff : -Diff);
          if (Diff <= 1)
            flagDilat = true; 
        } /* fin balayage voisinage 3 * 3 */
        if (flagDilat == true)
        {
          PIXEL(EdImD, point) = 255;
          // PIXEL_R(Edframe, point) = 0 ; // B en BGR
          // PIXEL_V(Edframe, point) = 255 ; // G en BGR
          // PIXEL_B(Edframe, point) = 255 ; // R en BGR
          nbpt++;
          if (POINT_X(point) < BOX_XMIN(boxPup))
            BOX_XMIN(boxPup) = POINT_X(point);
          if (POINT_X(point) > BOX_XMAX(boxPup))
            BOX_XMAX(boxPup) = POINT_X(point);
          if (POINT_Y(point) < BOX_YMIN(boxPup))
            BOX_YMIN(boxPup) = POINT_Y(point);
          if (POINT_Y(point) > BOX_YMAX(boxPup))
            BOX_YMAX(boxPup) = POINT_Y(point);
        }
        else 
          PIXEL(EdImD, point) = 0;
      } /* fin si point du fond */
    } /* fin balayage boxWk */
    
    
    /* --- Mise à Jour de l'Image "source" pour la dilatation --- */
    for (POINT_Y(point) = BOX_YMIN(boxWk); 
      POINT_Y(point) <= BOX_YMAX(boxWk);POINT_Y(point)++)
    for (POINT_X(point) = BOX_XMIN(boxWk); 
      POINT_X(point) <= BOX_XMAX(boxWk);POINT_X(point)++)
      PIXEL(EdImB, point) = PIXEL(EdImD, point); 
      
    num ++;
    // fprintf(stderr,"Iteration %d, Nombre de Points %d\n", num, nbpt);
     
  }
  while (nbpt > 0);
 
 
 int surf = 0, sdx = 0, sdy = 0;
 
 /* --- Nouvelle Validation : Centre de Gravité --- */
 for (POINT_Y(point) = BOX_YMIN(boxWk); 
      POINT_Y(point) <= BOX_YMAX(boxWk);POINT_Y(point)++)
 for (POINT_X(point) = BOX_XMIN(boxWk); 
      POINT_X(point) <= BOX_XMAX(boxWk);POINT_X(point)++)
 {
   if (PIXEL(EdImB, point) == 255)
   {
     surf += 1;
     sdx += POINT_X(point);
     sdy += POINT_Y(point);
   }
 }
 POINT_X(pointMin) = sdx / surf;
 POINT_Y(pointMin) = sdy / surf;
 
 int Ret;
 /* --- Validation de la Position de la pupulle --- */
 if ((POINT_X(pointMin) >= (BOX_XMIN (box) 
      + (BOX_XMAX (box) - BOX_XMIN (box))/3))
      && (POINT_X(pointMin) <= (BOX_XMIN (box) 
      + (BOX_XMAX (box) - BOX_XMIN (box)) * 2 /3)))
    Ret = 1; // pupille OK
  else
  {
    Ret =  0; // pupille NOK
    fprintf(stderr,"Image %d : Pupille non au centre !",num);
  }
 // Ajout : Pupille bien centree 
  if (Ret == 1)
  {
    PIXEL_R(EdframeRes, pointMin) = 0 ; // B en BGR
    PIXEL_V(EdframeRes, pointMin) = 0 ; // G en BGR
    PIXEL_B(EdframeRes, pointMin) = 255 ; // R en BGR
  
    /* --- Reperage par une croix --- */
    POINT_X(point) = POINT_X(pointMin) - 1; 
    POINT_Y(point) = POINT_Y(pointMin);
    PIXEL_R(EdframeRes, point) = 0 ; // B en BGR
    PIXEL_V(EdframeRes, point) = 255 ; // G en BGR
    PIXEL_B(EdframeRes, point) = 255 ; // R en BGR
  
    POINT_X(point) = POINT_X(pointMin) + 1; 
    POINT_Y(point) = POINT_Y(pointMin);
    PIXEL_R(EdframeRes, point) = 0 ; // B en BGR
    PIXEL_V(EdframeRes, point) = 255 ; // G en BGR
    PIXEL_B(EdframeRes, point) = 255 ; // R en BGR
  
    POINT_X(point) = POINT_X(pointMin); 
    POINT_Y(point) = POINT_Y(pointMin) - 1;
    PIXEL_R(EdframeRes, point) = 0 ; // B en BGR
    PIXEL_V(EdframeRes, point) = 255 ; // G en BGR
    PIXEL_B(EdframeRes, point) = 255 ; // R en BGR
  
    POINT_X(point) = POINT_X(pointMin); 
    POINT_Y(point) = POINT_Y(pointMin) + 1;
    PIXEL_R(EdframeRes, point) = 0 ; // B en BGR
    PIXEL_V(EdframeRes, point) = 255 ; // G en BGR
    PIXEL_B(EdframeRes, point) = 255 ; // R en BGR
  
    POINT_X(point) = POINT_X(pointMin) - 2; 
    POINT_Y(point) = POINT_Y(pointMin);
    PIXEL_R(EdframeRes, point) = 0 ; // B en BGR
    PIXEL_V(EdframeRes, point) = 255 ; // G en BGR
    PIXEL_B(EdframeRes, point) = 255 ; // R en BGR
  
    POINT_X(point) = POINT_X(pointMin) + 2; 
    POINT_Y(point) = POINT_Y(pointMin);
    PIXEL_R(EdframeRes, point) = 0 ; // B en BGR
    PIXEL_V(EdframeRes, point) = 255 ; // G en BGR
    PIXEL_B(EdframeRes, point) = 255 ; // R en BGR
  
    POINT_X(point) = POINT_X(pointMin); 
    POINT_Y(point) = POINT_Y(pointMin) - 2;
    PIXEL_R(EdframeRes, point) = 0 ; // B en BGR
    PIXEL_V(EdframeRes, point) = 255 ; // G en BGR
    PIXEL_B(EdframeRes, point) = 255 ; // R en BGR
  
    POINT_X(point) = POINT_X(pointMin); 
    POINT_Y(point) = POINT_Y(pointMin) + 2;
    PIXEL_R(EdframeRes, point) = 0 ; // B en BGR
    PIXEL_V(EdframeRes, point) = 255 ; // G en BGR
    PIXEL_B(EdframeRes, point) = 255 ; // R en BGR
  } /* fin si pupille bien placee */  
  
  free((void*)point);
  free((void*)pointv);
  Free_Image(EdImB);
  Free_Image(EdImD);
  free((void*)boxWk);
  free((void*)boxPup);
  return Ret;
}


