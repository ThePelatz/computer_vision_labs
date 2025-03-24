#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void showHistogram(const cv::Mat& src)
{
    if (src.channels() != 1) {
        std::cout << "The image should have only one channel.\n";
        return;
    }

    int histSize = 256;
    float range[] = { 0, 256 };
    const float* histRange[] = { range };

    bool uniform = true, accumulate = false;

    Mat hist;
    calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, histRange, uniform, accumulate);

    normalize(hist, hist, 0, 400, NORM_MINMAX);

    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double) hist_w / histSize);

    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

    for (int i = 1; i < histSize; i++)
    {
        line(histImage, 
             Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
             Point(bin_w * i, hist_h - cvRound(hist.at<float>(i))),
             Scalar(255, 255, 255), 2, 8, 0);
    }

    imshow("Histogram", histImage);
}

int main(int argc, char** argv)
{
    if(argc < 2){
        std::cout << "Uncorrect number of parameters. Please specify the name of the image.\n";
        return 0;
    }
        
    cv::Mat img = cv::imread(argv[1]);

    if(img.rows == 0 && img.cols == 0){
        std::cout << "Impossible to open the image. Check the name of the file.\n";
        return 0;
    }

    Mat src;
    cvtColor(img, src, COLOR_BGR2GRAY); 

    showHistogram(src);

    imshow("Source image", src);

    cv::waitKey(0);

    return 0;
}
