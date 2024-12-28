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

    // Vérifier que le format JSON est valide
    if (!jsonData.HasMember("annotations") || !jsonData["annotations"].HasMember("object") || !jsonData["annotations"]["object"].IsArray()) {
        std::cerr << "Erreur : Format JSON invalide" << std::endl;
        return -1.0;
    }

    const rapidjson::Value& objects = jsonData["annotations"]["object"];
    int totalLegos = objects.Size();
    int matchedLegos = 0;

    // Comparer les coordonnées des Legos détectés avec celles du JSON
    for (rapidjson::SizeType i = 0; i < objects.Size(); i++) {
        const rapidjson::Value& legoData = objects[i]["bndbox"];

        if (!legoData.HasMember("xmin") || !legoData.HasMember("ymin") || !legoData.HasMember("xmax") || !legoData.HasMember("ymax")) {
            std::cerr << "Erreur : Les clés 'xmin', 'ymin', 'xmax', ou 'ymax' sont manquantes dans le JSON" << std::endl;
            continue;
        }

        int xmin = std::stoi(legoData["xmin"].GetString());
        int ymin = std::stoi(legoData["ymin"].GetString());
        int xmax = std::stoi(legoData["xmax"].GetString());
        int ymax = std::stoi(legoData["ymax"].GetString());

        for (const auto& detectedLego : detectedLegos) {
            int detectedXmin = detectedLego.x;
            int detectedYmin = detectedLego.y;
            int detectedXmax = detectedLego.x + detectedLego.width;
            int detectedYmax = detectedLego.y + detectedLego.height;

            // Calculer les marges d'erreur
            int errorMarginX = static_cast<int>(0.1 * (xmax - xmin));
            int errorMarginY = static_cast<int>(0.1 * (ymax - ymin));

            // Vérifier si les coordonnées sont dans la marge d'erreur
            if (abs(detectedXmin - xmin) <= errorMarginX &&
                abs(detectedYmin - ymin) <= errorMarginY &&
                abs(detectedXmax - xmax) <= errorMarginX &&
                abs(detectedYmax - ymax) <= errorMarginY) {
                matchedLegos++;
                break;
            }
        }
    }

    // Calculer le pourcentage de correspondance
    float matchPercentage = static_cast<float>(matchedLegos) / totalLegos * 100.0f;
    return matchPercentage;
}