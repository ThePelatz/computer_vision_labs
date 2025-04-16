#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void searchWhiteLines(cv::Mat* img);
bool belowLine(float theta, float rho, int y, int x);
void colorRoadRegion(cv::Mat* img, vector<Vec2f> lines);


int main(int argc, char** argv)
{
    
   
    if(argc<2){
        std::cout << "Uncorrect number of parameters. Please specify the name of the image.\n";
        return 0;
    }
    
    cv::Mat src = cv::imread(argv[1]);

    if(src.rows == 0 && src.cols == 0){
        std::cout << "Impossible to open the image. Check the name of the file.\n";
        return 0;
    }


    
    imshow("Source", src);
    
    searchWhiteLines(&src);

    waitKey();
    return 0;
}

void searchWhiteLines(cv::Mat* img){

    Mat mask;
    int rows = img->rows;
    int cols = img->cols;
    mask = cv::Mat::zeros(rows,cols, CV_8U);
    
    
    int minThreshold = 220;

    for(int i=0; i<img->rows; i++){
        for(int j=0; j<img->cols; j++){
            
            if( (img->at<Vec3b>(i, j) [0] > minThreshold)      &&
                (img->at<Vec3b>(i, j) [1] > minThreshold)      &&
                (img->at<Vec3b>(i, j) [2] > minThreshold) ){
                    mask.at<unsigned char>(i,j) = 255;
                }
        }
    }

    
    Mat dst, cdst, cdstP;

    Canny(mask, dst, 50, 200, 7);
    
    cvtColor(dst, cdst, COLOR_GRAY2BGR);
    cdstP = img->clone();


    vector<Vec2f> lines;
    HoughLines(mask, lines, 1, CV_PI*2/ 180, 150); 

    
    std::cout << "Number of lines: " << lines.size() << std::endl;
    for (size_t i = 0; i < lines.size(); i++) {
        float rho = lines[i][0], theta = lines[i][1];
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        Point pt1, pt2;
        pt1.x = cvRound(x0 + 1000 * (-b)); 
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b)); 
        pt2.y = cvRound(y0 - 1000 * (a));
        line(cdstP, pt1, pt2, Scalar(0, 255, 0), 2, LINE_AA); 
    }
    
    imshow ("WhiteLines", mask);

    imshow("Detected Lines (in red) - Probabilistic Line Transform", cdstP);

    colorRoadRegion(img,lines);

    return;

}

bool belowLine(float theta, float rho, int x, int y){

    if ((-cos(theta)/sin(theta))*x + rho/sin(theta) < y)
        return true;
    else
        return false;
    

}


void colorRoadRegion(cv::Mat* img, vector<Vec2f> lines){

    cv::Mat result = img->clone();

    for(int i=0; i < result.rows; i++){
        for(int j=0; j < result.cols; j++){

            bool check = true; 
            for (size_t k = 0; k < lines.size(); k++) {
                float rho = lines[k][0], theta = lines[k][1];
                if(!belowLine(theta, rho, j, i)){
                    check = false;
                }
            }
            if(check) result.at<Vec3b>(i,j) = Vec3b(0, 0, 255);
        }
    }


    imshow("Road Region", result);


}