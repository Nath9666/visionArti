#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Lire l'image
    cv::Mat image = cv::imread("path_to_your_image.jpg");

    // Vérifier si l'image est chargée correctement
    if(image.empty()) {
        std::cerr << "Erreur: Impossible de charger l'image!" << std::endl;
        return -1;
    }

    // Afficher l'image
    cv::imshow("Image", image);

    // Attendre une touche pour fermer la fenêtre
    cv::waitKey(0);

    return 0;
}