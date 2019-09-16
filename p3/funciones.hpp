#ifndef FUNCIONES
#define FUNCIONES


#include <opencv2/videoio.hpp>
#include <vector>
#include <iostream>
#include <opencv2/core/core.hpp> 
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>

bool detectar_tablero(const cv::Mat& img, const cv::Size& tam, std::vector<cv::Point2f>& esquinas,
                      const cv::TermCriteria& termcrit = cv::TermCriteria(cv::TermCriteria::COUNT|cv::TermCriteria::EPS,20,0.03));

#endif