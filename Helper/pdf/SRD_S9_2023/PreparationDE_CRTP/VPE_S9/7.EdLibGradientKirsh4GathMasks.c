// ------------------------------------------------------------------
/**
 * @file EdLibGradientKirsh4SepMask.c
 *
 * @brief Gradient Vector Computation using Kirsh4 algorithm, 
 * under polar coordinate form :  norm and argument
 *
 * The computation requires 4 convolutions, gathered 
 * in our implementation, in an alone image scan.
 * The cordinate transform : from rectangular to polar 
 * is easy and quick to perform.
 *
 *  This file is the part "interface operator" 
 *
 * 
 * @author Patrick Bonnin
 * @email  patrick.bonnin@gmail.com
 * @date 2012.12.01 : integration
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
 * 2012.12.01 : Integration
 */
// ------------------------------------------------------------------

#include "EdStructures.h"
#include "EdLibEdgeUtilities.h"
/* ------------------------------------------------------------ */
/* ---- Gradient Vector Computation :
        Kirsh at 4 Directions algorithm on mono spectral image ---- */

// GradientKirsh4 ----------------------------------------------------
/** 
 * @brief Gradient Vector Computation in norm and argument
 * on a mono spectral image
 *
 *	@param	image		image to be processed.
 *	@param	imnorm		gradient norm image.
 *	@param  imarg		gradient argument image 
 *
 * @return 	none.
 */
// ------------------------------------------------------------------

