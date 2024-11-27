// ------------------------------------------------------------------
/**
 * @file EdLibMotion.c
 *
 * @brief Threshold Procedures : Classic, Hat, Multiple
 * This file is the part "Operator" itself
 * 
 * @author Patrick Bonnin
 * @email  patrick.bonnin@gmail.com
 * @date 2012.11.01 : creation.
 * @date 2013.08.01 : last modification.
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
 * 2013.08.01 : Multiple Threshold Procedure
 */
// ------------------------------------------------------------------

#include "EdStructures.h"
#include "EdUtilities.h"

int DifferenceImage(EdIMAGE *imRef, EdIMAGE *imCur, EdIMAGE *imRes, unsigned char Th)
{
  EdPOINT	*point = NULL;  /* current point */
  int iTh = Th;
  int diff_R, diff_V, diff_B;

  if(crea_POINT(point) == NULL)          /* Memory Allocation of point */
  {
     fprintf(stderr,"Error of Memory Allocation \n");
     system("PAUSE"); // Windows Only
     return 1; 
  }

  /* --- Video Scan of the image  --- */	
  for(POINT_Y(point) = 0; POINT_Y(point) < NLIG(imRef); 
           POINT_Y(point)++)
  for(POINT_X(point) = 0; POINT_X(point) < NCOL(imRef); 
           POINT_X(point)++)
  {
    diff_R = PIXEL_R(imCur, point) - PIXEL_R(imRef, point); 
    diff_V = PIXEL_V(imCur, point) - PIXEL_V(imRef, point); 
    diff_B = PIXEL_B(imCur, point) - PIXEL_B(imRef, point); 
    
    diff_R = diff_R >= 0 ? diff_R : -diff_R;
    diff_V = diff_V >= 0 ? diff_V : -diff_V;
    diff_B = diff_B >= 0 ? diff_B : -diff_B;
    
    if ((diff_R < iTh) && (diff_V < iTh) && (diff_B < iTh))
    { 
      /* --- Pas de Mouvement --- */
      PIXEL(imRes, point) = 0;
    }
    else
    {
    /* ---  Mouvement Détecté --- */
      PIXEL(imRes, point) = 255;
    }
    
  }/* --- End of the Image Video Scan --- */
  /* --- Memory Free  --- */
  free((void *)point);
  return 0;
} /* --- End of the Operator --- */  

/* ------------------------------------------------------- */
int Visualisation(EdIMAGE *imRes, EdIMAGE *imCur, EdIMAGE *imMotion)
{
  EdPOINT	*point = NULL;  /* current point */
  

  if(crea_POINT(point) == NULL)          /* Memory Allocation of point */
  {
     fprintf(stderr,"Error of Memory Allocation \n");
     system("PAUSE"); // Windows Only
     return 1; 
  }

  /* --- Video Scan of the image  --- */	
  for(POINT_Y(point) = 0; POINT_Y(point) < NLIG(imRes); 
           POINT_Y(point)++)
  for(POINT_X(point) = 0; POINT_X(point) < NCOL(imRes); 
           POINT_X(point)++)
  {
    
    
    if (PIXEL(imRes, point) == 0)
    { 
      /* --- Pas de Mouvement --- */
      PIXEL_R(imMotion, point) = 255;
      PIXEL_V(imMotion, point) = 255;
      PIXEL_B(imMotion, point) = 255;
    }
    else
    {
    /* ---  Mouvement Détecté --- */
      PIXEL_R(imMotion, point) = PIXEL_R(imCur, point);
      PIXEL_V(imMotion, point) = PIXEL_V(imCur, point);
      PIXEL_B(imMotion, point) = PIXEL_B(imCur, point);
    }
    
  }/* --- End of the Image Video Scan --- */
  /* --- Memory Free  --- */
  free((void *)point);
  return 0;
} /* --- End of the Operator --- */  


