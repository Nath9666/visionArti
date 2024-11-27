#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "EdStructures.h"


void EdImagefromMat (EdIMAGE *EdImage, cv::Mat &MatImage)
{
    NLIG(EdImage) = MatImage.rows;
    NCOL(EdImage) = MatImage.cols;
    PROF(EdImage) = MatImage.channels();
    PIOCTET(EdImage) = MatImage.ptr<uchar>(0);
}
