#include <opencv2/opencv.hpp>

int main() {
    cv::Mat image = cv::imread("image.jpg");
    cv::imshow("Image", image);
    cv::waitKey(0);
    return 0;
}