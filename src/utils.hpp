#ifndef UTILS_HPP
#define UTILS_HPP

#include <opencv2/opencv.hpp>
#include <string>

// Fonction pour charger une image depuis un fichier
cv::Mat loadImage(const std::string& filePath);

// Fonction pour afficher une image dans une fenêtre
void displayImage(const std::string& windowName, const cv::Mat& image);

// Fonction pour sauvegarder une image dans un fichier
void saveImage(const std::string& filePath, const cv::Mat& image);

// Fonction pour comparer les régions détectées avec un fichier JSON
float compareImageToJson(const std::vector<cv::Rect>& detectedLegos, const std::string& jsonPath);

#endif // UTILS_HPP