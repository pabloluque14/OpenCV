/*! \file train_bovw.cpp
    \brief Train a Bag of Visual Words model
    \authors Fundamentos de Sistemas Inteligentes en Vision
*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <tclap/CmdLine.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/ml/ml.hpp>


#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
//#include <unistd.h>
#include <ctype.h>
#include <cmath>

#include <tclap/CmdLine.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>

#include "common_code.hpp"

#define IMG_WIDTH 300
int
main(int argc, char * argv[])
{  
	TCLAP::CmdLine cmd("Testing the results with a given image", ' ', "0.0");

	TCLAP::ValueArg<std::string> imgArg("", "img", "input image.", false, "", "pathname");
	cmd.add(imgArg);
	TCLAP::ValueArg<std::string> configFile("", "config_file", "configuration file for the dataset.", false, "02_ObjectCategories_conf.txt", "pathname");
	cmd.add(configFile);
	TCLAP::ValueArg<std::string> dictionary("", "dict", "Dictionary of the boVw.", false, "dictionary.yml", "pathname");
	cmd.add(dictionary);
    TCLAP::ValueArg<std::string> descriptor("", "descriptor", "Descriptor used. Default SIFT.", false, "SIFT", "string");
    cmd.add(descriptor);
    TCLAP::ValueArg<int> thres_surf("", "thres_surf", "Threshold for surf. Default 300.", false, 300, "int");
    cmd.add(thres_surf);
    TCLAP::ValueArg<std::string> video("", "video", "input video", false, "", "pathname");
   	cmd.add(video);
   	TCLAP::ValueArg<std::string> classifierType("", "classifierType", "Classifier type. Default knn", false, "knn", "string"); //options: knn or svm
    cmd.add(classifierType);
    TCLAP::ValueArg<std::string> kernel("", "kernel", "[SVM] kernel type for svm. Default linear", false, "linear", "string"); //Options:linear,rbf or polinomial
    cmd.add(kernel);
    TCLAP::ValueArg<int> margin("", "margin", "[SVM] C parameter of SVM. Default 10", false, 10, "int");
    cmd.add(margin);
   	TCLAP::ValueArg<std::string> ntest("", "ntest", "Classifier YML file.", false, "classifier.yml", "pathname");
	cmd.add(ntest);



	cmd.parse(argc, argv);


	//Read dictionary
	cv::FileStorage dictFile;
	dictFile.open(dictionary.getValue(), cv::FileStorage::READ);
	int keywords;
	dictFile["keywords"]>>keywords;
	cv::Ptr<cv::ml::KNearest> dict = cv::Algorithm::read<cv::ml::KNearest>(dictFile.root());
	dictFile.release();
	

	cv::Mat predicted_labels,descriptors;
	std::vector<std::string> categories;
	std::vector<int> samples_per_cat;
	std::string basename = "../data";


	std::string dataset_desc_file = basename + "/" + configFile.getValue();
	int retCode;
	if ((retCode = load_dataset_information(dataset_desc_file, categories, samples_per_cat)) != 0)
	{
		std::cerr << "Error: could not load dataset information from '"
			<< dataset_desc_file
			<< "' (" << retCode << ")." << std::endl;
		exit(-1);
	}

	std::cout << "Found " << categories.size() << " categories: ";
	if (categories.size()<2)
	{
		std::cerr << "Error: at least two categories are needed." << std::endl;
		return -1;
	}

   for (size_t i=0;i<categories.size();++i)
		std::cout << categories[i] <<", ";
    	std::cout << std::endl;

   if(imgArg.getValue() == ""){
		
   		std:: cout<< "No input image"<<std:: endl;

	}else{


		std::string filename=imgArg.getValue();
		
		cv::Ptr<cv::ml::StatModel> classifier;

		if(classifierType.getValue()=="knn"){

			cv::Ptr<cv::ml::KNearest> knnClassifier = cv::Algorithm::load<cv::ml::KNearest>(ntest.getValue());
			classifier = knnClassifier;

		}else if(classifierType.getValue()=="svm"){

			cv::Ptr<cv::ml::SVM> svmClassifier = cv::Algorithm::load<cv::ml::SVM>(ntest.getValue());
			classifier = svmClassifier;
		}


		cv::Mat img = cv::imread(filename, cv::IMREAD_GRAYSCALE);

		if (img.empty()){

			std::cerr << "Error: could not read image '" << filename << "'." << std::endl;
			exit(-1);

		}else{

			resize(img, img, cv::Size(IMG_WIDTH, round(IMG_WIDTH*img.rows / img.cols))); 	

		}


		if(descriptor.getValue() == "SIFT"){

			descriptors = extractSIFTDescriptors(img,0);

		}else{

			descriptors = extractSURFDescriptors(img,thres_surf.getValue());

		}

		cv::Mat bovw = compute_bovw(dict,100, descriptors);


		classifier->predict(bovw, predicted_labels);

		std::cout<<"Image categorie: "<<categories[predicted_labels.at<float>(0,0)] << std::endl;


	} if(video.getValue() == ""){ //---------------- Option with input video-----------------

		std:: cout<<"No input video"<<std::endl;
	}else{

		cv::Ptr<cv::ml::StatModel> classifier;

		if(classifierType.getValue()=="knn"){

			cv::Ptr<cv::ml::KNearest> knnClassifier = cv::Algorithm::load<cv::ml::KNearest>(ntest.getValue());
			classifier = knnClassifier;

		}else if(classifierType.getValue()=="svm"){

			cv::Ptr<cv::ml::SVM> svmClassifier = cv::Algorithm::load<cv::ml::SVM>(ntest.getValue());
			classifier = svmClassifier;
		}

		cv::VideoCapture input;
		input.open(video.getValue());

		if (!input.isOpened())
		{
			std::cerr << "Error: the input stream is not opened.\n";
			abort();
		}

		cv::Mat inFrame;
		bool wasOk = input.read(inFrame);
		
		if (!wasOk)
		{
			std::cerr << "Error: could not read any image from stream.\n";
			abort();
		}

		double fps=25.0;
		fps=input.get(CV_CAP_PROP_FPS);
		int key = 0;

		std::cout<<"In the video there is or are these categories: ";
		std:: string cat_before="none";
		std:: string categoria;

		cv::Mat frameCopy;		
		while(wasOk && key!=27){

			cv::imshow ("Input video testing", inFrame);
			//frameCopy=inFrame.clone();
			cv::cvtColor(inFrame, inFrame, cv::COLOR_BGR2GRAY);
			
			resize(inFrame, inFrame, cv::Size(IMG_WIDTH, round(IMG_WIDTH*inFrame.rows / inFrame.cols)));
			
			if(descriptor.getValue() == "SIFT"){

				descriptors = extractSIFTDescriptors(inFrame,0);

			}else{

				descriptors = extractSURFDescriptors(inFrame,thres_surf.getValue());

			}
	
			cv::Mat bovw = compute_bovw(dict,100, descriptors);

			classifier->predict(bovw, predicted_labels);

			categoria=categories[predicted_labels.at<float>(0,0)];
			if(categoria != cat_before){
				
				std::cout<<categoria<< std::endl;
			}
			cat_before=categoria;

			wasOk=input.read(inFrame);
			key = cv::waitKey(20);
		
		}



	}

	return 0;
}