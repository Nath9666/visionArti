#include <stdio.h>
#include <stdlib.h>
#include "EdStructures.h"
#include "EdUtilities.h"
#include "EdLibGradientKirsh4SepMasks.h"
#include "EdLibThreshold.h"
#include "EdLibThinning.h"
#include "EdLibEdgeUtilities.h"
//#include "LibSeuillage.h"
//#include "LibAffinage.h"

int main(int argc, char **argv)
{
    EdIMAGE *image = NULL, *imnorm = NULL, *imarg = NULL, *impts = NULL;
    int nlig = 0, ncol = 0;
    unsigned char prof = 0;
    FILE *fichier = NULL, *fichnorm = NULL, *ficharg = NULL;
    int ret;
    int iTh;
    unsigned char Th;

    /* --- USAGE --- */
    if (argc != 5)
    {
        fprintf(stderr, "USAGE : DetectionContours image imnorm impts Th\n");
        fprintf(stderr, "image : name of the image to filter \n");
        fprintf(stderr, "imnorm : name of the image of the norm of the gradient \n");
        fprintf(stderr, "impts : name of the image of edge points \n");
        fprintf(stderr, "Compute the gradient vector : norm and argument on B&W image according to Kirsh's algorithm \n");
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

    iTh = atoi(argv[4]);
    Th = (unsigned char)iTh;

    /* --- Reading of Image Header --- */
    if ((ret = Reading_ImageHeader(fichier, &ncol, &nlig, &prof)))
    {
        fprintf(stderr, "Problem of Reading Image Header \n");
        fclose(fichier);
        fclose(fichnorm);
        fclose(ficharg);
        exit(0);
    }
    fprintf(stderr, "Size of the Image : %d lines x %d colums : Type : %d\n", nlig, ncol, (int)prof);
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

    if (crea_IMAGE(impts) == NULL)
    {
        fprintf(stderr, "Error of Memory Allocation \n");
        Free_Image(image);
        Free_Image(imnorm);
        Free_Image(imarg);
        fclose(fichier);
        fclose(fichnorm);
        fclose(ficharg);
        exit(0);
    }
    ret = Creation_Image(impts, nlig, ncol, prof);
    if (!ret)
    {
        fprintf(stderr, "Error of Memory Allocation of Pixels \n");
        Free_Image(image);
        Free_Image(imnorm);
        Free_Image(imarg);
        Free_Image(impts);
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
        Free_Image(impts);
        fclose(fichier);
        fclose(fichnorm);
        fclose(ficharg);
        exit(0);
    }

    /* --- Gradient Vector Computation : Kirsh4 Algorithm --- */
    ret = GradientKirsh4SepMask(image, imnorm, imarg);
    if (ret)
    {
        fprintf(stderr, "Problem of Memory Allocation in Kirsh 4 Operator \n");
        Free_Image(image);
        Free_Image(imnorm);
        Free_Image(imarg);
        Free_Image(impts);
        fclose(fichier);
        fclose(fichnorm);
        fclose(ficharg);
        exit(0);
    }

    /* --- Threshold --- */
    ret = ClassicThreshold(imnorm, impts, Th);
    if (ret)
    {
        fprintf(stderr, "Problem of Memory Allocation in Kirsh 4 Operator \n");
        Free_Image(image);
        Free_Image(imnorm);
        Free_Image(imarg);
        Free_Image(impts);
        fclose(fichier);
        fclose(fichnorm);
        fclose(ficharg);
        exit(0);
    }

    /* --- Thinning --- */
    ret = ThinningEdges(imnorm, imarg, impts);
    if (ret)
    {
        fprintf(stderr, "Problem of Memory Allocation in Kirsh 4 Operator \n");
        Free_Image(image);
        Free_Image(imnorm);
        Free_Image(imarg);
        Free_Image(impts);
        fclose(fichier);
        fclose(fichnorm);
        fclose(ficharg);
        exit(0);
    }

    /* --- Writing of the Images Result in File : Norm and Argument --- */
    fprintf(fichnorm, "P5\n#created by DetectionContours\n%d %d\n255\n", (int)ncol, (int)nlig); // Header
    ret = Writing_ImageData(fichnorm, imnorm); // Image Pixel Data
    if (!ret)
    {
        fprintf(stderr, "Problem of Writing \n");
        Free_Image(image);
        Free_Image(imnorm);
        Free_Image(imarg);
        Free_Image(impts);
        fclose(fichier);
        fclose(fichnorm);
        fclose(ficharg);
        exit(0);
    }

    fprintf(ficharg, "P5\n#created by DetectionContours\n%d %d\n255\n", (int)ncol, (int)nlig); // Header
    ret = Writing_ImageData(ficharg, impts); // Image Pixel Data
    if (!ret)
    {
        fprintf(stderr, "Problem of Writing \n");
        Free_Image(image);
        Free_Image(imnorm);
        Free_Image(imarg);
        Free_Image(impts);
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
    ret = Free_Image(impts);
    if (ret == FALSE)
    {
        fprintf(stderr, "Problem of Free the Memory \n");
    }

    fclose(fichier);
    fclose(fichnorm);
    fclose(ficharg);

    fprintf(stderr, "End of DetectionContours Operator\n");
    return (EXIT_SUCCESS);
}