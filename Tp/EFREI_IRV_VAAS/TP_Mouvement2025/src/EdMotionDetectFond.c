// ------------------------------------------------------------------
/**
 * @file EdMotionDetect.c
 *
 * @brief Motion Detection using Background Subtraction Method
 * This file contains the main function for processing a video sequence
 * to detect motion using the background subtraction method.
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
#include <string.h>
#include "EdStructures.h"
#include "EdUtilities.h"
#include "EdLibMotionDetectFond.h"

int main(int argc, char **argv) {
    EdIMAGE *imCur = NULL, *imBg = NULL, *imRes = NULL;
    int nlig = 0, ncol = 0, iTh;
    float alpha;
    int NumRef, Num;
    unsigned char prof = 0;
    FILE *fichier = NULL, *fichres = NULL;
    int ret;
    char nomGen[255], nomNum[100], nomExt[100];
    char nomImCur[255], nomImRes[255];

    // USAGE
    if (argc != 4) {
        fprintf(stderr, "USAGE :  MotionDetect image iTh alpha\n");
        fprintf(stderr, "image : name of the image to filter\n");
        fprintf(stderr, "iTh : Threshold value\n");
        fprintf(stderr, "alpha : Coefficient for updating the background image\n");
        fprintf(stderr, "Motion detection \n");
        exit(0);
    }
    sscanf(argv[1], "%[^0-9]%[0-9]%*[.]%[pm]", nomGen, nomNum, nomExt);
    NumRef = atoi(nomNum);
    iTh = atoi(argv[2]);
    alpha = atof(argv[3]);
    printf("NomGen %s \n NumRef %d, nomExt %s iTh = %d alpha = %f\n",
           nomGen, NumRef, nomExt, iTh, alpha);
    Num = NumRef;

    // Ouverture Fichier Image de Reference
    sprintf(nomImCur, "../NSequenceCote/%s%04d.ppm", nomGen, Num);

    if (!(fichier = fopen(nomImCur, "rb"))) {
        fprintf(stderr, "Source Image %s Pb of Opening\n", nomImCur);
        exit(0);
    }

    // Reading of Image Header
    if ((ret = Reading_ImageHeader(fichier, &ncol, &nlig, &prof))) {
        fprintf(stderr, "Problem of Reading Image Header \n");
        exit(0);
    }
    fprintf(stderr, "Size of the Image : %d lines x %d columns : Type : %d\n", nlig, ncol, (int)prof);
    if (prof != 3) {
        fprintf(stderr, "The source image is not a RGB image \n");
        exit(0);
    }

    // Creation of Images Header and Data : imBg, imCur, imRes
    if (crea_IMAGE(imBg) == NULL) {
        fprintf(stderr, "Error of Memory Allocation \n");
        exit(0);
    }
    ret = Creation_Image(imBg, nlig, ncol, prof); // Image Data

    if (crea_IMAGE(imCur) == NULL) {
        fprintf(stderr, "Error of Memory Allocation \n");
        exit(0);
    }
    ret = Creation_Image(imCur, nlig, ncol, prof); // Image Data

    if (crea_IMAGE(imRes) == NULL) {
        fprintf(stderr, "Error of Memory Allocation \n");
        exit(0);
    }
    ret = Creation_Image(imRes, nlig, ncol, prof); // Image Data

    // Reading of Image imBg from file to Memory
    ret = Reading_ImageData(fichier, imBg); // Image Pixel Data
    if (!ret) {
        fprintf(stderr, "Problem of Reading \n");
        exit(0);
    }

    fclose(fichier);

    while (1) {
        Num++;
        // Ouverture des Images Cur et Res
        // Creation des Noms des Images
        sprintf(nomImCur, "../NSequenceCote/%s%04d.ppm", nomGen, Num);
        sprintf(nomImRes, "../ImRes/%sFondRes%04d.ppm", nomGen, Num);

        // Source Image
        if (!(fichier = fopen(nomImCur, "rb"))) {
            fprintf(stderr, "Image : %s Pb of Opening\n", nomImCur);
            break;
        }
        // Image
        if (!(fichres = fopen(nomImRes, "wb"))) {
            fprintf(stderr, "Result Image %s Pb of Opening\n", nomImRes);
            exit(0);
        }
        printf("Image Cur : %s, Res %s \n", nomImCur, nomImRes);

        // Lecture de l'image courante
        if ((ret = Reading_ImageHeader(fichier, &ncol, &nlig, &prof))) {
            fprintf(stderr, "Problem of Reading Image Header \n");
            exit(0);
        }
        ret = Reading_ImageData(fichier, imCur); // Image Pixel Data
        if (!ret) {
            fprintf(stderr, "Problem of Reading \n");
            exit(0);
        }

        // Detection du Mouvement
        ret = MotionDetectBg(imBg, imCur, imRes, iTh, alpha);

        // Writing of the Image Result in File
        fprintf(fichres, "P6\n#creating by EdEnviTI\n%d %d\n255\n", (int)ncol, (int)nlig); // Header
        ret = Writing_ImageData(fichres, imRes); // Image Pixel Data
        if (!ret) {
            fprintf(stderr, "Problem of Writing \n");
            exit(0);
        }
        fclose(fichier);
        fclose(fichres);
    } // fin boucle

    // Liberation de la Memoire
    ret = Free_Image(imBg);
    if (ret == FALSE) {
        fprintf(stderr, "Problem of Free the Memory \n");
    }
    ret = Free_Image(imCur);
    if (ret == FALSE) {
        fprintf(stderr, "Problem of Free the Memory \n");
    }
    ret = Free_Image(imRes);
    if (ret == FALSE) {
        fprintf(stderr, "Problem of Free the Memory \n");
    }

    fprintf(stderr, "End of Motion Operator\n");
    return 0;
}