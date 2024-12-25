#ifndef IMAGE_PROCESSING_HPP
#define IMAGE_PROCESSING_HPP

#include <opencv2/opencv.hpp>
#include <vector>

// Fonction pour convertir une image en niveaux de gris
cv::Mat convertToGray(const cv::Mat& inputImage);

// Fonction pour appliquer un filtre gaussien à une image
cv::Mat applyGaussianBlur(const cv::Mat& inputImage, int kernelSize);

// Fonction pour effectuer la binarisation d'une image
cv::Mat binarizeImage(const cv::Mat& inputImage, double threshold = 128);

// Fonction pour réduire le bruit dans une image
cv::Mat reduceNoise(const cv::Mat& inputImage);

// Fonction pour effectuer la détection de contours
std::vector<std::vector<cv::Point>> detectContours(const cv::Mat& inputImage);

#endif // IMAGE_PROCESSING_HPP