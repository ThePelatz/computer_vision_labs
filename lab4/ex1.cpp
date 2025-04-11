#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace cv;
using std::cout;
const int alpha_slider_max = 100;
int thresholdMin = 0;
int thresholdMax = 0;
cv::Mat img;

static void on_trackbar( int, void* )
{
    std::cout << "ThresholdMin: " << thresholdMin << std::endl;
    std::cout << "ThresholdMin: " << thresholdMax << std::endl;

    cv::Mat edges;
    cv::Canny(img, edges, thresholdMin, thresholdMax + 200);

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


   namedWindow("Canny image", WINDOW_AUTOSIZE); // Create Window
   char TrackbarName1[50];
   snprintf( TrackbarName1, sizeof(TrackbarName1), "Min threshold%d", alpha_slider_max );
   char TrackbarName2[50];
   snprintf( TrackbarName2, sizeof(TrackbarName2), "Max threshold%d", alpha_slider_max );
   createTrackbar( TrackbarName1, "Canny image", &thresholdMin, alpha_slider_max, on_trackbar );
   createTrackbar( TrackbarName2, "Canny image", &thresholdMax, 100, on_trackbar );
   on_trackbar( thresholdMin, 0 );
   on_trackbar( thresholdMax, 0 );
   waitKey(0);
   return 0;
}