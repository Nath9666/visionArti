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


int MotionDetect(EdIMAGE *imRef, EdIMAGE *imCur, EdIMAGE *imRes, int iTh)
{
  EdPOINT	*point = NULL; /* curren and neighbour points */
  int diff_R, diff_V, diff_B;
  if(crea_POINT(point)== NULL) /* Creation of Points */
  {
     fprintf(stderr,"Pb of MEmory Allocation : EdLibGradientKirsh4 \n");
     return 1;
  }

  return 0;

for(POINT_Y(point) = 1; POINT_Y(point) < NLIG(imRef) - 1; 
           POINT_Y(point)++)
for(POINT_X(point) = 1; POINT_X(point) < NCOL(imRef) - 1; 
           POINT_X(point)++)
{
  diff_R = PIXEL_R(imCur, point) - PIXEL_R(imRef, point); //différence entre l'image de référence et l'image courante
  diff_V = PIXEL_V(imCur, point) - PIXEL_V(imRef, point);
  diff_B = PIXEL_B(imCur, point) - PIXEL_B(imRef, point);

  diff_R = (diff_R >= 0) ? diff_R : -diff_R; //valeur absolue
  diff_V = (diff_V >= 0) ? diff_V : -diff_V;
  diff_B = (diff_B >= 0) ? diff_B : -diff_B;

  if(diff_R >= iTh || diff_V >= iTh || diff_B >= iTh) //si la différence est supérieure au seuil
  { //Mouvement détecté

    PIXEL_R(imRes, point) = PIXEL_R(imCur,point); //on met le pixel de l'image courante dans l'image résultante
    PIXEL_V(imRes, point) = PIXEL_V(imCur,point);
    PIXEL_B(imRes, point) = PIXEL_B(imCur,point);
  }
  else
  {
    PIXEL_R(imRes, point) = 255; //sinon on met le pixel à blanc
    PIXEL_V(imRes, point) = 255;
    PIXEL_B(imRes, point) = 255;
  }
}

} /* --- End of the Operator --- */
