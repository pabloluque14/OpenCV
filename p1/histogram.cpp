
#include "histogram.hpp"


/*Recorrer la matriz, e ir incrementando el valor del pixel en uno*/
vector<int> CalculateHistogram( cv::Mat & image) {
	
std::vector<int> histogram(256);

	for(int i =0; i < image.rows ; i++){

		uchar * ptrImage = image.ptr<uchar>(i);

		for(int j =0; j < image.cols ; j ++){

			histogram[ptrImage[j]] ++;
		}
	}

	
	return histogram;
}


vector<int> CalculateCumulativeHistogram(vector<int> h) {

	for (int i = 1; i < h.size(); ++i)
	{
		h[i]+=h[i-1];
	}


	std::vector<int> v(h.size(),0);

	for (int i = 0; i < h.size(); ++i)
	{
		
		v[i]= ((h[i]*255)/h[h.size()-1]);
		
	}

	
	return v;
}

//Para calcular la ecualización coges el histogram acumulado y a la matriz salida le pones el valor del subpixel
void CalculateEqualization(cv::Mat & input) {
std::vector<int> h(256);

for (int i = 0; i < input.rows; ++i)
{
	uchar * inputPtr = input.ptr<uchar>(i);
	for (int j = 0; j < input.cols; ++j)
	{
		h[inputPtr[j]]++;
		
	}
}


for (int i = 1; i < h.size(); ++i)
{
	h[i] +=h[i-1];
}

for (int i = 0; i < h.size(); ++i)
{
	h[i]= (h[i]*255)/h[h.size()-1];
}


for (int i = 0; i < input.rows; ++i)
{

	uchar * inputPtr = input.ptr<uchar>(i);

	for (int j = 0; j < input.cols; ++j)
	{
		inputPtr[j]=h[inputPtr[j]];


	}
}


}




void CalculateEqualization(cv::Mat & input, std::vector<int> h) {

for (int i = 0; i < input.rows; ++i)
{
	uchar * ptrInput= input.ptr<uchar>(i);

	for (int j = 0; j < input.cols; ++j)
	{
		ptrInput[j]=h[ptrInput[j]];
	}
}


}



// Con máscara es lo mismo, pero con tres punteros y en los valores distintos de cero
void CalculateEqualization(cv::Mat & input, cv::Mat mask) {

vector<int> h(256);	

for(int i=0 ; i < input.rows ; i++){

	uchar * ptrInput = input.ptr<uchar>(i);

	for(int j=0; j < input.cols; j++){

		h[ptrInput[j]]++;
	}
}


for(int i = 1; i < h.size(); i++){

	h[i]+= h[i-1];
}



for (int i = 0; i < h.size(); ++i)
{
	h[i]= ((h[i]*255) / h[h.size()-1]);

}


for (int i=0; i < input.rows; i++){

	uchar * inputPtr= input.ptr<uchar>(i);
	uchar * maskPtr = mask.ptr<uchar>(i);

	for(int j=0; j < input.cols; j++){

		if (maskPtr[j] != 0){
			inputPtr[j]=h[inputPtr[j]];
		}

	}
}

}





void CalculateEqualization(cv::Mat & input, cv::Mat mask, std::vector<int> h) {

for (int i=0; i < input.rows; i++){

	uchar * inputPtr= input.ptr<uchar>(i);
	uchar * maskPtr = mask.ptr<uchar>(i);

	for(int j=0; j < input.cols; j++){

		if (maskPtr[j] != 0){
			inputPtr[j]=h[inputPtr[j]];
		}

	}
}

}


