#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
#include <opencv2/imgproc.hpp>

using namespace cv;

int main(int argc, char** argv)
{

    if(argc<2){
        std::cout << "Uncorrect number of parameters. Please specify the name of the image.\n";
        return 0;
    }
    
    cv::Mat img = cv::imread(argv[1]);

    if(img.rows == 0 && img.cols == 0){
        std::cout << "Impossible to open the image. Check the name of the file.\n";
        return 0;
    }


    Mat Garden_grayscale(img.rows,img.cols, CV_8U);
 
    cvtColor(img,Garden_grayscale, COLOR_BGR2GRAY);

    cv::namedWindow("Garden_grayscale");
    cv::imshow("Garden_grayscale", Garden_grayscale);
    cv::waitKey(0);

    return 0;

}