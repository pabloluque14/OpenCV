

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>


#include "funciones_p5.hpp"

cv::Mat extractSIFTDescriptors(const cv::Mat& img, const int ndesc)
{
	
	std::vector< cv::KeyPoint > kps;
	cv:: Mat descs;

	cv:: Ptr<cv::xfeatures2d::SIFT> sift = cv::xfeatures2d::SIFT::create(ndesc);

	sift->detectAndCompute(img, cv:: noArray(),kps,descs);

    return descs;
}


cv::Mat extractSURFDescriptors(const cv::Mat& img, const int thresh)
{

	std::vector< cv::KeyPoint > kps;
	cv:: Mat descs;

	cv:: Ptr<cv::xfeatures2d::SURF> surf = cv::xfeatures2d::SURF::create(thresh);

	surf->detectAndCompute(img, cv:: noArray(),kps,descs);


    return descs;
}




void entrenar_diccionario(const cv:: Mat indexes, cv:: Mat & keyws)
{

	cv::Ptr<cv::ml::KNearest> dict = cv::ml::KNearest::create();
	dict->setAlgorithmType(cv::ml::KNearest::BRUTE_FORCE);
	dict->train(indexes,cv::ml::ROW_SAMPLE,keyws);


}


void entrenar_calsificadorKN(const int k, const cv:: Mat train_bovw, cv:: Mat & train_labels)
{

	cv::Ptr<cv::ml::StatModel> classifier;
	cv::Ptr<cv::ml::KNearest> knn = cv::ml::KNearest::create();
	knn->setAlgorithmType(cv::ml::KNearest::BRUTE_FORCE);
	knn->setDefaultK(k);
	knn->setIsClassifier(true);

	classifier=knn;

	classifier->train(train_bovw,cv::ml::ROW_SAMPLE,train_labels);


}


//hay dos maneras para el compute bovw que son casi las mismas
cv::Mat compute_bovw (const cv::Ptr<cv::ml::KNearest>& dict, const int dict_size, cv::Mat& img_descs)
{
    cv::Mat bovw = cv::Mat::zeros(1,dict_size,CV_32FC1);
    cv::Mat vwords;
    
    CV_Assert(img_descs.type()==CV_32F);
    
    dict->findNearest(descs,1,vwords);
    
    CV_Assert(vwords.depth()==CV_32F);

    for (int i = 0; i < img_descs.rows; ++i)
    {
    	bovw.at<float>(vwords.at<float>(i))+=1.0;
    }

   bovw /= float(img_descs.rows);

    
    
    return bovw;
}



cv::Mat compute_bovw2(const std::vector<int> & vwords, int dict_size)
{
 

	cv:: Mat bovw = cv:: Mat:: zeros(1, dict_size, CV_32FC1);

	for (int i = 0; i < vwords.size(); ++i)
	{
		bovw.at<float>(vwords[i])++;
	}
	 float sum=0.0;

	for (int i = 0; i < vwords.size(); ++i)
	{
		sum+=bovw.at<float>(i);
	}

	for (int i = 0; i < vwords.size(); ++i)
	{
		bovw.at<float>(i) /= sum;
	}


	return bovw;
}


void vecino_mas_cercano(const std::vector<cv::Mat> & src, const std::vector<cv::Mat> & dst, std::vector<int> & match)
{

	cv:: Ptr<cv::ml::KNearest> knn= cv::ml::KNearest::create();
	knn->setAlgorithmType(cv::ml::KNearest::BRUTE_FORCE);
	knn->setDefaultK(1);
	knn->setIsClassifier(true);

	knn->train(src,cv::ml::ROW_SAMPLE,dst);

	knn->predict(dst,match);




}



cv::Mat compute_confusion_matrix(int n_categories, const cv::Mat& true_labels, const cv::Mat& predicted_labels)
{
    CV_Assert(true_labels.rows == predicted_labels.rows);
    CV_Assert(true_labels.type()==CV_32FC1);
    CV_Assert(predicted_labels.type()==CV_32FC1);

    cv::Mat matrix = cv::Mat::zeros(n_categories,n_categories, CV_32FC1);

    for (int i = 0; i < true_labels.rows; ++i)
    {
    	matrix.at<float>(true_labels.at<float>(i),predicted_labels.at<float>(i))+= 1.0;
    }
 
}


void cargarDiccionario(const string dictFile){

	cv:: FileStorage dict;

	dict.open(dictFile,cv::FileStorage::OPEN);

	cv::Ptr<cv::ml::KNearest> dictk = cv::Algoritm::read(dict.root());



}



void cargarClasificador(const string classFile){

	cv::Ptr<cv::ml::StatModel>classifier;

	cv::Ptr<cv::ml::KNearest> knn = cv::Algoritm::load<cv::ml::KNearest(classFile)>;


	classifier=knn;


}



void ejecutar_kmeans(cv:: TermCriteria termcrit, std::vector<cv::Point2f> points, int k){

	std::vector<int> best_labels;

	cv::kmeans(points,k, best_labels, termcrit,3, cv::KMEANS_PP_CENTERS );
}