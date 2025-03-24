#include "header_ex2.h"


using namespace cv; 
void maxFilter(cv::Mat& img, int l){

    if(!l%2){
        std::cout << "Invalid dimension of the filter";
        return; 
    }

    int max = 0; 

    Mat maxImage(img.rows,img.cols, CV_8U);

    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            max = img.at<unsigned char> (i, j);
            for(int x = i-(l/2); x<i+(l/2+1); x++){
                for(int y=j-(l/2); y<j+(l/2+1);y++){
                    if(x >= 0 & y>=0 && x<img.rows && y<img.cols){
                        if(max < img.at<unsigned char> (x, y)) max = img.at<unsigned char> (x, y);
                    }
                }
            }
            maxImage.at<unsigned char> (i, j) =max; 
        }
    
    
    }
    
    cv::namedWindow("MaxFilter");
    cv::imshow("MaxFilter", maxImage);
    cv::waitKey(0);


}
void minFilter(cv::Mat& img, int l){

    if(!l%2){
        std::cout << "Invalid dimension of the filter";
        return; 
    }

    int min = img.at<unsigned char> (0, 0); 

    Mat minImage(img.rows,img.cols, CV_8U);

    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            min = img.at<unsigned char> (i, j);
            for(int x = i-(l/2); x<i+(l/2+1); x++){
                for(int y=j-(l/2); y<j+(l/2+1);y++){
                    if(x >= 0 & y>=0 && x<img.rows && y<img.cols){
                        if(min > img.at<unsigned char> (x, y)) min = img.at<unsigned char> (x, y);
                    }
                }
            }
            minImage.at<unsigned char> (i, j) = min; 
        }
    }    

    cv::namedWindow("MinFilter");
    cv::imshow("MinFilter", minImage);
    cv::waitKey(0);



}

void medianFilter(cv::Mat& img, int l){

    if(!l%2){
        std::cout << "Invalid dimension of the filter";
        return; 
    }

    std::vector<unsigned char> median;

    Mat medianImage(img.rows,img.cols, CV_8U);

    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {

            for(int x = i-(l/2); x<i+(l/2+1); x++){
                for(int y=j-(l/2); y<j+(l/2+1);y++){
                    if(x >= 0 & y>=0 && x<img.rows && y<img.cols){
                        median.push_back(img.at<unsigned char> (x, y));
                    }
                    else{
                        median.push_back(0);
                    }
                }
            }

            
            std::sort(median.begin(), median.end());
        
            if(l%2){
                medianImage.at<unsigned char> (i, j) = median.at(l/2); 
            }
            else{
                medianImage.at<unsigned char> (i, j) =(median.at(l / 2 - 1) + median.at(l / 2)) / 2;
            }
            
            median.clear();
        }
    }    

    cv::namedWindow("MedianFilter");
    cv::imshow("MedianFilter", medianImage);
    cv::waitKey(0);



}