int GradientKirsh4GathMaskThrThi(EdIMAGE *image, EdIMAGE *imnorm, 
                              EdIMAGE *imarg, EdIMAGE *impts, unsigned char Th)
{
  EdPOINT	*point = NULL, *pointv = NULL; /* curren and neighbour points */
  int	i,j;       /*  column and line index of the neighbourhood  */
  int	grad_x, grad_y;      /*  variable to perform computations */
  int	grad_d, grad_i;
  int   nvois;
  int   ret;
	
  if(crea_POINT(point)== NULL) /* Creation of Points */
  {
     fprintf(stderr,"Pb of MEmory Allocation : EdLibGradientKirsh4 \n");
     return 1;
  }

  if(crea_POINT(pointv)== NULL)
  {
     fprintf(stderr,"Pb of MEmory Allocation : EdLibGradientKirsh4 \n");
     return 1;
  }
  /* --- Initialisation of Image Borders : Set to "0"  --- */
  for(POINT_X(point) = 0; POINT_X(point) < NCOL(image); 
           POINT_X(point)++)
  {
    POINT_Y(point) = 0;                  /* first line */
    PIXEL(imnorm, point) = 0;
    PIXEL(imarg, point) = 0;
    POINT_Y(point) = NLIG(image) - 1;    /* last line */
    PIXEL(imnorm, point) = 0;
    PIXEL(imarg, point) = 0;
  } /*--- End of first and last line initialisation --- */ 

  for(POINT_Y(point) = 0; POINT_Y(point) < NLIG(image); 
           POINT_Y(point)++)
  {
    POINT_X(point) = 0;                  /* first column */
    PIXEL(imnorm, point) = 0;
    PIXEL(imarg, point) = 0;

    POINT_X(point) = NCOL(image) - 1;    /* last column */
    PIXEL(imnorm, point) = 0;
    PIXEL(imarg, point) = 0;
  } /*--- End of first and last column initialisation --- */ 

  /* --- Video Scan of the image, except the Border --- */	
	
  for(POINT_Y(point) = 1; POINT_Y(point) < NLIG(image) - 1; 
           POINT_Y(point)++)
  for(POINT_X(point) = 1; POINT_X(point) < NCOL(image) - 1; 
           POINT_X(point)++)
  {
  
    grad_x = 0;
    grad_y = 0;
    grad_d = 0;
    grad_i = 0;
    
    // Voisin 0
    POINT_X(pointv) = POINT_X(point) + 1; 
    POINT_Y(pointv) = POINT_Y(point);
    grad_x += (int)PIXEL(image, pointv); 
    grad_d += (int)PIXEL(image, pointv); 
    grad_i += (int)PIXEL(image, pointv);  
    
    // Voisin 1
    POINT_Y(pointv) = POINT_Y(point) - 1;
    grad_x += (int)PIXEL(image, pointv); 
    grad_y -= (int)PIXEL(image, pointv); 
    grad_d += (int)PIXEL(image, pointv); 
    
    // Voisin 2
    POINT_X(pointv) = POINT_X(point); 
    grad_y -= (int)PIXEL(image, pointv); 
    grad_d += (int)PIXEL(image, pointv); 
    grad_i -= (int)PIXEL(image, pointv); 
    
    // Voisin 3
    POINT_X(pointv) = POINT_X(point) - 1; 
    grad_x -= (int)PIXEL(image, pointv); 
    grad_y -= (int)PIXEL(image, pointv); 
    grad_i -= (int)PIXEL(image, pointv); 
    
    // Voisin 4
    POINT_Y(pointv) = POINT_Y(point) ; 
    grad_x -= (int)PIXEL(image, pointv); 
    grad_d -= (int)PIXEL(image, pointv); 
    grad_i -= (int)PIXEL(image, pointv); 
    
    // Voisin 5
    POINT_Y(pointv) = POINT_Y(point) + 1 ; 
    grad_x -= (int)PIXEL(image, pointv); 
    grad_y += (int)PIXEL(image, pointv); 
    grad_d -= (int)PIXEL(image, pointv); 
    
    // Voisin 6
    POINT_X(pointv) = POINT_X(point)  ; 
    grad_y += (int)PIXEL(image, pointv); 
    grad_d -= (int)PIXEL(image, pointv); 
    grad_i += (int)PIXEL(image, pointv); 
    
    // Voisin 7
    POINT_X(pointv) = POINT_X(point) + 1; 
    grad_x += (int)PIXEL(image, pointv); 
    grad_y += (int)PIXEL(image, pointv); 
    grad_i += (int)PIXEL(image, pointv); 
    
    grad_x = ((grad_x >= 0) ? grad_x : - grad_x); /* absolute value */
    grad_x /=3;                             /* Normalization */ 
    
    grad_y = ((grad_y >= 0) ? grad_y : - grad_y); /* absolute value */
    grad_y /=3;                             /* Normalization */ 
    
    grad_d = ((grad_d >= 0) ? grad_d : - grad_d); /* absolute value */
    grad_d /=3;                             /* Normalization */ 
    
    grad_i = ((grad_i >= 0) ? grad_i : - grad_i); /* absolute value */
    grad_i /=3;				/* Normalization */ 
    
    PIXEL(imnorm, point) = grad_x;
    PIXEL(imarg, point) = 0;
    
    if (grad_y >  PIXEL(imnorm, point))
    {
      PIXEL(imnorm, point) = grad_y;
      PIXEL(imarg, point) = 2;
    } 
    
    if (grad_d >  PIXEL(imnorm, point))
    {
      PIXEL(imnorm, point) = grad_d;
      PIXEL(imarg, point) = 1;
    } 
    
    if (grad_i >  PIXEL(imnorm, point))
    {
      PIXEL(imnorm, point) = grad_i;
      PIXEL(imarg, point) = 3;
    } 
    /* --- Seuillage et Affinage --- */  
    if (PIXEL(imnorm, point) >= Th)
    { 
      /* --- le point courant est de contour --- */ 
      PIXEL(impts, point) = 255;
      /* --- Recherche Point Voisin dans le Passe --- */
      nvois = (int)PIXEL(imarg, point);
      if ((nvois == 0) || (nvois >= 5))
        nvois = (nvois + 4) % 8;
      
      ret = NeighbourPoint(imnorm, point, pointv, nvois);
      if (ret != 0)
      {
        fprintf(stderr,"Neighbour Points : Outside the image \n");
        return 2; 
      }
     /* --- Affinage proprement dit : selection --- */
     if (PIXEL(imnorm, point) < PIXEL(imnorm, pointv) )
       PIXEL(impts, point) = 0; 
     else if (PIXEL(imnorm, point) > PIXEL(imnorm, pointv) )
       PIXEL(impts, pointv) = 0;
    
    } /* fin si point courant de contour */
    else
      PIXEL(impts, point) = 0;
                               
    
  
  }/* --- fin du balayage de l'image --- */

  free((void *)pointv); 	/* free of point data structure  */
  free((void *)point);
  return 0;
} /* --- End of Operator --- */	











