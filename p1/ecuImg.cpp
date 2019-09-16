#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <tclap/CmdLine.h>
#include "histogram.hpp"

using namespace std;

int main(int argc,char **argv){


	TCLAP::CmdLine cmd("Testing the results with a given image", ' ', "0.0");

	TCLAP::ValueArg<int> radius("", "r", "radius.", true,0, "int");
	cmd.add(radius);
	TCLAP::ValueArg<std::string> inputImage("", "input", "input image", true, "cells.png", "pathname");
	cmd.add(inputImage);
	TCLAP::ValueArg<std::string> outputImage("", "output", "output image", false, "output", "string");
	cmd.add(outputImage);
	TCLAP::ValueArg<std::string> maskImage("", "mask", " mask to apply", false, "", "pathname");
	cmd.add(maskImage);
	TCLAP::ValueArg<int> hsvFlag("", "hsv", "hsv format", false, 0, "int");
	cmd.add(hsvFlag);
	TCLAP::ValueArg<int> bFlag("", "b", "b value", false, 0, "int");
	cmd.add(bFlag);
	cmd.parse(argc, argv);


	
	int r= radius.getValue();

	cv::Mat input=cv::imread(inputImage.getValue());

	cv:: Mat input2;
	input.copyTo(input2);
	
	//cout<<"Canales-> "<<input.channels()<<endl;
	//cout<<"Tipo-> "<<input.type()<<endl;
	if( input.rows==0) {cerr<<"Error reading image"<<endl;return 0;}
	if(input.channels() > 1) {cv::cvtColor(input, input, CV_RGB2GRAY);}


	cv:: Mat mask;
	if(maskImage.getValue() != ""){

		mask=cv::imread(maskImage.getValue());
		
		if( mask.rows==0) {cerr<<"Error reading mask"<<endl;return 0;}
		
		if(mask.channels() > 1) {cv::cvtColor(mask, mask, CV_RGB2GRAY);}

	}


	cv::Mat output(input.rows,input.cols,CV_8UC1);
	
	input.copyTo(output);

	
	if(r == 0){



		if(maskImage.getValue() == "" ){

			if (hsvFlag.getValue()== 1)
			{
				cv:: Mat output= CalculateEqualizationHSV(input2);

				cv::namedWindow("output");
				//displays the image in the window
				cv::imshow(outputImage.getValue(),output);
				//wait for a key to be pressed
				cv::waitKey(0);

			
			}else{

				if(bFlag.getValue() == 1){

					
					ecualizationByBipartition(input);
				
					cv::namedWindow("output");
					//displays the image in the window
					cv::imshow(outputImage.getValue(),input);
					//wait for a key to be pressed
					cv::waitKey(0);

				}else{

					CalculateEqualization(input);

					cv::namedWindow("output");
					//displays the image in the window
					cv::imshow(outputImage.getValue(),input);
					//wait for a key to be pressed
					cv::waitKey(0);
				}
			}	
		
		}else{

			
			CalculateEqualization(input,mask);

			cv::namedWindow(outputImage.getValue());
			//displays the image in the window
			cv::imshow(outputImage.getValue(),input);
			//wait for a key to be pressed
			cv::waitKey(0);

		}

	}else{ // Si se ha introducido la opción r

			
			if(maskImage.getValue() == "" ){

				

				windowEqualization( input,output,r);
			
				cv::namedWindow(outputImage.getValue());
				//displays the image in the window
				cv::imshow(outputImage.getValue(),output);
				//wait for a key to be pressed
				cv::waitKey(0);
			
			}else{ //Opción r with mask


				windowEqualization( input,output,r, mask);
	
			
				cv::namedWindow(outputImage.getValue());
				//displays the image in the window
				cv::imshow(outputImage.getValue(),output);
				//wait for a key to be pressed
				cv::waitKey(0);

			}

	}

return 0;
}