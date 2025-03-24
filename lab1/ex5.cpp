
#include <opencv2/highgui.hpp>
using namespace cv;

int main(void)
{
    Mat img(256, 256, CV_8U);
    
    for (int i = 0; i < 256; ++i){
        for (int j = 0; j < 256; ++j){
            img.at<unsigned char> (i, j) = i;
        }
    }
    
    namedWindow("Example 5.1");
    imshow ("Example 5.1", img);
    waitKey(0);

    Mat img2(256, 256, CV_8U);
    
    for (int i = 0; i < 256; ++i){
        for (int j = 0; j < 256; ++j){
            img2.at<unsigned char> (i, j) = j;
        }
    }
    
    namedWindow("Example 5.2");
    imshow ("Example 5.2", img2);
    waitKey(0);

    
    Mat img3;
    int size = 300; 
    img3 = cv::Mat::zeros(size,size, CV_8U);

    int tile1 = 0;
    int count1 = 0; 
    int tile2 = 0;
    int count2 = 0; 
    int tileSize = 20; 

    for (int i = 0; i <size; ++i){
        if(count1 >= tileSize){
            if(tile1==1) tile1 = 0; else tile1 = 1;
            count1 = 0;
        }
        count1++;
        for (int j = 0; j < size; ++j){
            if(count2 >= tileSize){
                if(tile2==1) tile2 = 0; else tile2 = 1;
                count2 = 0;
            }
            count2++;
            img3.at<unsigned char> (i, j) = 255*((tile1+tile2)%2);
        }
    }
    
    namedWindow("Example 5.3");
    imshow ("Example 5.3", img3);
    waitKey(0);
    
    return 0;
}