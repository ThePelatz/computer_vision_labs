#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace cv;
using std::cout;
const int alpha_slider_max = 100;
int alpha_slider;
int thresholdMin;
cv::Mat img;

static void on_trackbar( int, void* )
{
    thresholdMin = (int) alpha_slider ;
    std::cout << "ThresholdMin: " << thresholdMin << std::endl;

    cv::Mat edges;
    double thresholdMax = 150;
    cv::Canny(img, edges, thresholdMin, thresholdMax);

    cv::imshow("Canny image", edges);

    waitKey(0);
}


int main(int argc, char** argv)
{
   
    if(argc<2){
        std::cout << "Uncorrect number of parameters. Please specify the name of the image.\n";
        return 0;
    }
    
    img = cv::imread(argv[1]);

    if(img.rows == 0 && img.cols == 0){
        std::cout << "Impossible to open the image. Check the name of the file.\n";
        return 0;
    }


   alpha_slider = 0;
   namedWindow("Canny image", WINDOW_AUTOSIZE); // Create Window
   char TrackbarName[50];
   snprintf( TrackbarName, sizeof(TrackbarName), "Alpha x %d", alpha_slider_max );
   createTrackbar( TrackbarName, "Canny image", &alpha_slider, alpha_slider_max, on_trackbar );
   on_trackbar( alpha_slider, 0 );
   waitKey(0);
   return 0;
}