#include "EdStructures.h"
#include <stdio.h>

int ClassicThreshold(EdIMAGE *imnorm, EdIMAGE *impts, unsigned char Th)
{
    EdPOINT *point = NULL;

    if (crea_POINT(point) == NULL)
    {
        fprintf(stderr, "Error of Memory Allocation for the EdPOINT\n");
        return 1;
    }

    for (POINT_Y(point) = 0; POINT_Y(point) < NLIG(imnorm); POINT_Y(point)++)
    {
        for (POINT_X(point) = 0; POINT_X(point) < NCOL(imnorm); POINT_X(point)++)
        {
            if (PIXEL(imnorm, point) >= Th)
            {
                PIXEL(impts, point) = 255; // Edge point
            }
            else
            {
                PIXEL(impts, point) = 0; // Non-edge point
            }
        }
    }

    free((void *)point);
    return 0;
}