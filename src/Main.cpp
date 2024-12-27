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

    //Afficher l'image
    displayImage("Image d'origine", image);

    // Créer les trackbars
    createTrackbars();

    bool showTrackbars = true;

    while (showTrackbars) {
        // Détecter les Legos
        std::vector<cv::Rect> detectedLegos;
        int legoCount = detectLegos(image, detectedLegos);

        // Afficher les résultats de la détection
        displayDetectionResults(image, detectedLegos);

        // Afficher le nombre de Legos détectés
        std::cout << "Nombre de Legos : " << legoCount << std::endl;

        // Attendre 30 ms pour permettre la mise à jour des trackbars
        if (cv::waitKey(2) >= 0) break;

        // toucher 'q' pour quitter
        if (cv::waitKey(2) == 'q') {
            showTrackbars = false;
        }
    }

    return EXIT_SUCCESS;
}