
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

    cv::Mat imgs[3];
    for (int k = 0; k < 3; k++) {
        imgs[k] = cv::Mat::zeros(img.rows, img.cols, CV_8UC3);
    }


    if(channels==3){

        for(int k=0; k<3; k++){
            for (int i = 0; i < img.rows; ++i)
            {
                for (int j = 0; j < img.cols; ++j)
                {
                    imgs[k].at<Vec3b> (i, j)[k] = img.at<Vec3b> (i, j)[k];
                }
            }
        }
        
    }

    std::cout << "Image number of channels: " << img.channels() << "\n";
    cv::namedWindow("Example 1");
    cv::imshow("Example 1", img);
    cv::waitKey(0);

    for(int k=0; k<3; k++){
        cv::namedWindow("Example");
        cv::imshow("Example", imgs[k]);
        cv::waitKey(0);
    }
    
    
    
    return 0;
    
}