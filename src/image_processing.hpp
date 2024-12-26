#ifndef IMAGE_PROCESSING_HPP
#define IMAGE_PROCESSING_HPP

#include <opencv2/opencv.hpp>

cv::Mat convertToGray(const cv::Mat& inputImage);
cv::Mat applyGaussianBlur(const cv::Mat& inputImage, int kernelSize);
cv::Mat binarizeImage(const cv::Mat& grayImage);
cv::Mat reduceNoise(const cv::Mat& inputImage);
cv::Mat processImage(const cv::Mat& inputImage);

#endif // IMAGE_PROCESSING_HPP