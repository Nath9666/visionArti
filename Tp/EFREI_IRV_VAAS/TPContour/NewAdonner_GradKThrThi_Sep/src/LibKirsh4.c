#include <stdio.h>
#include <stdlib.h>
#include "EdStructures.h"
#include "LibKirsh4.h"

int GradientKirsh4(EdIMAGE *image, EdIMAGE *imnorm, EdIMAGE *imarg)
{
    EdPOINT *point = NULL, *pointv = NULL; /* current and neighbour points */
    int grad, i, j; /* variables for gradient computation */
    unsigned char pixel; /* temporary variable */

    if (crea_POINT(point) == NULL) /* Creation of Points */
    {
        fprintf(stderr, "Pb of Memory Allocation : LibKirsh4 \n");
        return 1;
    }

    if (crea_POINT(pointv) == NULL)
    {
        fprintf(stderr, "Pb of Memory Allocation : LibKirsh4 \n");
        return 1;
    }

    /* --- Initialisation of Image Borders : Set to "0"  --- */
    for (POINT_X(point) = 0; POINT_X(point) < NCOL(image); POINT_X(point)++)
    {
        POINT_Y(point) = 0; /* first line */
        PIXEL(imnorm, point) = 0;
        PIXEL(imarg, point) = 0;
        POINT_Y(point) = NLIG(image) - 1; /* last line */
        PIXEL(imnorm, point) = 0;
        PIXEL(imarg, point) = 0;
    }

    for (POINT_Y(point) = 0; POINT_Y(point) < NLIG(image); POINT_Y(point)++)
    {
        POINT_X(point) = 0; /* first column */
        PIXEL(imnorm, point) = 0;
        PIXEL(imarg, point) = 0;
        POINT_X(point) = NCOL(image) - 1; /* last column */
        PIXEL(imnorm, point) = 0;
        PIXEL(imarg, point) = 0;
    }

    /* --- Video Scan of the image, except the Border --- */
    for (POINT_Y(point) = 1; POINT_Y(point) < NLIG(image) - 1; POINT_Y(point)++)
    {
        for (POINT_X(point) = 1; POINT_X(point) < NCOL(image) - 1; POINT_X(point)++)
        {
            /* --- First Mask : Horizontal Gradients (0 degrees) --- */
            grad = 0; /* initialisation */
            POINT_X(pointv) = POINT_X(point) - 1;
            POINT_Y(pointv) = POINT_Y(point) - 1;
            grad -= (int)PIXEL(image, pointv); /* M(0,0) = -1 */
            POINT_Y(pointv) = POINT_Y(point);
            grad -= (int)PIXEL(image, pointv); /* M(0,1) = -1 */
            POINT_Y(pointv) = POINT_Y(point) + 1;
            grad -= (int)PIXEL(image, pointv); /* M(0,2) = -1 */
            POINT_X(pointv) = POINT_X(point) + 1;
            POINT_Y(pointv) = POINT_Y(point) - 1;
            grad += (int)PIXEL(image, pointv); /* M(2,0) = 1 */
            POINT_Y(pointv) = POINT_Y(point);
            grad += (int)PIXEL(image, pointv); /* M(2,1) = 1 */
            POINT_Y(pointv) = POINT_Y(point) + 1;
            grad += (int)PIXEL(image, pointv); /* M(2,2) = 1 */
            grad = ((grad >= 0) ? grad : -grad); /* absolute value */
            grad /= 3; /* Normalization */
            PIXEL(imnorm, point) = (unsigned char)grad;
            PIXEL(imarg, point) = 0;

            /* --- Second Mask : Gradients of 45 degrees --- */
            grad = 0; /* initialisation */
            POINT_X(pointv) = POINT_X(point) - 1;
            POINT_Y(pointv) = POINT_Y(point);
            grad -= (int)PIXEL(image, pointv); /* M(0,1) = -1 */
            POINT_Y(pointv) = POINT_Y(point) + 1;
            grad -= (int)PIXEL(image, pointv); /* M(0,2) = -1 */
            POINT_X(pointv) = POINT_X(point);
            POINT_Y(pointv) = POINT_Y(point) - 1;
            grad += (int)PIXEL(image, pointv); /* M(1,0) = 1 */
            POINT_Y(pointv) = POINT_Y(point) + 1;
            grad -= (int)PIXEL(image, pointv); /* M(1,2) = -1 */
            POINT_X(pointv) = POINT_X(point) + 1;
            POINT_Y(pointv) = POINT_Y(point) - 1;
            grad += (int)PIXEL(image, pointv); /* M(2,0) = 1 */
            POINT_Y(pointv) = POINT_Y(point);
            grad += (int)PIXEL(image, pointv); /* M(2,1) = 1 */
            grad = ((grad >= 0) ? grad : -grad); /* Absolute Value */
            grad /= 3; /* Normalization */
            pixel = (unsigned char)grad;
            if (pixel > PIXEL(imnorm, point))
            {
                PIXEL(imnorm, point) = pixel;
                PIXEL(imarg, point) = 1;
            }

            /* --- Third Mask : Vertical Gradients (90 degrees) --- */
            grad = 0; /* initialisation */
            POINT_Y(pointv) = POINT_Y(point) - 1;
            POINT_X(pointv) = POINT_X(point) - 1;
            grad -= (int)PIXEL(image, pointv); /* M(0,0) = -1 */
            POINT_X(pointv) = POINT_X(point);
            grad -= (int)PIXEL(image, pointv); /* M(1,0) = -1 */
            POINT_X(pointv) = POINT_X(point) + 1;
            grad -= (int)PIXEL(image, pointv); /* M(2,0) = -1 */
            POINT_Y(pointv) = POINT_Y(point) + 1;
            POINT_X(pointv) = POINT_X(point) - 1;
            grad += (int)PIXEL(image, pointv); /* M(0,2) = 1 */
            POINT_X(pointv) = POINT_X(point);
            grad += (int)PIXEL(image, pointv); /* M(1,2) = 1 */
            POINT_X(pointv) = POINT_X(point) + 1;
            grad += (int)PIXEL(image, pointv); /* M(2,2) = 1 */
            grad = ((grad >= 0) ? grad : -grad); /* Absolute Value */
            grad /= 3; /* Normalisation */
            pixel = (unsigned char)grad;
            if (pixel > PIXEL(imnorm, point))
            {
                PIXEL(imnorm, point) = pixel;
                PIXEL(imarg, point) = 6;
            }

            /* --- Fourth Mask : Gradients of -45 degrees --- */
            grad = 0; /* initialisation */
            POINT_Y(pointv) = POINT_Y(point) - 1;
            POINT_X(pointv) = POINT_X(point) - 1;
            grad -= (int)PIXEL(image, pointv); /* M(0,0) = -1 */
            POINT_X(pointv) = POINT_X(point);
            grad -= (int)PIXEL(image, pointv); /* M(1,0) = -1 */
            POINT_Y(pointv) = POINT_Y(point);
            POINT_X(pointv) = POINT_X(point) + 1;
            grad += (int)PIXEL(image, pointv); /* M(2,1) = 1 */
            POINT_X(pointv) = POINT_X(point) - 1;
            grad -= (int)PIXEL(image, pointv); /* M(0,1) = -1 */
            POINT_Y(pointv) = POINT_Y(point) + 1;
            POINT_X(pointv) = POINT_X(point);
            grad += (int)PIXEL(image, pointv); /* M(1,2) = 1 */
            POINT_X(pointv) = POINT_X(point) + 1;
            grad += (int)PIXEL(image, pointv); /* M(2,2) = 1 */
            grad = ((grad >= 0) ? grad : -grad); /* Absolute Value */
            grad /= 3; /* Normalization */
            pixel = (unsigned char)grad;
            if (pixel > PIXEL(imnorm, point))
            {
                PIXEL(imnorm, point) = pixel;
                PIXEL(imarg, point) = 7;
            }
        }
    }

    free((void *)pointv); /* free of point data structure */
    free((void *)point);
    return 0;
}

