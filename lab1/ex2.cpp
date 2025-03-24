// OpenImg.cpp
#include <opencv2/highgui.hpp>
#include <iostream>

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

    std::cout << "Image number of channels: " << img.channels() << "\n";

    cv::namedWindow("Example 1");
    cv::imshow("Example 1", img);
    char key = cv::waitKey(0);

    std::cout << "Key pressed: " << key << "\n"; 
    
    
    return 0;

}
