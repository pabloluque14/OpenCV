#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include "examen.hpp"

using namespace cv;

cv::Mat cargar_y_suavizar (const std::string& filename, float sigma)
{

	cv:: Mat resultado= cv:: imread( filename, cv:: IMREAD_GRAYSCALE );

	cv:: GaussianBlur(resultado, resultado, sigma, sigma, cv:: Size(0,0));


	
	return resultado;
}

void calcular_media_desviacion(const cv::Mat& img, float& media, float& desv)
{
	media= 0.0;
    desv = 0.0;
	int tam = img.rows * img.cols;

	for (int i = 0; i < img.rows; ++i)
		for (int j = 0; j < img.cols; ++j)
		{
			
			media+= img.at<float>(i,j);

		}
		media/= tam;	

	for (int i = 0; i < img.rows; ++i)
		for (int j = 0; j < img.cols; ++j)
		{
			
			desv+= pow( media-img.at<float>(i,j), 2);

		}

		desv=sqrt(desv/tam,2);
    
}

void umbralizar_gradiente(const cv::Mat& gX, const cv::Mat& gY, float umbral, cv::Mat& segmentada)
{
	//Calculate the magnitude

	cv:: magnitude(gX,gY,segmentada);

	for (int i = 0; i < segmentada.rows; ++i)
	{
		for (int j = 0; j < segmentada.cols; ++j)
		{
			if (segmentada.at<float>(i,j) >= umbral )
			{
				segmentada.at<float>(i,j)=1;
			}else{

				segmentada.at<float>(i,j)=0;

			}
		}
	}
 
}

cv::Mat calcularBOVW(const std::vector<int> & wordsId, int dict_size)
{
 

	cv:: Mat bovw = cv:: Mat:: zeros(dict_size,1, CV_32FC1);


	for (int i = 0; i < wordsId.size(); ++i)
	{
		bovw.at<int>(0,wordsId[i])++;
	}

	sum=0;
	for (int i = 0; i < dict_size; ++i)
	{
		sum+=bovw.at<int>(0,i);
	}

	for (int i = 0; i < dict_size; ++i)
	{
		bovw.at<int>(0,i)/= sum;
	}

return bovw;
}

bool detectar_tablero(const cv::Mat& img, const cv::Size& tam, std::vector<cv::Point2f>& esquinas,const cv::TermCriteria& termcrit  )
{

	cv:: findChessboardCorners(img, tam, esquinas);

	 cv::cornerSubPix(img,esquinas, tam, cv:: Size(-1,-1), termcrit);



    return detectado;
}


//---------------------------------------





void calcular_media (const cv::Mat& img, float& r, float& g, float& b)
{
    r=0.0;
    g=0.0;
    b=0.0;
    //Escribe aquí tu código.
    //Write here your code.

for (double i=0; i<img.rows; i++){
	for (double j=0; j<img.cols; j++){
		const uchar * ptr = img.ptr<uchar>(i,j);
		b=(float)ptr[2]+b;
		g=(float)ptr[1]+g;
		r=(float)ptr[0]+r;
	}

}
b=b/(img.rows*img.cols);
g=g/(img.rows*img.cols);
r=r/(img.rows*img.cols);


    //-----------------------
}


std::vector<float> calcular_histograma(const cv::Mat& img)
{
	std::vector<float> hist;
	for(int i=0;i<256;i++){
		hist.push_back(0);
	}

for (double i=0; i<img.rows; i++){
	for (double j=0; j<img.cols; j++){
		float aux=(float)img.at<uchar>(i,j);
		hist.at(aux)++;
	}
}

    //-----------------------
    return hist;
}



void calcular_gradiente(const cv::Mat& imgGray, cv::Mat& gX, cv::Mat& gY)
{


cv::Sobel(imgGray,gX,CV_8U,1,0,3);
cv::Sobel(imgGray,gY,CV_8U,0,1,3);


}


void vecino_mas_cercano(const std::vector<cv::Mat> & src, const std::vector<cv::Mat> & dst, std::vector<int> & match)
{

cv::ml::Ptr<cv::ml::KNearest> classifier= cv::ml::KNearest::create();
classifier->setDefaultK(1);
classifier->setIsClassifier(true);
classifier->setAlgorithmType(cv::ml::KNearest::BRUTE_FORCE);
classifier->train(src,cv::ml::ROW_SAMPLE ,dst);

classifier->findNearest(src,1,match);


}


bool almacenar_calibracion(const std::string& filename,
                            const cv::Mat& k,
                            const cv::Mat& d,
                            const cv::Mat& r,
                            const cv::Mat& t)
{
   
    //Escribe aquí tu código.
    //Write here your code.
 	
 	bool es_correcto=false;
	cv::FileStorage fs = cv::FileStorage(filename, cv::FileStorage::WRITE);
	
	es_correcto=fs.isOpened();
	
	if(es_correcto){
		fs<<"k " << k;
		fs<<"d " << d;
		fs<<"r " << r;
		fs<<"t " << t;
	}

    //-----------------------
    return es_correcto;
}
