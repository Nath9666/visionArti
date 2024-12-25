#include <iostream>
#include "image_processing.hpp"
#include "lego_detection.hpp"
#include "utils.hpp"

int main(int argc, char** argv) {
    // Vérification des arguments
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <image_path>" << std::endl;
        return EXIT_FAILURE;
    }

    // Chargement de l'image
    std::string imagePath = argv[1];
    cv::Mat image = loadImage(imagePath);
    if (image.empty()) {
        std::cerr << "Erreur lors du chargement de l'image." << std::endl;
        return EXIT_FAILURE;
    }

    // Prétraitement de l'image
    cv::Mat processedImage = preprocessImage(image);

    // Détection des Legos
    std::vector<DetectedLego> legos = detectLegos(processedImage);

    // Affichage des résultats
    displayResults(image, legos);

    return EXIT_SUCCESS;
}