#include "lego_detection.hpp"
#include "image_processing.hpp"
#include "utils.hpp"
#include <opencv2/opencv.hpp>
#include <vector>

// Fonction pour détecter et compter les Legos dans une image
int detectLegos(const cv::Mat& inputImage, std::vector<cv::Rect>& detectedLegos) {
    cv::Mat grayImage, binaryImage;
    
    // Conversion de l'image en niveaux de gris
    cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);
    
    // Application d'un filtre pour réduire le bruit
    cv::GaussianBlur(grayImage, grayImage, cv::Size(5, 5), 0);
    
    // Binarisation de l'image
    cv::threshold(grayImage, binaryImage, 0, 255, cv::THRESH_BINARY + cv::THRESH_OTSU);
    
    // Détection des contours
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(binaryImage, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    
    // Identification des Legos par leurs contours
    for (const auto& contour : contours) {
        double area = cv::contourArea(contour);
        if (area > 100) { // Filtrer les petits objets
            cv::Rect boundingBox = cv::boundingRect(contour);
            detectedLegos.push_back(boundingBox);
        }
    }
    
    return detectedLegos.size(); // Retourne le nombre de Legos détectés
}

// Fonction pour afficher les résultats de la détection
void displayDetectionResults(const cv::Mat& inputImage, const std::vector<cv::Rect>& detectedLegos) {
    cv::Mat outputImage = inputImage.clone();
    
    // Dessiner des rectangles autour des Legos détectés
    for (const auto& lego : detectedLegos) {
        cv::rectangle(outputImage, lego, cv::Scalar(0, 255, 0), 2);
    }
    
    // Afficher l'image avec les résultats
    cv::imshow("Detected Legos", outputImage);
    cv::waitKey(0);
}