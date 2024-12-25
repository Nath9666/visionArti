#include <gtest/gtest.h>
#include "image_processing.hpp"
#include "utils.hpp"

// Tests pour les fonctions de traitement d'image

TEST(ImageProcessingTest, ConvertToGray) {
    cv::Mat colorImage = cv::imread("data/images/test_image.jpg");
    ASSERT_FALSE(colorImage.empty()) << "L'image n'a pas pu être chargée.";

    cv::Mat grayImage = convertToGray(colorImage);
    ASSERT_FALSE(grayImage.empty()) << "La conversion en niveaux de gris a échoué.";
    ASSERT_EQ(grayImage.channels(), 1) << "L'image convertie ne doit avoir qu'un seul canal.";
}

TEST(ImageProcessingTest, ApplyGaussianBlur) {
    cv::Mat image = cv::imread("data/images/test_image.jpg");
    ASSERT_FALSE(image.empty()) << "L'image n'a pas pu être chargée.";

    cv::Mat blurredImage = applyGaussianBlur(image, 5);
    ASSERT_FALSE(blurredImage.empty()) << "L'application du flou gaussien a échoué.";
}

TEST(ImageProcessingTest, BinarizeImage) {
    cv::Mat grayImage = cv::imread("data/images/test_image_gray.jpg", cv::IMREAD_GRAYSCALE);
    ASSERT_FALSE(grayImage.empty()) << "L'image en niveaux de gris n'a pas pu être chargée.";

    cv::Mat binaryImage = binarizeImage(grayImage);
    ASSERT_FALSE(binaryImage.empty()) << "La binarisation de l'image a échoué.";
}

TEST(ImageProcessingTest, LoadImage) {
    cv::Mat image = loadImage("data/images/test_image.jpg");
    ASSERT_FALSE(image.empty()) << "L'image n'a pas pu être chargée.";
}

TEST(ImageProcessingTest, SaveImage) {
    cv::Mat image = cv::imread("data/images/test_image.jpg");
    ASSERT_FALSE(image.empty()) << "L'image n'a pas pu être chargée.";

    bool success = saveImage("data/results/test_output.jpg", image);
    ASSERT_TRUE(success) << "L'image n'a pas pu être sauvegardée.";
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}