#include "EdStructures.h"
#include <stdio.h>

int ThinningEdges(EdIMAGE *imnorm, EdIMAGE *imarg, EdIMAGE *impts)
{
    EdPOINT *point = NULL, *pointv1 = NULL, *pointv2 = NULL;
    int nvois1, nvois2, ret;

    if (crea_POINT(point) == NULL || crea_POINT(pointv1) == NULL || crea_POINT(pointv2) == NULL)
    {
        fprintf(stderr, "Error of Memory Allocation for the EdPOINT\n");
        return 1;
    }

    for (POINT_Y(point) = 1; POINT_Y(point) < NLIG(imnorm) - 1; POINT_Y(point)++)
    {
        for (POINT_X(point) = 1; POINT_X(point) < NCOL(imnorm) - 1; POINT_X(point)++)
        {
            if (PIXEL(impts, point) == 255) // Edge point
            {
                nvois1 = (int)PIXEL(imarg, point);
                nvois2 = (nvois1 + 4) % 8;

                ret = NeighbourPoint(imnorm, point, pointv1, nvois1);
                ret += NeighbourPoint(imnorm, point, pointv2, nvois2);
                if (ret != 0)
                {
                    fprintf(stderr, "Neighbour Points : Outside the image\n");
                    return 2;
                }

                if ((PIXEL(imnorm, point) < PIXEL(imnorm, pointv1)) || (PIXEL(imnorm, point) < PIXEL(imnorm, pointv2)))
                {
                    PIXEL(impts, point) = 0; // No more edge point
                }
            }
        }
    }

    free((void *)pointv1);
    free((void *)pointv2);
    free((void *)point);
    return 0;
}