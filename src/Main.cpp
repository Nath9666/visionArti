#include <iostream>
#include "image_processing.hpp"
#include "lego_detection.hpp"
#include "utils.hpp"

int main(int argc, char** argv) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <seuil> <thresh>" << std::endl;
        return -1;
    }

    int seuil = std::stoi(argv[1]);
    int thresh = std::stoi(argv[2]);
    int ImageDisplay = std::stoi(argv[3]);
    if (seuil <= 0 || thresh <= 0) {
        std::cerr << "Erreur : Les valeurs de seuil et de thresh doivent être positives." << std::endl;
        return -1;
    }

    if (ImageDisplay != 0 && ImageDisplay != 1) {
        std::cerr << "Erreur : La valeur de ImageDisplay doit être 0 ou 1." << std::endl;
        return -1;
    }

    cv::Mat image = loadImage("./data/images/1001.png");

    // Détecter les Legos
    std::vector<cv::Rect> detectedLegos;
    int legoCount = detectLegos(image, detectedLegos, seuil, thresh, ImageDisplay);

    // Afficher les résultats de la détection
    displayDetectionResults(image, detectedLegos);

    // Comparer les résultats avec les données JSON
    float similarity = compareImageToJson(detectedLegos, "./data/results/1001.json");
    if (similarity >= 0.0) {
        std::cout << "Similarité : " << similarity << std::endl;
    }

    // Afficher le nombre de Legos détectés
    std::cout << "Nombre de Legos : " << legoCount << std::endl;

    // Attendre une touche pour quitter
    cv::waitKey(0);

    return EXIT_SUCCESS;
}