#include <gtest/gtest.h>
#include "lego_detection.hpp"

// Test de la fonction de détection des Legos
TEST(LegoDetectionTest, CountLegos) {
    // Charger une image de test
    cv::Mat testImage = cv::imread("data/test_cases/test_image.jpg");
    ASSERT_FALSE(testImage.empty()) << "L'image de test n'a pas pu être chargée.";

    // Appeler la fonction de détection
    int legoCount = countLegos(testImage);

    // Vérifier le nombre de Legos détectés
    EXPECT_GT(legoCount, 0) << "Aucun Lego détecté dans l'image de test.";
}

// Test de la fonction d'identification des Legos
TEST(LegoDetectionTest, IdentifyLegos) {
    // Charger une image de test
    cv::Mat testImage = cv::imread("data/test_cases/test_image.jpg");
    ASSERT_FALSE(testImage.empty()) << "L'image de test n'a pas pu être chargée.";

    // Identifier les Legos dans l'image
    std::vector<Lego> legos = identifyLegos(testImage);

    // Vérifier que des Legos ont été identifiés
    EXPECT_FALSE(legos.empty()) << "Aucun Lego identifié dans l'image de test.";
}

// Point d'entrée pour exécuter les tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}