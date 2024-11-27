// ------------------------------------------------------------------
/**
 * @file EdMotionDiff.c
 *
 * @brief Compte the Gradient Vector (Norm, Argument)
 * using Kirsh 4 algorithm
 *
 * This file is the part "interface with the user" 
 * 
 * @author Patrick Bonnin
 * @email  patrick.bonnin@gmail.com
 * @date 2012.11.01 : creation.
 * @date 2012.11.01 : last modification.
 */
// ------------------------------------------------------------------
/* COPYRIGHT (C)	2012, P. Bonnin <patrick.bonnin@gmail.com>
 *
 * This  library  is  a free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as  published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This  Library  is  distributed in the hope that it will be useful,
 * but  WITHOUT  ANY  WARRANTY;  without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULIAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You  should  have received a copy of the GNU Lesser General Public 
 * License  along  with  this  library;  if  not,  write  to the Free 
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
// ------------------------------------------------------------------
/* Modifications :
 * 2012.11.01 : creation
 */
// ------------------------------------------------------------------
#include <string.h>
#include "EdStructures.h"
#include "EdUtilities.h"
#include "EdLibMotionDiff.h"



int main(int argc, char **argv)
{
  EdIMAGE	    *imRef, *imCur, *imMotion; 
  EdIMAGE           * imRes, *imTmp;
  int	        nlig = 0, ncol = 0;
  unsigned char	prof = 0;
  FILE	        *fichier, *fichRes;
  int           ret;
  int 		iTh;
  unsigned char Th;
  int numFirst, num;
  
  char nom[256], nomGen[256], nomNum[256], nomExt[256];
  char nomImCur[256], nomImRes[256];
  
  /* --- USAGE --- */
  if(argc != 3 )
  {
    fprintf(stderr,"USAGE :  EdMotionDiff  image  Th\n");
    fprintf(stderr,"image : name of the first image \n");
    fprintf(stderr,"Th : Threshol value \n");
    fprintf(stderr,"Compute motion\n");
    exit(0);
  }
  strcpy(nom, *++argv);
  sscanf(nom,"%[^0-9]%[0-9]%*[.]%[pgm]",nomGen, nomNum,nomExt);
  numFirst = atoi(nomNum);
  
  printf("nom : %s, nomGen %s, nomExt %s, num: %d\n", nom, nomGen, nomExt, numFirst);
  
  if (strcmp(nomExt,"pgm") == 0)
    printf("Sequence pgm \n");
  else if (strcmp(nomExt,"ppm") == 0)
    printf("Sequence ppm \n");
  else
  {
    printf("Format non repertorie \n");
    exit(0);
  }
    
  /* --- Recuperation du Seuil --- */
  iTh = atoi(*++argv);
  Th = (unsigned char)iTh;
  
  /* --- Source Image --- */
  if(!(fichier = fopen(nom,"rb")))
  {
    fprintf(stderr,"Source Image %s Pb of Opening\n",nom);
    exit(0);
  } 

  
  /* --- Reading of Image Header --- */
  if ((ret = Reading_ImageHeader(fichier, &ncol, &nlig, &prof)))
  {
    fprintf (stderr, "Problem of Reading Image Header \n");
    exit(0);
  }
  fprintf(stderr, "Size of the Image : %d lines x %d colums : Type : %d\n", nlig,ncol, (int)prof);  
  
  /* --- Creation of Images Header and Data --- */
  if (crea_IMAGE(imRef) == NULL)	/* creation of Image Header  */
  {
    fprintf(stderr,"Error of Memory Allocation  \n");
    exit (0);
  }
  ret = Creation_Image (imRef, nlig, ncol, prof); // Image Data
  if (!ret)
  {
    fprintf(stderr,"Error of Memory Allocation of Pixels  \n");
    exit (0);
  }
 
  if (crea_IMAGE(imCur) == NULL) 
  {
    fprintf(stderr,"Error of Memory Allocation  \n");
    exit (0);
  }
  ret = Creation_Image (imCur, nlig, ncol, prof);
  if (!ret)
  {
    fprintf(stderr,"Error of Memory Allocation of Pixels  \n");
    exit (0);
  }

  if (crea_IMAGE(imMotion) == NULL) 
  {
    fprintf(stderr,"Error of Memory Allocation  \n");
    exit (0);
  }
  ret = Creation_Image (imMotion, nlig, ncol, prof);
  if (!ret)
  {
    fprintf(stderr,"Error of Memory Allocation of Pixels  \n");
    exit (0);
  } 
  
  prof = 1;
  if (crea_IMAGE(imRes) == NULL) 
  {
    fprintf(stderr,"Error of Memory Allocation  \n");
    exit (0);
  }
  ret = Creation_Image (imRes, nlig, ncol, prof);
  if (!ret)
  {
    fprintf(stderr,"Error of Memory Allocation of Pixels  \n");
    exit (0);
  }
  
  if (crea_IMAGE(imTmp) == NULL) 
  {
    fprintf(stderr,"Error of Memory Allocation  \n");
    exit (0);
  }
  ret = Creation_Image (imTmp, nlig, ncol, prof);
  if (!ret)
  {
    fprintf(stderr,"Error of Memory Allocation of Pixels  \n");
    exit (0);
  }
  
  /* --- Reading of Image Data from file to Memory --- */
  ret = Reading_ImageData(fichier,imRef); // Image Pixel Data
  if (!ret)
  {
    fprintf(stderr,"Problem of Reading \n");
    system ("PAUSE"); // Windows Only
    exit(0);
  }
  fclose (fichier);
  num = numFirst; 
  
  /* --- Boucle de Lecture --- */
  while (1)
  {
    num += 1;
    sprintf(nomImCur,"%s%04d.%s",nomGen, num, nomExt);
    sprintf(nomImRes,"%sRes%04d.%s",nomGen, num, nomExt);
    printf("nom de l'image source : %s, resultat %s \n", 
      nomImCur, nomImRes);
    
    if(!(fichier = fopen(nomImCur,"rb")))
    {
      fprintf(stderr,"Source Image %s Pb of Opening\n",nomImCur);
      break;
    } 
    
    if(!(fichRes = fopen(nomImRes,"wb")))
    {
      fprintf(stderr,"Source Image %s Pb of Opening\n",nomImRes);
      break;
    } 
 
    /* --- Reading of Image Header --- */
    if ((ret = Reading_ImageHeader(fichier, &ncol, &nlig, &prof)))
    {
      fprintf (stderr, "Problem of Reading Image Header \n");
      exit(0);
    }

    /* --- Reading of Image Data from file to Memory --- */
    ret = Reading_ImageData(fichier,imCur); // Image Pixel Data
    if (!ret)
    {
      fprintf(stderr,"Problem of Reading \n");
      exit(0);
    }
    fclose (fichier);
    
    /* --- Motion Detection --- */
    ret = DifferenceImage(imRef, imCur, imRes, Th);
    
    /* --- Filtrages Spatial --- */
    /* --- Ouverture --- */
    ret = Erosion3(imRes, imTmp);
    ret = Dilatation3(imTmp, imRes);
    
    /* --- Fermeture --- */
    ret = Dilatation3(imRes, imTmp);
    ret = Erosion3(imTmp, imRes);
    
    /* --- Visualisation --- */
    ret = Visualisation(imRes, imCur, imMotion);
    
    
    /* --- Writing of the Image Result --- */
    fprintf(fichRes,"P6\n#creating by EdEnviTI\n%d %d\n255\n",(int)ncol, (int)nlig); // Header 
    ret = Writing_ImageData(fichRes, imMotion); // Image Pixel Data
    if (!ret)
    {
      fprintf(stderr,"Problem of Writing \n");
      exit(0);
    }
    fclose (fichRes);

     
  } /* Fin boucle de Traitements */
#if 0  
  /* --- Gradient Vecteur Comutation : Kirsh4 Algorithm --- */
  ret = GradientKirsh4SepMask (image, imnorm, imarg); 
  if (ret)
  {
    fprintf(stderr,"Problem of Memory Allocation in Kirsh 4 Operator \n");
    system ("PAUSE"); // Windows Only
    exit(0);
  }
  /* --- Threshold --- */
  ret =  ClassicThreshold (imnorm, impts, Th);
  if (ret)
  {
    fprintf(stderr,"Problem of Memory Allocation in Kirsh 4 Operator \n");
    system ("PAUSE"); // Windows Only
    exit(0);
  }
  #if 0
  /* --- Thinning --- */
  ret = ThinningEdges (imnorm, imarg, impts);
  if (ret)
  {
    fprintf(stderr,"Problem of Memory Allocation in Kirsh 4 Operator \n");
    system ("PAUSE"); // Windows Only
    exit(0);
  }
  #endif

  /* --- Writing of the Images Result in File : Norm and Argument --- */
  fprintf(fichnorm,"P5\n#creating by EdEnviTI\n%d %d\n255\n",(int)ncol, (int)nlig); // Header 
  ret = Writing_ImageData(fichnorm, imnorm); // Image Pixel Data
  if (!ret)
  {
    fprintf(stderr,"Problem of Writing \n");
    system ("PAUSE"); // Windows Only
    exit(0);
  }

  fprintf(ficharg,"P5\n#creating by EdEnviTI\n%d %d\n255\n",(int)ncol, (int)nlig); // Header 
  ret = Writing_ImageData(ficharg, impts); // Image Pixel Data
  if (!ret)
  {
    fprintf(stderr,"Problem of Writing \n");
    system ("PAUSE"); // Windows Only
    exit(0);
  }
/* --- Free of Images --- */
  ret = Free_Image(image);
  if(ret == FALSE)
  {
    fprintf(stderr,"Problem of Free the Memory \n");
  }
  ret = Free_Image(imnorm);
  if(ret == FALSE)
  {
    fprintf(stderr,"Problem of Free the Memory \n");
  }
  ret = Free_Image(imarg);
  if(ret == FALSE)
  {
    fprintf(stderr,"Problem of Free the Memory \n");
  }
  
  fclose (fichier);
  fclose (fichnorm);
  fclose (ficharg);
 #endif 
 	
  fprintf(stderr,"End of Motion Detection Operator\n");
  
  return 0;
}
