#ifndef LEGO_DETECTION_HPP
#define LEGO_DETECTION_HPP

#include <opencv2/opencv.hpp>
#include <vector>

// Structure pour stocker les informations sur les pièces de Lego détectées
struct LegoPiece {
    cv::Rect boundingBox; // Boîte englobante de la pièce
    int id;               // Identifiant unique de la pièce
};

// Fonction pour détecter les Legos dans une image
std::vector<LegoPiece> detectLegos(const cv::Mat& image);

// Fonction pour compter le nombre de Legos détectés
int countLegos(const std::vector<LegoPiece>& legos);

// Fonction pour appliquer un modèle d'apprentissage automatique pour la détection
std::vector<LegoPiece> detectLegosWithModel(const cv::Mat& image, const std::string& modelPath);

#endif // LEGO_DETECTION_HPP