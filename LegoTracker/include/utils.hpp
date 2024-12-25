#ifndef UTILS_HPP
#define UTILS_HPP

#include <opencv2/opencv.hpp>
#include <string>

// Fonction pour charger une image à partir d'un fichier
cv::Mat loadImage(const std::string& filePath);

// Fonction pour afficher une image dans une fenêtre
void displayImage(const std::string& windowName, const cv::Mat& image);

// Fonction pour sauvegarder une image dans un fichier
void saveImage(const std::string& filePath, const cv::Mat& image);

// Fonction pour afficher les résultats de détection
void displayResults(const cv::Mat& image, const std::vector<cv::Rect>& detectedLegos);

#endif // UTILS_HPP