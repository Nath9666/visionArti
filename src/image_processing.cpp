#include "image_processing.hpp"
#include <opencv2/opencv.hpp>

using namespace cv;

// Fonction pour convertir une image en niveaux de gris
Mat convertToGray(const Mat& inputImage) {
    Mat grayImage;
    cvtColor(inputImage, grayImage, COLOR_BGR2GRAY);
    return grayImage;
}

// Fonction pour appliquer un filtre gaussien
Mat applyGaussianBlur(const Mat& inputImage, int kernelSize) {
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
    if (inputImage.channels() == 1) {
        // Si l'image est en niveaux de gris, la convertir en BGR
        Mat bgrImage;
        cvtColor(inputImage, bgrImage, COLOR_GRAY2BGR);
        fastNlMeansDenoisingColored(bgrImage, denoisedImage, 10, 10, 7, 21);
    } else {
        fastNlMeansDenoisingColored(inputImage, denoisedImage, 10, 10, 7, 21);
    }
    return denoisedImage;
}

// Fonction principale de traitement d'image
Mat processImage(const Mat& inputImage) {
    Mat grayImage = convertToGray(inputImage);
    cv::imshow("grayImage", grayImage);
    cv::waitKey(0);
    Mat blurredImage = applyGaussianBlur(grayImage, 2);
    cv::imshow("blurredImage", blurredImage);
    cv::waitKey(0);
    Mat binaryImage = binarizeImage(blurredImage);
    cv::imshow("binaryImage", binaryImage);
    cv::waitKey(0);
    //Mat denoisedImage = reduceNoise(binaryImage);
    return binaryImage;
}