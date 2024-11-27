// ------------------------------------------------------------------
/**
 * @file EdLibThreshold.c
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
//  Function : int ClassicThreshold (EdIMAGE *image, EdIMAGE *imres, unsigned char Th)
//  Parameters : 
//           : image : image .pgm  to threshold using classical procedure
//	         : imres : image .pgm  result image
//           : Th : Threshold value
//  Rule     : Perform a classical threshold 
//  Return   : 0 if OK : 
//
//  Function : int HatThreshold (EdIMAGE *image, EdIMAGE *imres, 
//           : unsigned char ThH, unsigned char ThL)
//  Parameters : 
//           : image : image .pgm  to threshold using classical procedure
//	         : imres : image .pgm  result image
//           : ThH : High Threshold value
//           : ThL : Low Threshold value
//  Rule     : Perform a Hat threshold 
//  Return   : 0 if OK : 
//
//  Function : int MultipleThreshold (EdIMAGE *image, EdIMAGE *imres, 
//           : unsigned char *Th, int nTh)
//  Parameters : 
//           : image : image .pgm  to threshold using classical procedure
//	         : imres : image .pgm  result image
//           : Th : array of Threshold values
//           : nTh: number of Threshold values
//  Rule     : Perform a Multiple threshold 
//  Return   : 0 if OK : 
//
//  Function : int ColorClassification (EdIMAGE *image, EdIMAGE *imres, 
//           : unsigned char Rmax, unsigned char Rmin, 
//           : unsigned char Gmax, unsigned char Gmin,
//           : unsigned char Bmax, unsigned char Bmin,)
//  Parameters : 
//           : image : image .ppm  to color classify
//	         : imres : image .pgm  result image
//           : R, G, B max and min : Threshold values
//  Rule     : Perform a color classification
//  Return   : 0 if OK : 
//
//
#include "EdStructures.h"
#include "EdUtilities.h"
/* ---------------------------------------------------------*/
// ClassicThreshold ----
/** 
 * @brief  Performs Classical Threshold 
 *
 *	@param	image : image .pgm  to threshold
 *	@param	imres : image .pgm threshold
 *	@param   Th : threshold value
 *
 * @return 	0 if OK, 1 if Memory Allocation Problem
 */
 /* ---------------------------------------------------------*/
int ClassicThreshold (EdIMAGE *image, EdIMAGE *imres, unsigned char Th)
{
  EdPOINT	*point = NULL;  /* current point */

  if(crea_POINT(point) == NULL)          /* Memory Allocation of point */
  {
     fprintf(stderr,"Error of Memory Allocation \n");
     system("PAUSE"); // Windows Only
     return 1; 
  }

  /* --- Video Scan of the image  --- */	
  for(POINT_Y(point) = 0; POINT_Y(point) < NLIG(image); 
           POINT_Y(point)++)
  for(POINT_X(point) = 0; POINT_X(point) < NCOL(image); 
           POINT_X(point)++)
  {
    if(PIXEL(image, point) >= Th) 
      PIXEL(imres, point) = 255;   // Level "1"
    else
      PIXEL(imres, point) = 0;     // Level "0"
  }/* --- End of the Image Video Scan --- */
  /* --- Memory Free  --- */
  free((void *)point);
  return 0;
} /* --- End of the Operator --- */   
/* ---------------------------------------------------------*/

// HatThreshold ----
/** 
 * @brief  Performs Hat Threshold 
 *
 *	@param	image : image .pgm  to threshold
 *	@param	imres : image .pgm threshold
 *	@param   ThH : High threshold value
 *	@param   ThL : Low threshold value 
 *
 * @return 	0 if OK, 1 if Memory Allocation Problem
 */
 /* ---------------------------------------------------------*/
