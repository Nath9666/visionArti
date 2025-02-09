// ------------------------------------------------------------------
/**
 * @file EdLibMotionDetectFond.c
 *
 * @brief Motion Detection using Background Subtraction Method
 * This file contains the function for detecting motion using the background subtraction method.
 *
 * @date 2025.02.09 : creation.
 * @date 2025.02.09 : last modification.
 */
// ------------------------------------------------------------------
/* COPYRIGHT (C)	2025, <Your Name>
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
 * 2025.02.09 : creation
 */
// ------------------------------------------------------------------
#include "EdStructures.h"

// ------------------------------------------------------------------
/**
 * @brief Motion Detection using Background Subtraction Method
 * This function performs motion detection by comparing the current image
 * with the background image using a simple difference method.
 *
 * @param imBg Pointer to the background image
 * @param imCur Pointer to the current image
 * @param imRes Pointer to the result image
 * @param iTh Threshold for motion detection
 * @param alpha Coefficient for updating the background image
 *
 * @return 0 if successful, 1 otherwise
 */
// ------------------------------------------------------------------
int MotionDetectBg(EdIMAGE *imBg, EdIMAGE *imCur, EdIMAGE *imRes, int iTh, float alpha) {
    EdPOINT *point = NULL; /* current and neighbour points */
    int diff_R, diff_V, diff_B;

    if (crea_POINT(point) == NULL) { /* Creation of Points */
        fprintf(stderr, "Pb of Memory Allocation : EdLibMotionDetect \n");
        return 1;
    }

    for (POINT_Y(point) = 1; POINT_Y(point) < NLIG(imBg) - 1; POINT_Y(point)++) {
        for (POINT_X(point) = 1; POINT_X(point) < NCOL(imBg) - 1; POINT_X(point)++) {
            diff_R = PIXEL_R(imCur, point) - PIXEL_R(imBg, point); // différence entre l'image de fond et l'image courante
            diff_V = PIXEL_V(imCur, point) - PIXEL_V(imBg, point);
            diff_B = PIXEL_B(imCur, point) - PIXEL_B(imBg, point);

            diff_R = (diff_R >= 0) ? diff_R : -diff_R; // valeur absolue
            diff_V = (diff_V >= 0) ? diff_V : -diff_V;
            diff_B = (diff_B >= 0) ? diff_B : -diff_B;

            if (diff_R > iTh || diff_V > iTh || diff_B > iTh) { // si la différence est supérieure au seuil
                // Mouvement détecté
                PIXEL_R(imRes, point) = PIXEL_R(imCur, point); // on met le pixel de l'image courante dans l'image résultante
                PIXEL_V(imRes, point) = PIXEL_V(imCur, point);
                PIXEL_B(imRes, point) = PIXEL_B(imCur, point);

                // Pas de mise à jour de l'image de fond
                PIXEL_R(imBg, point) = PIXEL_R(imBg, point);
                PIXEL_V(imBg, point) = PIXEL_V(imBg, point);
                PIXEL_B(imBg, point) = PIXEL_B(imBg, point);
            } else {
                // Pas de mouvement détecté
                PIXEL_R(imRes, point) = 0; // on met le pixel à noir
                PIXEL_V(imRes, point) = 0;
                PIXEL_B(imRes, point) = 0;

                // Mise à jour de l'image de fond
                PIXEL_R(imBg, point) = (unsigned char)(alpha * PIXEL_R(imCur, point) + (1 - alpha) * PIXEL_R(imBg, point));
                PIXEL_V(imBg, point) = (unsigned char)(alpha * PIXEL_V(imCur, point) + (1 - alpha) * PIXEL_V(imBg, point));
                PIXEL_B(imBg, point) = (unsigned char)(alpha * PIXEL_B(imCur, point) + (1 - alpha) * PIXEL_B(imBg, point));
            }
        }
    }

    free((void*)point);
    return 0;
}