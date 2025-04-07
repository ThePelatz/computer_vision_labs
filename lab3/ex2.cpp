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

    float avg[3] = {0.0,0.0,0.0}; 
    for(int i = x-4; i < x+4; i++){
        for(int j = y-4; j < y+4; j++){
            if(i >= 0 & j>=0 && i<img->rows && j<img->cols){
                avg[0] +=  (int) img->at<Vec3b>(j, i) [0];
                avg[1] +=  (int) img->at<Vec3b>(j, i) [1];
                avg[2] +=  (int) img->at<Vec3b>(j, i) [2];
            }
        }
    }

    std::cout << "Avg Blue: " << avg [0] / (9^2) << std::endl;
    std::cout << "Avg Green: " << avg [1] / (9^2) << std::endl;
    std::cout << "Avg Red: " << avg [2] / (9^2) << std::endl;

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