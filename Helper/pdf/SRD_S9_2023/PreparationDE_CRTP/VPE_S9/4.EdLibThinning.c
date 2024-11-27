// ------------------------------------------------------------------
/**
 * @file EdLibThinning.c
 *
 * @brief Operateur of Edge (Point) Thinning. 
 *
 * The thinning step is independant of the gradient computation.
 * It requires : the gradient norm (coded [0,255]), the gradient argument 
 * (coded [0,8]), and the edge point information.
 * This is the basis algorithm looking at the two neighbour points 
 * of the current pixel : one on the past, the other on the futur.
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
//
//  fonction : void ThinningEdges (EdIMAGE *imnorm, EdIMAGE *imarg, 
//           : EdIMAGE *impts)
//  Rule     : Perform the thinning processing in keeping edge point
//           : whose norm is local (3x3 neighbourhood) maximal and directional
//           : in the direction of gradient
//


#include "EdStructures.h"
#include "EdLibEdgeUtilities.h"


/* ------------------------------------------------------------ */
/* ---- Thinning Operateur in two directions ---- */

// ThinningEdges ----------------------------------------------------
/** 
 * @brief  Perform the thinning processing in keeping edge point
 * whose norm is local (3x3 neighbourhood) maximal and directional
 * in the direction of gradient
 *
 *	@param	imnorm		image of gradient norm 
 *	@param	imarg       image of gradient argument
 *	@param  impts       image of edge points
 *
 * @return 	0 : No problem.
 */
// ------------------------------------------------------------------

int ThinningEdges (EdIMAGE *imnorm, EdIMAGE *imarg, EdIMAGE *impts)
{
  EdPOINT    *point = NULL; /* current point */
  EdPOINT    *pointv1 = NULL, *pointv2 = NULL; /* neighbour points  */
  int        nvois1, nvois2; /* direction of neighbour points */
  int        ret;
  
  if(crea_POINT(point) == NULL)
  {
    fprintf(stderr,"Error of MEmory Allocation for the EdPOINT \n");
    return 1;
  }

  if(crea_POINT(pointv1) == NULL)
  {
    fprintf(stderr,"Error of MEmory Allocation for the EdPOINT\n");
    return 1;
  }

  if(crea_POINT(pointv2) == NULL)
  {
    fprintf(stderr,"Error of MEmory Allocation for the EdPOINT \n");
    return 1;
  }
  	
  /* --- Video Scan of the image, except the Border --- */
  for(POINT_Y(point) = 1; POINT_Y(point) < NLIG(imnorm) - 1; 
            POINT_Y(point)++)
  for(POINT_X(point) = 1; POINT_X(point) < NCOL(imnorm) - 1; 
            POINT_X(point)++)
  {
    if(PIXEL(impts, point) == 255) /* Edge point */
    {
      /* --- Search of the two Neighbours  --- */
          nvois1 = (int)PIXEL(imarg, point);
	  nvois2 = (nvois1 + 4) % 8;
	 
	  ret = NeighbourPoint(imnorm, point, pointv1, nvois1);
	  ret += NeighbourPoint(imnorm, point, pointv2, nvois2);
	  if (ret != 0)
	  {
        fprintf(stderr,"Neighbour Points : Outside the image \n");
        return 2; 
      }

      if((PIXEL(imnorm, point) < PIXEL(imnorm, pointv1)) ||
	    (PIXEL(imnorm, point) < PIXEL(imnorm, pointv2)))
        PIXEL(impts, point) = 0; /* No more edge point */
    } /* fin si le point courant est de contour */
  }/* --- End of the Video Scan --- */
  free((void *)pointv1); 	/* --- free of memory --- */
  free((void *)pointv2);
  free((void *)point);
  return 0; /* Correct End */
} /* --- End of Thinning operateur --- */	

