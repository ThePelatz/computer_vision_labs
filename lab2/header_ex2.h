#ifndef HEADER_EX2
#define HEADER_EX2
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
#include <opencv2/imgproc.hpp>


void maxFilter(cv::Mat& img, int l);
void minFilter(cv::Mat& img, int l);
void medianFilter(cv::Mat& img, int l);


#endif