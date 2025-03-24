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


    Mat gray_scale(img.rows,img.cols, CV_8U);
 
    cvtColor(img,gray_scale, COLOR_BGR2GRAY);

    Mat filtered_image(img.rows,img.cols, CV_8U);
    
    //sobel filter
    std::vector<std::vector<int>> filter{ 
                                                { -1, 0 ,1 }, 
                                                { -2, 0, 2 },
                                                { -1, 0, 1 } 
                                         };

    //average filter
    /*
    std::vector<std::vector<int>> filter{   
                                            { 1, 1 ,1 }, 
                                            { 1, 1, 1 }, 
                                            { 1, 1, 1 } 
                                        };
    */

    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            for(int x = i-1; x<i+2; x++){
                for(int y=j-1; y<j+2;y++){
                    if(x >= 0 & y>=0 && x<img.rows && y<img.cols){
                        filtered_image.at<unsigned char> (i, j) =filtered_image.at<unsigned char> (i, j) + gray_scale.at<unsigned char> (x, y)*filter[x-i+1][y-j+1];
                    }
                }
            }
        }
    }


    //std::cout << "Image number of channels: " << img.channels() << "\n";
    cv::namedWindow("Example 1");
    cv::imshow("Example 1", gray_scale);

    cv::namedWindow("Example 2");
    cv::imshow("Example 2", filtered_image);
    cv::waitKey(0);
    

    return 0; 

}