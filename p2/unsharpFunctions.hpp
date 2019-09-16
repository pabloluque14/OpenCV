#ifndef UNSHARPFUNCTIONS
#define UNSHARPFUNCTIONS
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <iostream>
#include <math.h>
#include <string>
#include <vector>


using namespace std;

cv::Mat createBoxFilter(int r);
void convolve( cv::Mat& in,  cv::Mat& filter, cv::Mat& out);
cv:: Mat createGaussianFilter(int r);
void medianFilter( cv::Mat& in, int r );
cv:: Mat sobelFilter(cv::Mat in );
#endif
