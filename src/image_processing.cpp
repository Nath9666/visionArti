#include "image_processing.hpp"
#include <opencv2/opencv.hpp>
#include <thread> // Pour obtenir le nombre de cœurs du processeur

using namespace cv;

// Fonction pour convertir une image en niveaux de gris
Mat convertToGray(const Mat& inputImage) {
    Mat grayImage;
    cvtColor(inputImage, grayImage, COLOR_BGR2GRAY);
    return grayImage;
}

// Fonction pour appliquer un filtre gaussien
Mat applyGaussianBlur(const Mat& inputImage, int kernelSize) {
    // Vérifier que la taille du noyau est positive et impaire
    if (kernelSize <= 0) {
        kernelSize = 1; // Valeur par défaut
    }
    if (kernelSize % 2 == 0) {
        kernelSize += 1; // Rendre la taille impaire
    }

    Mat blurredImage;
    GaussianBlur(inputImage, blurredImage, Size(kernelSize, kernelSize), 0);
    return blurredImage;
}

// Fonction pour binariser une image
Mat binarizeImage(const Mat& grayImage) {
    Mat binaryImage;
    threshold(grayImage, binaryImage, 0, 255, THRESH_BINARY | THRESH_OTSU);
    return binaryImage;
}

// Fonction pour réduire le bruit dans une image
Mat reduceNoise(const Mat& inputImage) {
    Mat denoisedImage;

    // Obtenir le nombre de cœurs du processeur
    unsigned int numCores = std::thread::hardware_concurrency();

    // Ajuster les paramètres de réduction de bruit en fonction du nombre de cœurs
    int h = int(numCores/4); // Paramètre de filtre pour fastNlMeansDenoising
    int hForColorComponents = int(numCores/4); // Paramètre de filtre pour fastNlMeansDenoisingColored

    //Affiche le nombre de coeurs
    std::cout << "Nombre de coeurs : " << numCores << std::endl;

    if (inputImage.channels() == 1) {
        // Si l'image est en niveaux de gris, utiliser fastNlMeansDenoising
        fastNlMeansDenoising(inputImage, denoisedImage, h, 7, 21);
    } else {
        // Si l'image est en couleur, utiliser fastNlMeansDenoisingColored avec des paramètres ajustés
        fastNlMeansDenoisingColored(inputImage, denoisedImage, h, hForColorComponents, 7, 21);
    }
    return denoisedImage;
}

// Fonction principale de traitement d'image
Mat processImage(const Mat& inputImage) {
    Mat grayImage = convertToGray(inputImage);
    Mat blurredImage = applyGaussianBlur(grayImage, 5);
    Mat binaryImage = binarizeImage(blurredImage);
    //Mat denoisedImage = reduceNoise(binaryImage);
    return binaryImage;
}