int HatThreshold (EdIMAGE *image, EdIMAGE *imres, unsigned char ThH,
    unsigned char ThL)
{
  EdPOINT	*point = NULL;  /* current point */

  if(crea_POINT(point) == NULL)          /* Memory Allocation of point */
  {
     fprintf(stderr,"Error of Memory Allocation \n");
     system("PAUSE"); // Windows Only
     return 1; 
  }

  /* --- Video Scan of the image  --- */	
  for(POINT_Y(point) = 0; POINT_Y(point) < NLIG(image); 
           POINT_Y(point)++)
  for(POINT_X(point) = 0; POINT_X(point) < NCOL(image); 
           POINT_X(point)++)
  {
    if((PIXEL(image, point) >= ThL)&&(PIXEL(image, point) <= ThH))       
      PIXEL(imres, point) = 255;   // Level "1"
    else
      PIXEL(imres, point) = 0;     // Level "0"
  }/* --- End of the Image Video Scan --- */
  /* --- Memory Free  --- */
  free((void *)point);
  return 0;
} /* --- End of the Operator --- */   
/* ---------------------------------------------------------*/

// MultipleThreshold ----
/** 
 * @brief  Performs Multiple Threshold 
 *
 *	@param	image : image .pgm  to threshold
 *	@param	imres : image .pgm threshold image
 *	@param   Th : Array of threshold values
 *	@param   nTh : number of threshold values 
 *
 * @return 	0 if OK, 1 if Memory Allocation Problem
 */
 /* ---------------------------------------------------------*/
int MultipleThreshold (EdIMAGE *image, EdIMAGE *imres, unsigned char *Th,
    int nTh)
{
  EdPOINT	*point = NULL;  /* current point */
  int k;
  
  if(crea_POINT(point) == NULL)          /* Memory Allocation of point */
  {
     fprintf(stderr,"Error of Memory Allocation \n");
     system("PAUSE"); // Windows Only
     return 1; 
  }

  /* --- Video Scan of the image  --- */	
  for(POINT_Y(point) = 0; POINT_Y(point) < NLIG(image); 
           POINT_Y(point)++)
  for(POINT_X(point) = 0; POINT_X(point) < NCOL(image); 
           POINT_X(point)++)
  {
    PIXEL(imres, point) = 0;       
    for (k = 0; k < nTh;k++)
    {
      if(PIXEL(image, point) < Th[k])
        break;       
      else
        PIXEL(imres, point) = 255 * (k + 1) / nTh;    
    } /* --- End of the Loop on Threshold --- */
  }/* --- End of the Image Video Scan --- */
  /* --- Memory Free  --- */
  free((void *)point);
  return 0;
} /* --- End of the Operator --- */   
/* ---------------------------------------------------------*/

// ColorClassification ----
/** 
 * @brief  Performs a Color Classification
 *
 *	@param	image : image .ppm  to color classify
 *	@param	imres : image .pgm classified image
 *	@param  Rmax, Rmin : High and Low threshold values on Red Component
 *	@param  Gmax, Gmin : High and Low threshold values on Green Component 
 *  @param  Bmax, Bmin : High and Low threshold values on Blue Component
 *
 * @return 	0 if OK, 1 if Memory Allocation Problem
 */
 /* ---------------------------------------------------------*/
int ColorClassification (EdIMAGE *image, EdIMAGE *imres, unsigned char Rmax,
    unsigned char Rmin, unsigned char Gmax, unsigned char Gmin,
    unsigned char Bmax, unsigned char Bmin)
{
  EdPOINT	*point = NULL;  /* current point */

  if(crea_POINT(point) == NULL)          /* Memory Allocation of point */
  {
     fprintf(stderr,"Error of Memory Allocation \n");
     system("PAUSE"); // Windows Only
     return 1; 
  }

  /* --- Video Scan of the image  --- */	
  for(POINT_Y(point) = 0; POINT_Y(point) < NLIG(image); 
           POINT_Y(point)++)
  for(POINT_X(point) = 0; POINT_X(point) < NCOL(image); 
           POINT_X(point)++)
  {
    if((PIXEL_R(image, point) >= Rmin)&&(PIXEL_R(image, point) <= Rmax)
      && (PIXEL_V(image, point) >= Gmin)&&(PIXEL_V(image, point) <= Gmax)
      &&(PIXEL_B(image, point) >= Bmin)&&(PIXEL_B(image, point) <= Bmax))       
      PIXEL(imres, point) = 255;   // Level "1"
    else
      PIXEL(imres, point) = 0;     // Level "0"
  }/* --- End of the Image Video Scan --- */
  /* --- Memory Free  --- */
  free((void *)point);
  return 0;
} /* --- End of the Operator --- */   
/* ---------------------------------------------------------*/
