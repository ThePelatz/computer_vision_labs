
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>

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

    char channels =  img.channels();
    std::cout << "Number of channels: " << channels; 

    if(channels==3){
        for (int i = 0; i < img.rows; ++i)
        {
            for (int j = 0; j < img.cols; ++j)
            {
                img.at<Vec3b> (i, j)[0] = 0;    //blue channel
                //img.at<Vec3b> (i, j)[1] = 0;    //green channel
                //img.at<Vec3b> (i, j)[2] = 0;    //red channel 
            }
        }
        
    }
    std::cout << "Image number of channels: " << img.channels() << "\n";
    cv::namedWindow("Example 1");
    cv::imshow("Example 1", img);
    
    cv::waitKey(0);
    
    return 0;
    
}