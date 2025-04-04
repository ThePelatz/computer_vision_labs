#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
#include <opencv2/imgproc.hpp>

using namespace cv;

static void onMouse( int event, int x, int y, int, void* param)
{
    
    cv::Mat* img = (cv::Mat*) param; 
    
    if( event != EVENT_LBUTTONDOWN )
        return;


    std::cout << "Blue: " << (int) img->at<Vec3b>(y, x) [0] << std::endl;
    std::cout << "Green: " << (int) img->at<Vec3b>(y, x) [1] << std::endl;
    std::cout << "Red: " << (int) img->at<Vec3b>(y, x) [2] << std::endl;

    return; 

}

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

    cv::namedWindow("robocop");
    cv::imshow("robocop", img);
    setMouseCallback( "robocop", onMouse, &img);
    
    waitKey(0);


    return 0;

}