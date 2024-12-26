#include <iostream>
#include "image_processing.hpp"
#include "lego_detection.hpp"
#include "utils.hpp"

int main() {
    // Lire l'image
    cv::Mat image = cv::imread("./data/images/1001.png");

    // Vérifier si l'image est chargée correctement
    if(image.empty()) {
        std::cerr << "Erreur: Impossible de charger l'image!" << std::endl;
        return -1;
    }

    // Afficher l'image
    cv::imshow("Image", image);

    // Attendre une touche pour fermer la fenêtre
    cv::waitKey(0);

    // Prétraitement de l'image
    //cv::Mat processedImage = processImage(image);

    // Détection des Legos
    std::vector<cv::Rect> legos;
    int legoCount = detectLegos(image, legos);

    // Affichage des résultats
    displayDetectionResults(image, legos);

    std::cout << "Nombre de Legos : " << legoCount << std::endl;

    return EXIT_SUCCESS;
}