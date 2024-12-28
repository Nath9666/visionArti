#include "lego_detection.hpp"
#include "image_processing.hpp"
#include "utils.hpp"
#include <opencv2/opencv.hpp>
#include <vector>

// Fonction pour détecter et compter les Legos dans une image
int detectLegos(const cv::Mat& inputImage, std::vector<cv::Rect>& detectedLegos, int seuil, int thresh, bool ImageDisplay) {
    // Convertir l'image en espace de couleur HSV
    cv::Mat hsvImage;
    cv::cvtColor(inputImage, hsvImage, cv::COLOR_BGR2HSV);

    // Segmenter les couleurs spécifiques aux Legos
    cv::Mat mask1, mask2, mask3, combinedMask;
    cv::inRange(hsvImage, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), mask1); // Rouge
    cv::inRange(hsvImage, cv::Scalar(40, 100, 100), cv::Scalar(50, 255, 255), mask2); // Vert
    cv::inRange(hsvImage, cv::Scalar(70, 100, 100), cv::Scalar(90, 255, 255), mask3); // Bleu
    
    // Combiner les masques
    cv::bitwise_or(mask1, mask2, combinedMask);
    cv::bitwise_or(combinedMask, mask3, combinedMask);
    
    // Appliquer le masque à l'image d'entrée
    cv::Mat maskedImage;
    cv::bitwise_and(inputImage, inputImage, maskedImage, combinedMask);

    // Convertir l'image masquée en niveaux de gris
    cv::Mat grayImage = convertToGray(inputImage);
    cv::Mat blurredImage = applyGaussianBlur(grayImage, 5);
    cv::Mat binaryImage = binarizeImage(blurredImage);

    if (ImageDisplay) {
        displayImage("Image originale", inputImage);
        displayImage("Image masquée", maskedImage);
        displayImage("Image en niveaux de gris", grayImage);
        displayImage("Image floutée", blurredImage);
        displayImage("Image binaire", binaryImage);
    }

    // Segmentation de région par croissance de région
    cv::Mat labels, stats, centroids;
    int numLabels = cv::connectedComponentsWithStats(binaryImage, labels, stats, centroids, 8, CV_32S);

    // Identification des Legos par leurs régions
    int legoCount = 0;
    for (int i = 1; i < numLabels; i++) { // Commencer à 1 pour ignorer le fond
        int area = stats.at<int>(i, cv::CC_STAT_AREA);
        if (area > seuil) { // Filtrer les petites régions
            legoCount++;
            int x = stats.at<int>(i, cv::CC_STAT_LEFT);
            int y = stats.at<int>(i, cv::CC_STAT_TOP);
            int width = stats.at<int>(i, cv::CC_STAT_WIDTH);
            int height = stats.at<int>(i, cv::CC_STAT_HEIGHT);
            detectedLegos.push_back(cv::Rect(x, y, width, height));
        }
    }

    // Détection des contours avec Canny
    cv::Mat cannyOutput;
    cv::Canny(binaryImage, cannyOutput, thresh, thresh * 2);

    // Détection des contours avec hiérarchie
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(cannyOutput, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // Approximation polygonale des contours
    std::vector<std::vector<cv::Point>> approxContours(contours.size());
    for (size_t i = 0; i < contours.size(); i++) {
        cv::approxPolyDP(contours[i], approxContours[i], 0.02 * cv::arcLength(contours[i], true), true);
    }

    // Identification des Legos par leurs contours
    for (size_t i = 0; i < approxContours.size(); i++) {
        double area = cv::contourArea(approxContours[i]);
        if (area > seuil) { // Filtrer les petits objets
            legoCount++;
            cv::Rect boundingBox = cv::boundingRect(approxContours[i]);
            detectedLegos.push_back(boundingBox);
        }
    }

    return legoCount; // Retourne le nombre de Legos détectés
}

// Fonction pour afficher les résultats de la détection
void displayDetectionResults(const cv::Mat& inputImage, const std::vector<cv::Rect>& detectedLegos) {
    cv::Mat outputImage = inputImage.clone();

    // Vérifier le nombre de canaux de l'image et convertir si nécessaire
    if (outputImage.channels() == 1) {
        cv::cvtColor(outputImage, outputImage, cv::COLOR_GRAY2BGR);
    }

    // Dessiner des rectangles autour des Legos détectés
    for (const auto& lego : detectedLegos) {
        cv::rectangle(outputImage, lego, cv::Scalar(0, 255, 0), 2);
    }

    // Afficher l'image avec les rectangles
    displayImage("Résultats de la détection", outputImage);
}