#ifndef LEGO_DETECTION_HPP
#define LEGO_DETECTION_HPP

#include <opencv2/opencv.hpp>
#include <vector>

// Fonction pour détecter et compter les Legos dans une image
int detectLegos(const cv::Mat& inputImage, std::vector<cv::Rect>& detectedLegos, int seuil, int thresh, bool ImageDisplay, int blur);

// Fonction pour afficher les résultats de la détection
void displayDetectionResults(const cv::Mat& inputImage, const std::vector<cv::Rect>& detectedLegos);

void createTrackbars();

#endif // LEGO_DETECTION_HPP