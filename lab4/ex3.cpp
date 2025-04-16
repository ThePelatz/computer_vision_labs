#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
    // if(argc<2){
    //     std::cout << "Uncorrect number of parameters. Please specify the name of the image.\n";
    //     return 0;
    // }
    
    // cv::Mat src = cv::imread(argv[1]);
    cv::Mat src = cv::imread("street_scene.png");

    if(src.rows == 0 && src.cols == 0){
        std::cout << "Impossible to open the image 'street_scene.png '\n";
        return 0;
    }
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    vector<Vec3f> circles;
    medianBlur(gray, gray, 7);

    for(int i=0; i < gray.rows; i++){
        for(int j=0; j < gray.cols; j++){
            Vec3b color = src.at<Vec3b>(i, j);
            int offset = 20;

            // Yellow filter: isolating yellow road signs
            if(color[1] > 120 - offset && color[2] > 150 -offset && color[0] < 100 + offset){
            gray.at<unsigned char>(i, j) = 255;
            }
            else{
            gray.at<unsigned char>(i, j) = 0;
            }
        }
    }
    medianBlur(gray, gray, 7);

    imshow("Gray image", gray);
    cv::Mat cpy = src.clone();

    HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
                 gray.rows/16,  // change this value to detect circles with different distances to each other
                 10, 10, 1, 50 // change the last two parameters
            // (min_radius & max_radius) to detect larger circles
    );
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        // circle center
        circle( src, center, 1, Scalar(0,100,100), 3, LINE_AA);
        // circle outline
        int radius = c[2];
        circle( src, center, radius, Scalar(255,0,255), 3, LINE_AA);
    }

    imshow("detected circles", src);
    imshow("Original image", cpy);
    waitKey();
    return EXIT_SUCCESS;
}