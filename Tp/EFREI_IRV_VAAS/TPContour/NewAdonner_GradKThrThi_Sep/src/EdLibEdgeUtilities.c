// ------------------------------------------------------------------
/**
 * @file EdLibEdgeUtilities.c
 *
 * @brief General Functionnalities used by Edge Detection Operators
 *
 *
 * @author Patrick Bonnin
 * @email  patrick.bonnin@gmail.com
 * @date 2012.12.15 : integration
 */
// ------------------------------------------------------------------
/* COPYRIGHT (C)	2012, P. Bonnin <patrick.bonnin@.gmail.com>
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
 * 2012.12.15 : Integration
 */
// ------------------------------------------------------------------
//  function : int NeighbourPoint(EdPOINT *point, EdPOINT *pointv, int nvois)
//  Rule     : Compute the image coordinates of the neighbour point 
//	         : knowing its number of neighbourhood, according to the freeman code
//
//  fonction : int IndexNeighbourPoint(EdPOINT *point, 
//           : EdPOINT *pointv, int *pIndex)
//  Rule     : Gives the Index according to Freeman Code or the direction 
//           :  of the Neighbour point pointv, in the neighbourhood 
//           : of the current point point.

#include "EdStructures.h"


#define DEBUGFRENCH 0
/* ------------------------------------------------------*/
int NeighbourPoint(EdIMAGE *im, EdPOINT *point, EdPOINT *pointv, int nvois)
{
  switch (nvois)
  {
    case 0:
      POINT_X(pointv) = POINT_X(point) + 1;
	  POINT_Y(pointv) = POINT_Y(point);
	  break;
     
    case 1:
      POINT_X(pointv) = POINT_X(point) + 1;
	  POINT_Y(pointv) = POINT_Y(point) - 1;
	  break;
		
    case 2:
      POINT_X(pointv) = POINT_X(point);
	  POINT_Y(pointv) = POINT_Y(point) - 1;
	  break;
		
    case 3:
      POINT_X(pointv) = POINT_X(point) - 1;
	  POINT_Y(pointv) = POINT_Y(point) - 1;
      break;
		
    case 4:
	  POINT_X(pointv) = POINT_X(point) - 1;
	  POINT_Y(pointv) = POINT_Y(point);
	  break;
		
    case 5:
	  POINT_X(pointv) = POINT_X(point) - 1;
	  POINT_Y(pointv) = POINT_Y(point) + 1;
	  break;
		
    case 6:
	  POINT_X(pointv) = POINT_X(point);
	  POINT_Y(pointv) = POINT_Y(point) + 1;
	  break;
      
    case 7:
	  POINT_X(pointv) = POINT_X(point) + 1;
	  POINT_Y(pointv) = POINT_Y(point) + 1;
      break;
		
    default:
     fprintf (stderr," NeighbourPoint : Index impossible \n");
     return 1;
  } /* --- end of switch --- */	
/* --- Verification : the neighbour point is inside the image --- */
  if((POINT_X(pointv) < 0) || (POINT_Y(pointv) < 0) || 
                    (POINT_X(pointv) >= NCOL(im)) || 
                    (POINT_Y(pointv) >= NLIG(im)))
  {
      fprintf (stderr," NeighbourPoint : Out of Image \n");
      return 2;
  }
  return 0;	
} /* --- end NeighbourPoint --- */
/* ---------------------------------------------------------------------*/
// IndexNeighbourPoint ----------------------------------------------------
/** 
 * @brief  Gives the Index according to Freeman Code or the direction 
 * of the Neighbour point pointv, in the neighbourhood of the current point point.
 *	@param	point		current point 
 *	@param  pointv		neighbour point 
 *  @param  pnvois      pointer on the index of the neighbour point
 *
 * @return 	0, if OK.
 */
// ------------------------------------------------------------------
/* ------------------------------------------------------*/
int IndexNeighbourPoint(EdPOINT *point, EdPOINT *pointv, int *pIndex)
{
  int difx, dify; /* x and y differences */

  difx = POINT_X(pointv) - POINT_X(point);
  dify = POINT_Y(pointv) - POINT_Y(point);

  switch (difx)
  {
    case -1:
    switch (dify)
    {
      case -1:
        *pIndex = 3;
        break;
      case	0:
        *pIndex = 4;
		break;
      case 	1:
        *pIndex = 5;
        break;
      default:
        fprintf(stderr,"Coordinate Error on Y of  the Neighbour Point\n");
        return 1;
    }
    break;
    
    case	0:
	switch (dify)
   	{
	  case -1:
	    *pIndex = 2;
	    break;
	  case	0:
	    *pIndex = 8; /* central point  */
	    break;
	  case 	1:
	    *pIndex = 6;
	    break;
	  default:
	    fprintf(stderr,"Coordinate Error on Y of  the Neighbour Point \n");
	    return 1;
	}
	break;
   
    case 	1:
    switch (dify)
    {
      case -1:
        *pIndex = 1;
        break;
      case	0:
        *pIndex = 0;
        break;
      case 	1:
        *pIndex = 7;
        break;
      default:
        fprintf(stderr,"Coordinate Error on Y of  the Neighbour Point \n");
        return 1;
    }
    break;
    default:
      fprintf(stderr,"Coordinate Error on X of  the Neighbour Point\n");
      return 1;
  }
  return 0;
} /* --- End of Operator :  IndexNeighbourPoint--- */

