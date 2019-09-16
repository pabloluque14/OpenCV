#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <tclap/CmdLine.h>

#include "unsharpFunctions.hpp"

using namespace std;

int main(int argc,char **argv){

		TCLAP::CmdLine cmd("Testing the results with a given image", ' ', "0.0");
		TCLAP::ValueArg<int> radius("", "r", "radius.", true,1, "int");
		cmd.add(radius);
		TCLAP::ValueArg<float> ganancia("", "g", "ganancia.", true,1.0, "float");
		cmd.add(ganancia);
		TCLAP::ValueArg<std::string> inputImage("", "input", "input image", true, "cells.png", "pathname");
		cmd.add(inputImage);
		TCLAP::ValueArg<std::string> outputImage("", "output", "output image", false, "output", "string");
		cmd.add(outputImage);
		TCLAP::ValueArg<int> optionFilter("", "op", "option filter, 0 - box, 1 - gauss ", false, 0, "int");
		cmd.add(optionFilter);
		cmd.parse(argc, argv);
		

		int r = radius.getValue();
		float sigma,g = ganancia.getValue(); 
		string out=outputImage.getValue();
		cv::Mat I=cv::imread(inputImage.getValue());
		int op = optionFilter.getValue();
		
		if( I.rows==0) {cerr<<"Error reading image"<<endl;return 0;}
		if(I.channels() > 1) {cv::cvtColor(I, I, CV_RGB2GRAY);}


		if(r < 0){cerr<<"ERROR: r debe ser mayor que 0"<<endl;return 0;}

   		if(g < 0.0 || g > 10.0 ){cerr<<"ERROR: g > 0 o g < 10"<<endl;return 0;}
	

		
   		I.convertTo(I, CV_32FC1);
		cv::Mat IL(I.rows,I.cols,CV_32FC1);
		cv::Mat IL2(I.rows,I.cols,CV_32FC1);
		
		cv::Mat O, filter, I2;


		switch(op){

			case 0:
					
					filter=createBoxFilter(r);
					convolve(I,filter,IL);

					O = ( ((g+1)*I) - (g*IL) );

					cv:: filter2D(I,IL2,I.depth(),filter); // si en el examen no va, hacer esto

					O.convertTo(O,CV_8UC1);
					IL.convertTo(IL,CV_8UC1);
					IL2.convertTo(IL2,CV_8UC1);


					
					//creates a window
				   	cv::namedWindow("IL");
				   	//displays the image in the window
				   	cv::imshow("IL",IL);

				   	//creates a window
				   	cv::namedWindow("IL2");
				   	//displays the image in the window
				   	cv::imshow("IL2",IL2);

				   	//creates a window
				   	cv::namedWindow("O");
				   	//displays the image in the window
				   	cv::imshow("O",O);

				
				   	//wait for a key to be pressed
				   	cv::waitKey(0);


			break;

			case 1:
					filter=createGaussianFilter(r);

					convolve(I,filter,IL);

					sigma=5.0;

					I.convertTo(I,CV_8UC1);
    				
    				GaussianBlur(I,I,cv::Size(2*r+1,2*r+1),sigma,sigma);

    				IL.convertTo(IL,CV_8UC1);
    				

				   	//creates a window
				   	cv::namedWindow("IL");
				   	//displays the image in the window
				   	cv::imshow("IL",IL);


				   	//creates a window
				   	cv::namedWindow("I - LLamando a la funcion");
				   	//displays the image in the window
				   	cv::imshow("I - LLamando a la funcion",I);
				
				   	//wait for a key to be pressed
				   	cv::waitKey(0);

			break;


			case 2:

					I.convertTo(I,CV_8UC1);

					medianFilter(I,r);
					I.copyTo(I2);

					cv::medianBlur(I, I2, r);
				   	
				   	//creates a window
				   	cv::namedWindow("medianFilter");
				   	//displays the image in the window
				   	cv::imshow("medianFilter",I);


				   	//creates a window
				   	cv::namedWindow("medianBlur");
				   	//displays the image in the window
				   	cv::imshow("medianBlur",I2);
				
				   	//wait for a key to be pressed
				   	cv::waitKey(0);

			break;



			case 3:

					I.convertTo(I,CV_8UC1);
					IL.convertTo(IL,CV_8UC1);

					cv:: bilateralFilter ( I, IL, 9, 80, 80 );

					//creates a window
				   	cv::namedWindow("bilateral filter");
				   	//displays the image in the window
				   	cv::imshow("bilaterak filter",IL);

				   	//creates a window
				   	cv::namedWindow("original");
				   	//displays the image in the window
				   	cv::imshow("original",I);
				
				   	//wait for a key to be pressed
				   	cv::waitKey(0);

			break;

			case 4:

					I.convertTo(I,CV_8UC1);
					IL.convertTo(IL,CV_8UC1);

					IL=sobelFilter(I);

					//creates a window
				   	cv::namedWindow("sobel filter");
				   	//displays the image in the window
				   	cv::imshow("sobel filter",IL);

				   	//creates a window
				   	cv::namedWindow("original");
				   	//displays the image in the window
				   	cv::imshow("original",I);
				
				   	//wait for a key to be pressed
				   	cv::waitKey(0);

			break;

		}

		
	




	}