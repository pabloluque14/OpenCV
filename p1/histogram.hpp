#ifndef HISTOGRAM
#define HISTOGRAM

#include <opencv2/core/core.hpp> //core routines
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <iostream>
#include <math.h>
#include <string>
#include <vector>


using namespace std;

vector<int> CalculateHistogram( cv::Mat & image);
vector<int> CalculateCumulativeHistogram(vector<int> h);
void CalculateEqualization(cv::Mat & input);
void CalculateEqualization(cv::Mat & input, std::vector<int> h);
cv:: Mat CalculateEqualizationHSV(cv::Mat & input);
void CalculateEqualization(cv::Mat & input, cv::Mat mask);
void CalculateEqualization(cv::Mat & input, cv::Mat mask, std::vector<int> h);
void windowEqualization(cv::Mat & input, cv::Mat & output, int r);
void windowEqualization(cv::Mat & input, cv::Mat & output, int r, cv::Mat mask);

void ecualizationByBipartition(cv:: Mat & input);
void biecualization(std::vector<int> histogramMayor, std::vector<int> histogramMenorIgual, cv:: Mat & input, int b);
int calcularMediana(std:: vector<int> v);
#endif