//Aqui si hace falta matriz de salida !!!!
void windowEqualization(cv::Mat & input, cv::Mat & output, int r) {

for (int i = r; i < input.rows-r; ++i)
{
		uchar * inputPtr = input.ptr<uchar>(i);
		uchar * outputPtr = output.ptr<uchar>(i);
	

	for (int j = r; j < input.cols-r; ++j)
	{
		
		cv:: Range RangeR(i-r,i+r);
		cv:: Range RangeC(j-r,j+r);

		cv:: Mat window=input.operator()(RangeR,RangeC);

		std::vector<int> h(256);

		for (int k = 0 ; k < window.rows; ++k)
		{
			uchar * windowPtr = window.ptr<uchar>(k);

			for (int l = 0; l < window.cols; ++l)
			{

				h[windowPtr[l]]++;

			}
		}


		for(int i = 1; i < h.size(); i++){

			h[i]+= h[i-1];
		}



		for (int i = 0; i < h.size(); ++i)
		{
			h[i]= ((h[i]*255) / h[h.size()-1]);
		}

		outputPtr[j]=h[inputPtr[j]];


	}

}

}


void windowEqualization(cv::Mat & input, cv::Mat & output, int r, cv::Mat mask) {
	

for (int i = r; i < input.rows-r; ++i)
{

	uchar * inputPtr = input.ptr<uchar>(i);
	uchar * outPtr = output.ptr<uchar>(i);
	uchar * maskPtr = mask.ptr<uchar>(i);


	for (int j = r; j < input.cols-r; j++){


		cv:: Range RangeR(i-r,i+r);
		cv:: Range RangeC(j-r,j+r);

		cv:: Mat window = input.operator()(RangeR,RangeC);

		std::vector<int> h(256,0);

		for(int k =0; k< window.rows; k++){

			uchar * windowPtr = window.ptr<uchar>(k);

			for(int l =0; l < window.cols; l++){

				h[windowPtr[l]]++;
			}

		}

		for(int i = 1; i < h.size(); i++){

			h[i]+= h[i-1];
		}



		for (int i = 0; i < h.size(); ++i)
		{
			h[i]= ((h[i]*255) / h[h.size()-1]);

		}

		if(maskPtr[j] != 0){

			outPtr[j]=h[inputPtr[j]];


		}




	}
}
		

}


cv:: Mat CalculateEqualizationHSV(cv:: Mat & input){

	cv:: Mat result;

	cv::cvtColor(input,input,CV_RGB2HSV);

	std::vector<cv::Mat> v;

	cv::split(input,v);

	cv::equalizeHist(v[2],v[2]);

	cv::merge(v,result);


	cv::cvtColor(result,result,CV_HSV2RGB);

	return result;

}


void biecualization(std::vector<int> histogramMayor, std::vector<int> histogramMenorIgual, cv:: Mat & input, int b){

for (int i = 0; i < input.rows; ++i)
{

	uchar * inputPtr = input.ptr<uchar>(i);

	for(int j=0; j < input.cols; j++){

		if (inputPtr[j] <= b ){
			
			inputPtr[j]=histogramMenorIgual[inputPtr[j]];
			
		}else{

			
			inputPtr[j]=histogramMayor[inputPtr[j] - b];

		
		}

	}
}



}




void ecualizationByBipartition(cv:: Mat & input){

	std::vector<int> histogram(256,0);
	std::vector<int> histogramMenorIgual, acumuladoMenorIgual;
	std::vector<int> histogramMayor, acumuladoMayor;


	histogram=CalculateHistogram(input);

	std::vector<int> v=histogram;
	std::sort(v.begin(), v.end());

	int b= calcularMediana(v);

	for (int i = 0; i < histogram.size(); ++i)
	{
		if (histogram[i] > b)
		{

			histogramMayor.push_back(histogram[i]);
		}else{

		 	histogramMenorIgual.push_back(histogram[i]);

		}
	}


	acumuladoMayor= CalculateCumulativeHistogram(histogramMayor);
	acumuladoMenorIgual= CalculateCumulativeHistogram(histogramMenorIgual);
	

	biecualization(acumuladoMayor, acumuladoMenorIgual, input, b);



}



int calcularMediana(std:: vector<int> v){
	return (int)((v[(v.size()/2)-1] + v[(v.size()/2)] ) /2);
}