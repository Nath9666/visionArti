#include "utils.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>

// Fonction pour charger une image depuis un fichier
cv::Mat loadImage(const std::string& filePath) {
    cv::Mat image = cv::imread(filePath);
    if (image.empty()) {
        std::cerr << "Erreur : Impossible de charger l'image à partir de " << filePath << std::endl;
    }
    return image;
}

// Fonction pour afficher une image dans une fenêtre
void displayImage(const std::string& windowName, const cv::Mat& image) {
    // Obtenir la résolution de l'écran
    int screenWidth = 1920 / 2; // Largeur de l'écran
    int screenHeight = 1080 / 2; // Hauteur de l'écran

    // Calculer la position et la taille de la fenêtre pour qu'elle ne dépasse pas l'écran
    int windowWidth = std::min(image.cols, screenWidth);
    int windowHeight = std::min(image.rows, screenHeight);
    int windowX = (screenWidth - windowWidth) / 2 + 100;
    int windowY = (screenHeight - windowHeight) / 2 + 100;

    // Afficher l'image dans une fenêtre redimensionnée
    cv::namedWindow(windowName, cv::WINDOW_NORMAL);
    cv::imshow(windowName, image);
    cv::moveWindow(windowName, windowX, windowY);
    cv::resizeWindow(windowName, windowWidth, windowHeight);
    cv::waitKey(0); // Attendre une touche pour fermer la fenêtre
}

// Fonction pour sauvegarder une image dans un fichier
void saveImage(const std::string& filePath, const cv::Mat& image) {
    if (!cv::imwrite(filePath, image)) {
        std::cerr << "Erreur : Impossible de sauvegarder l'image à " << filePath << std::endl;
    }
}

// Fonction pour comparer les Legos détectés avec les données JSON
float compareImageToJson(const std::vector<cv::Rect>& detectedLegos, const std::string& jsonPath) {
    // Charger le fichier JSON
    FILE* fp = fopen(jsonPath.c_str(), "rb");
    if (!fp) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier JSON à " << jsonPath << std::endl;
        return -1.0;
    }

    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    rapidjson::Document jsonData;
    jsonData.ParseStream(is);
    fclose(fp);

    // Vérifier que le nombre de Legos détectés correspond au nombre de Legos dans le JSON
    if (!jsonData.IsArray() || detectedLegos.size() != jsonData.Size()) {
        std::cerr << "Erreur : Le nombre de Legos détectés ne correspond pas aux données JSON" << std::endl;
        return -1.0;
    }

    // Comparer les coordonnées des Legos détectés avec celles du JSON
    for (rapidjson::SizeType i = 0; i < jsonData.Size(); i++) {
        const cv::Rect& detectedLego = detectedLegos[i];
        const rapidjson::Value& legoData = jsonData[i];

        if (!legoData.HasMember("x") || !legoData.HasMember("y") || !legoData.HasMember("width") || !legoData.HasMember("height")) {
            std::cerr << "Erreur : Les clés 'x', 'y', 'width', ou 'height' sont manquantes dans le JSON" << std::endl;
            return -1.0;
        }

        int x = legoData["x"].GetInt();
        int y = legoData["y"].GetInt();
        int width = legoData["width"].GetInt();
        int height = legoData["height"].GetInt();

        if (detectedLego.x != x || detectedLego.y != y || detectedLego.width != width || detectedLego.height != height) {
            std::cerr << "Erreur : Les coordonnées du Lego détecté ne correspondent pas aux données JSON" << std::endl;
            return -1.0;
        }
    }

    return 0.0;
}