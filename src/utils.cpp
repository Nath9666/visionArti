#include "utils.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

// Fonction pour charger une image depuis un fichier
cv::Mat loadImage(const std::string& filePath) {
    cv::Mat image = cv::imread(filePath);
    if (image.empty()) {
        std::cerr << "Erreur : Impossible de charger l'image à partir de " << filePath << std::endl;
    }
    return image;
}

// Fonction pour afficher une image dans une fenêtre
void displayImage(const std::string& windowName, const cv::Mat& image) {
    cv::imshow(windowName, image);
    cv::waitKey(0); // Attendre une touche pour fermer la fenêtre
}

// Fonction pour sauvegarder une image dans un fichier
void saveImage(const std::string& filePath, const cv::Mat& image) {
    if (!cv::imwrite(filePath, image)) {
        std::cerr << "Erreur : Impossible de sauvegarder l'image à " << filePath << std::endl;
    }
}