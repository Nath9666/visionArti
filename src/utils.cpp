#include "utils.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

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
    // Obtenir la résolution de l'écran
    int screenWidth = 1920/2; // Largeur de l'écran
    int screenHeight = 1080/2; // Hauteur de l'écran

    // Calculer la position et la taille de la fenêtre pour qu'elle ne dépasse pas l'écran
    int windowWidth = std::min(image.cols, screenWidth);
    int windowHeight = std::min(image.rows, screenHeight);
    int windowX = (screenWidth - windowWidth) / 2 + 100;
    int windowY = (screenHeight - windowHeight) / 2 + 100;

    // Afficher l'image dans une fenêtre redimensionnée
    cv::namedWindow(windowName, cv::WINDOW_NORMAL);
    cv::imshow(windowName, image);
    cv::moveWindow(windowName, windowX, windowY);
    cv::resizeWindow(windowName, windowWidth, windowHeight);
    cv::waitKey(0); // Attendre une touche pour fermer la fenêtre
}

// Fonction pour sauvegarder une image dans un fichier
void saveImage(const std::string& filePath, const cv::Mat& image) {
    if (!cv::imwrite(filePath, image)) {
        std::cerr << "Erreur : Impossible de sauvegarder l'image à " << filePath << std::endl;
    }
}