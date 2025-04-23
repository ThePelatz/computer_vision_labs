#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int main() {
    Mat src = imread("street_scene.png");

    if (src.empty()) {
        cout << "Could not open or find the image!" << endl;
        return -1;
    }

    cv::Mat sky = cv::Mat::zeros(src.rows, src.cols, CV_8UC3);

    cv::Mat copy = src.clone();
    medianBlur(copy,copy, 7);

    int red=120,green=200,blue=255; 
    int offset = 60;

    for(int i=0; i<src.rows; i++){
        for(int j=0; j<src.cols; j++){

            int b =(int) copy.at<Vec3b>(i, j) [0];
            int g =(int) copy.at<Vec3b>(i, j) [1];
            int r =(int) copy.at<Vec3b>(i, j) [2];

            if(
                b > blue - offset && b < blue + offset &&
                g > green - offset && g < green + offset &&
                r > red - offset && r < red + offset 
            ){
                // sky.at<Vec3b>(i, j) [0] = blue;
                // sky.at<Vec3b>(i, j) [1] = green;
                // sky.at<Vec3b>(i, j) [2] = red;
                sky.at<Vec3b>(i, j) [0] = 0;
                sky.at<Vec3b>(i, j) [1] = 0;
                sky.at<Vec3b>(i, j) [2] = 255;
            }
            else{
                sky.at<Vec3b>(i, j) [0] = src.at<Vec3b>(i, j) [0];
                sky.at<Vec3b>(i, j) [1] = src.at<Vec3b>(i, j) [1];
                sky.at<Vec3b>(i, j) [2] = src.at<Vec3b>(i, j) [2];
            } 

        }
    } 



    imshow("Original Image", src);
    
    imshow("Sky", sky);

    waitKey(0);

    return 0;
}