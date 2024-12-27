#include <iostream>
#include "image_processing.hpp"
#include "lego_detection.hpp"
#include "utils.hpp"

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <seuil> <thresh>" << std::endl;
        return -1;
    }

    int seuil = std::stoi(argv[1]);
    int thresh = std::stoi(argv[2]);

    // Lire l'image
    cv::Mat image = cv::imread("./data/images/1001.png");

    // Vérifier si l'image est chargée correctement
    if(image.empty()) {
        std::cerr << "Erreur: Impossible de charger l'image!" << std::endl;
        return -1;
    }

    // Détecter les Legos
    std::vector<cv::Rect> detectedLegos;
    int legoCount = detectLegos(image, detectedLegos, seuil, thresh);

    // Afficher les résultats de la détection
    //?displayDetectionResults(image, detectedLegos);

    // Afficher le nombre de Legos détectés
    std::cout << "Nombre de Legos : " << legoCount << std::endl;

    // Attendre une touche pour quitter
    cv::waitKey(0);

    return EXIT_SUCCESS;
}