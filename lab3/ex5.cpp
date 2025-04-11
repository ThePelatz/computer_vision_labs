#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
#include <opencv2/imgproc.hpp>

using namespace cv;

void searchTshirt(cv::Mat* img);
void colorTShirt(cv::Mat* img,Mat mask);
std::vector<float> getAvgColor(int x,int y, cv::Mat* img); 

static void onMouse( int event, int x, int y, int, void* param)
{
    
    cv::Mat* img = (cv::Mat*) param; 
    
    if( event != EVENT_LBUTTONDOWN )
        return;

    float avg[3] = {0.0,0.0,0.0}; 
    for(int i = x-4; i < x+4; i++){
        for(int j = y-4; j < y+4; j++){
            if(i >= 0 & j>=0 && i<img->cols && j<img->rows){
                avg[0] +=  (int) img->at<Vec3b>(j, i) [0];
                avg[1] +=  (int) img->at<Vec3b>(j, i) [1];
                avg[2] +=  (int) img->at<Vec3b>(j, i) [2];
            }
        }
    }

    std::cout << "Avg Blue: " << avg [0] / (9*9) << std::endl;
    std::cout << "Avg Green: " << avg [1] / (9*9) << std::endl;
    std::cout << "Avg Red: " << avg [2] / (9*9) << std::endl;


    searchTshirt(img);

    return; 

}

void searchTshirt(cv::Mat* img){

    Mat mask;
    int rows = img->rows;
    int cols = img->cols;
    mask = cv::Mat::zeros(rows,cols, CV_8U);
    
    int thresholdBlue = 30;
    int thresholdGreen = 70;
    int thresholdRed = 70;

    int targetBlue = 25;
    int targetGreen = 100;
    int targetRed = 130;

    for(int i=0; i<img->rows; i++){
        for(int j=0; j<img->cols; j++){
            
           std::vector<float> avgColor = getAvgColor(i,j,img);
            if( (avgColor[0] > targetBlue - thresholdBlue && avgColor[0] < targetBlue + thresholdBlue)      &&
                (avgColor[1] > targetGreen - thresholdGreen && avgColor[1] < targetGreen + thresholdGreen)  &&
                (avgColor[2] > targetRed - thresholdRed && avgColor[2] < targetRed + thresholdRed) ){
                    mask.at<unsigned char>(i,j) = 255;
                }
        }
    }
    
    destroyWindow("Masked shirt");
    namedWindow("Masked shirt");
    imshow ("Masked shirt", mask);

    colorTShirt(img, mask);

    return;

}

void colorTShirt(cv::Mat* img, Mat mask){

    Mat coloredMask;
    int rows = img->rows;
    int cols = img->cols;
    coloredMask = cv::Mat::zeros(rows,cols, CV_8UC3);

    int shirtColor[3] = {92,37,201};
    
    for(int i=0; i<img->rows; i++){
        for(int j=0; j<img->cols; j++){
           
            if(mask.at<unsigned char>(i,j) == 0){
                coloredMask.at<Vec3b>(i,j)[0] = img->at<Vec3b>(i,j)[0];
                coloredMask.at<Vec3b>(i,j)[1] = img->at<Vec3b>(i,j)[1];
                coloredMask.at<Vec3b>(i,j)[2] = img->at<Vec3b>(i,j)[2];
            }
            else{
                coloredMask.at<Vec3b>(i,j)[0] = shirtColor[0];
                coloredMask.at<Vec3b>(i,j)[1] = shirtColor[1];
                coloredMask.at<Vec3b>(i,j)[2] = shirtColor[2];
            }  
        }
    }
    
    destroyWindow("Coloredshirt");
    namedWindow("Colored shirt");
    imshow ("Colored shirt", coloredMask);
    waitKey(0);

    return;

}

std::vector<float> getAvgColor(int x,int y, cv::Mat* img) {

    float avg[3] = {0.0,0.0,0.0}; 
    for(int i = x-4; i < x+4; i++){
        for(int j = y-4; j < y+4; j++){
            if(i >= 0 & j>=0 && i<img->rows && j<img->cols){
                avg[0] +=  (int) img->at<Vec3b>(i, j) [0];
                avg[1] +=  (int) img->at<Vec3b>(i, j) [1];
                avg[2] +=  (int) img->at<Vec3b>(i, j) [2];
            }
        }
    }

    std::vector<float> avgColor(3);

    avgColor[0] =  avg [0] / (9*9);
    avgColor[1] = avg [1] / (9*9);
    avgColor[2] = avg [2] / (9*9);

    return avgColor; 

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