int main(int argc, char **argv)
{
    EdIMAGE *image = NULL, *imnorm = NULL, *imarg = NULL;
    int nlig = 0, ncol = 0;
    unsigned char prof = 0;
    FILE *fichier = NULL, *fichnorm = NULL, *ficharg = NULL;
    int ret;

    /* --- USAGE --- */
    if (argc != 4)
    {
        fprintf(stderr, "USAGE : LibKirsh4 image imnorm imarg\n");
        fprintf(stderr, "image : name of the image to filter \n");
        fprintf(stderr, "imnorm : name of the image of the norm of the gradient \n");
        fprintf(stderr, "imarg : name of the image of the argument of the gradient \n");
        exit(0);
    }

    /* --- Source Image --- */
    if (!(fichier = fopen(argv[1], "rb")))
    {
        fprintf(stderr, "Source Image %s Pb of Opening\n", argv[1]);
        exit(0);
    }

    /* --- Result Images : Norm & Argument  --- */
    if (!(fichnorm = fopen(argv[2], "wb")))
    {
        fprintf(stderr, "Norm Result Image %s Pb of Opening\n", argv[2]);
        fclose(fichier);
        exit(0);
    }

    if (!(ficharg = fopen(argv[3], "wb")))
    {
        fprintf(stderr, "Argument Result Image %s Pb of Opening\n", argv[3]);
        fclose(fichier);
        fclose(fichnorm);
        exit(0);
    }

    /* --- Reading of Image Header --- */
    if ((ret = Reading_ImageHeader(fichier, &ncol, &nlig, &prof)))
    {
        fprintf(stderr, "Problem of Reading Image Header \n");
        fclose(fichier);
        fclose(fichnorm);
        fclose(ficharg);
        exit(0);
    }
    fprintf(stderr, "Size of the Image : %d lines x %d columns : Type : %d\n", nlig, ncol, (int)prof);
    if (prof != 1)
    {
        fprintf(stderr, "The source image is not a B&W image \n");
        fclose(fichier);
        fclose(fichnorm);
        fclose(ficharg);
        exit(0);
    }

    /* --- Creation of Images Header and Data --- */
    if (crea_IMAGE(image) == NULL)
    {
        fprintf(stderr, "Error of Memory Allocation \n");
        fclose(fichier);
        fclose(fichnorm);
        fclose(ficharg);
        exit(0);
    }
    ret = Creation_Image(image, nlig, ncol, prof);
    if (!ret)
    {
        fprintf(stderr, "Error of Memory Allocation of Pixels \n");
        Free_Image(image);
        fclose(fichier);
        fclose(fichnorm);
        fclose(ficharg);
        exit(0);
    }

    if (crea_IMAGE(imnorm) == NULL)
    {
        fprintf(stderr, "Error of Memory Allocation \n");
        Free_Image(image);
        fclose(fichier);
        fclose(fichnorm);
        fclose(ficharg);
        exit(0);
    }
    ret = Creation_Image(imnorm, nlig, ncol, prof);
    if (!ret)
    {
        fprintf(stderr, "Error of Memory Allocation of Pixels \n");
        Free_Image(image);
        Free_Image(imnorm);
        fclose(fichier);
        fclose(fichnorm);
        fclose(ficharg);
        exit(0);
    }

    if (crea_IMAGE(imarg) == NULL)
    {
        fprintf(stderr, "Error of Memory Allocation \n");
        Free_Image(image);
        Free_Image(imnorm);
        fclose(fichier);
        fclose(fichnorm);
        fclose(ficharg);
        exit(0);
    }
    ret = Creation_Image(imarg, nlig, ncol, prof);
    if (!ret)
    {
        fprintf(stderr, "Error of Memory Allocation of Pixels \n");
        Free_Image(image);
        Free_Image(imnorm);
        Free_Image(imarg);
        fclose(fichier);
        fclose(fichnorm);
        fclose(ficharg);
        exit(0);
    }

    /* --- Reading of Image Data from file to Memory --- */
    ret = Reading_ImageData(fichier, image);
    if (!ret)
    {
        fprintf(stderr, "Problem of Reading \n");
        Free_Image(image);
        Free_Image(imnorm);
        Free_Image(imarg);
        fclose(fichier);
        fclose(fichnorm);
        fclose(ficharg);
        exit(0);
    }

    /* --- Gradient Vector Computation : Kirsh4 Algorithm --- */
    ret = GradientKirsh4(image, imnorm, imarg);
    if (ret)
    {
        fprintf(stderr, "Problem of Memory Allocation in Kirsh 4 Operator \n");
        Free_Image(image);
        Free_Image(imnorm);
        Free_Image(imarg);
        fclose(fichier);
        fclose(fichnorm);
        fclose(ficharg);
        exit(0);
    }

    /* --- Writing of the Images Result in File : Norm and Argument --- */
    fprintf(fichnorm, "P5\n#created by LibKirsh4\n%d %d\n255\n", (int)ncol, (int)nlig); // Header
    ret = Writing_ImageData(fichnorm, imnorm); // Image Pixel Data
    if (!ret)
    {
        fprintf(stderr, "Problem of Writing \n");
        Free_Image(image);
        Free_Image(imnorm);
        Free_Image(imarg);
        fclose(fichier);
        fclose(fichnorm);
        fclose(ficharg);
        exit(0);
    }

    fprintf(ficharg, "P5\n#created by LibKirsh4\n%d %d\n255\n", (int)ncol, (int)nlig); // Header
    ret = Writing_ImageData(ficharg, imarg); // Image Pixel Data
    if (!ret)
    {
        fprintf(stderr, "Problem of Writing \n");
        Free_Image(image);
        Free_Image(imnorm);
        Free_Image(imarg);
        fclose(fichier);
        fclose(fichnorm);
        fclose(ficharg);
        exit(0);
    }

    /* --- Free of Images --- */
    ret = Free_Image(image);
    if (ret == FALSE)
    {
        fprintf(stderr, "Problem of Free the Memory \n");
    }
    ret = Free_Image(imnorm);
    if (ret == FALSE)
    {
        fprintf(stderr, "Problem of Free the Memory \n");
    }
    ret = Free_Image(imarg);
    if (ret == FALSE)
    {
        fprintf(stderr, "Problem of Free the Memory \n");
    }

    fclose(fichier);
    fclose(fichnorm);
    fclose(ficharg);

    fprintf(stderr, "End of LibKirsh4 Operator\n");
    return (EXIT_SUCCESS);
}