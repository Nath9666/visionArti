// ------------------------------------------------------------------
/**
 * @file EdLibMeanFiltering.c
 *
 * @brief Smooth Filtering using Mean Filter
 * This file is the part "Operator" itself
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
#include "EdStructures.h"

int InitGabarit(EdIMAGE *imMin, EdIMAGE *imMax, EdIMAGE *imCur)
{
  EdPOINT	*point = NULL; /* curren and neighbour points */

   if(crea_POINT(point)== NULL) /* Creation of Points */
  {
     fprintf(stderr,"Pb of MEmory Allocation : EdLibGradientKirsh4 \n");
     return 1;
  }

 for(POINT_Y(point) = 1; POINT_Y(point) < NLIG(imMin) - 1; 
           POINT_Y(point)++)
  for(POINT_X(point) = 1; POINT_X(point) < NCOL(imMin) - 1; 
           POINT_X(point)++)
  {
    PIXEL_R(imMin, point) - PIXEL_R(imCur, point); 
    PIXEL_V(imMin, point) - PIXEL_V(imCur, point);
    PIXEL_B(imMin, point) - PIXEL_B(imCur, point);

    PIXEL_R(imMax, point) - PIXEL_R(imCur, point); 
    PIXEL_V(imMax, point) - PIXEL_V(imCur, point);
    PIXEL_B(imMax, point) - PIXEL_B(imCur, point);
  }
  free((void*)point);

  return 0;
}

//------------------------------------------------------------------
int UpDateGab(EdIMAGE *imMin, EdIMAGE *imMax, EdIMAGE *imCur)
{
  EdPOINT	*point = NULL; /* curren and neighbour points */

   if(crea_POINT(point)== NULL) /* Creation of Points */
  {
     fprintf(stderr,"Pb of MEmory Allocation : EdLibGradientKirsh4 \n");
     return 1;
  }

 for(POINT_Y(point) = 1; POINT_Y(point) < NLIG(imMin) - 1; 
           POINT_Y(point)++)
  for(POINT_X(point) = 1; POINT_X(point) < NCOL(imMin) - 1; 
           POINT_X(point)++)
  {
    if(PIXEL_R(imCur, point) < PIXEL_R(imMin, point))
    {
      PIXEL_R(imMin, point) = PIXEL_R(imCur, point);
    }
    
    if(PIXEL_R(imCur, point) > PIXEL_R(imMax, point))
    {
      PIXEL_R(imMax, point) = PIXEL_R(imCur, point);
    }

    if(PIXEL_V(imCur, point) < PIXEL_V(imMin, point))
    {
      PIXEL_V(imMin, point) = PIXEL_V(imCur, point);
    }

    if(PIXEL_V(imCur, point) > PIXEL_V(imMax, point))
    {
      PIXEL_V(imMax, point) = PIXEL_V(imCur, point);
    }

    if(PIXEL_B(imCur, point) < PIXEL_B(imMin, point))
    {
      PIXEL_B(imMin, point) = PIXEL_B(imCur, point);
    }

    if(PIXEL_B(imCur, point) > PIXEL_B(imMax, point))
    {
      PIXEL_B(imMax, point) = PIXEL_B(imCur, point);
    }

  }
  
  free((void*)point);

  return 0;
}

//------------------------------------------------------------------
int GabMotionDetect(EdIMAGE *imMin, EdIMAGE *imMax, EdIMAGE *imCur, EdIMAGE *imRes)
{
  EdPOINT	*point = NULL; /* curren and neighbour points */

  if(crea_POINT(point)== NULL) /* Creation of Points */
  {
     fprintf(stderr,"Pb of MEmory Allocation : EdLibGradientKirsh4 \n");
     return 1;
  }

  return 0;


{


  if((PIXEL_R(imCur, point) >= PIXEL_R(imMin, point)) && (PIXEL_R(imCur, point) <= PIXEL_R(imMax, point)) 
  && (PIXEL_V(imCur, point) >= PIXEL_V(imMin, point)) && (PIXEL_V(imCur, point) <= PIXEL_V(imMax, point)) 
  && (PIXEL_B(imCur, point) >= PIXEL_B(imMin, point)) && (PIXEL_B(imCur, point) <= PIXEL_B(imMax, point)))
  { //Mouvement détecté

    PIXEL_R(imRes, point) = 255;
    PIXEL_V(imRes, point) = 255;
    PIXEL_B(imRes, point) = 255;
  }
  else
  {
    PIXEL_R(imRes, point) = PIXEL_R(imCur,point); //sinon on met le pixel à blanc
    PIXEL_V(imRes, point) = PIXEL_V(imCur,point);
    PIXEL_B(imRes, point) = PIXEL_B(imCur,point);
  }
}

} /* --- End of the Operator --- */
