#ifndef GENERALIMAGETRANSFORMS_H
#define GENERALIMAGETRANSFORMS_H

#include <opencv2/opencv.hpp>

#include <QString>

using namespace cv;

/*
 void cv::resize(
        cv::InputArray src, // Input image
        cv::OutputArray dst, // Result image
        cv::Size dsize, // New size
        double fx = 0, // x-rescale
        double fy = 0, // y-rescale
        int interpolation = CV::INTER_LINEAR // interpolation method
);

cv::INTER_NEAREST Nearest neighbor
cv::INTER_LINEAR Bilinear
cv::INTER_AREA Pixel area resampling
cv::INTER_CUBIC Bicubic interpolation
cv::INTER_LANCZOS4 Lanczos interpolation over 8 ¡Á 8 neighborhood

*/

void Resize()
{
    Mat src = imread("f:/ecg.jpg"), dst;
    imshow("raw", src);

    resize(src, dst, cv::Size(200, 200), 0, 0, cv::INTER_NEAREST);
    imshow("INTER_NEAREST", dst);

    resize(src, dst, cv::Size(200, 200), 0, 0,  cv::INTER_LINEAR);
    imshow("INTER_LINEAR", dst);

    resize(src, dst, cv::Size(200, 200), 0, 0, cv::INTER_AREA);
    imshow("INTER_AREA", dst);

    resize(src, dst, cv::Size(200, 200), 0, 0, cv::INTER_CUBIC);
    imshow("INTER_CUBIC", dst);

    resize(src, dst, cv::Size(200, 200), 0, 0, cv::INTER_LANCZOS4);
    imshow("INTER_LANCZOS4", dst);

}


/*
 * void cv::pyrDown(
            cv::InputArray src, // Input image
            cv::OutputArray dst, // Result image
            const cv::Size& dstsize = cv::Size() // Output image size
        );
*/
void PyrDown()
{
    Mat src = imread("f:/ecg.jpg"), dst;
    imshow("raw", src);

    cv::pyrDown(src, dst);
    imshow("PyrDown", dst);

}

/*
void cv::buildPyramid(
    cv::InputArray src, // Input image
    cv::OutputArrayOfArrays dst, // Output images from pyramid
    int maxlevel // Number of pyramid levels
);

*/
void BuildPyramid()
{
    Mat src = imread("f:/ecg.jpg"), dst;
    imshow("raw", src);

    int nMax = 5;

    std::vector<Mat> vDst;
    cv::buildPyramid(src, vDst, nMax);

    for (int i = 0 ; i < vDst.size(); ++i)
    {
        Mat& dst = vDst[i];
        QString strTitle = QString("BuildPyramid - %1").arg(i);
        imshow(strTitle.toLocal8Bit().data(), dst);
    }
}


/*

*/
void PyrUp()
{
    Mat src = imread("f:/ecg.jpg"), dst;
    imshow("raw", src);

    cv::pyrUp(src, dst);
    imshow("PyrUp", dst);

}



#endif // GENERALIMAGETRANSFORMS_H
