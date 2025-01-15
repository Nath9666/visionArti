#include <iostream>
#include <filesystem>
#include "image_processing.hpp"
#include "lego_detection.hpp"
#include "utils.hpp"

namespace fs = std::filesystem;

int main(int argc, char** argv) {
    if (argc < 5) {
        std::cerr << "Usage: " << argv[0] << " <seuil> <debugMode> <NumImg> <blur>" << std::endl;
        return -1;
    }

    int seuil = std::stoi(argv[1]);
    int ImageDisplay = std::stoi(argv[2]);
    int NumImg = std::stoi(argv[3]);
    int blur = std::stoi(argv[4]);
    if (seuil <= 0) {
        std::cerr << "Erreur : Les valeurs de seuil et de thresh doivent être positives." << std::endl;
        return -1;
    }

    if (blur <= 0) {
        std::cerr << "Erreur : La valeur de blur doit être positive." << std::endl;
        return -1;
    }

    std::string imagePath = "./data/images/" + std::to_string(NumImg) + ".png";
    if (!fs::exists(imagePath)) {
        std::cerr << "Erreur : L'image " << imagePath << " n'existe pas." << std::endl;
        return -1;
    }

    cv::Mat image = loadImage(imagePath);

    // Détecter les Legos
    std::vector<cv::Rect> detectedLegos;
    int thresh = 100;
    int legoCount = detectLegos(image, detectedLegos, seuil, thresh, ImageDisplay, blur);

    // Afficher les résultats de la détection
    displayDetectionResults(image, detectedLegos);

    // Comparer les résultats avec les données JSON
    std::string jsonPath = "./data/results/" + std::to_string(NumImg) + ".json";
    float similarity = compareImageToJson(detectedLegos, jsonPath);
    if (similarity >= 0.0) {
        std::cout << "Similarite : " << similarity << std::endl;
    }

    // Afficher le nombre de Legos détectés
    std::cout << "Nombre de Legos : " << legoCount << std::endl;

    // Attendre une touche pour quitter
    cv::waitKey(0);

    return EXIT_SUCCESS;
}