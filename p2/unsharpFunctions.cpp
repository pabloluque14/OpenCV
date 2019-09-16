#include "unsharpFunctions.hpp"


//crea un box filter de radio r
cv::Mat createBoxFilter(int r){

	int tam= (2*r)+1;
	float value= 1.0/pow(tam,2);

	cv:: Mat filter(tam, tam, CV_32FC1);

	for (int i = 0; i < filter.rows; ++i)
	{
		float * filterPtr = filter.ptr<float>(i);

		for(int j=0; j < filter.cols; j++){

			filterPtr[j]=value;
		}
	}

 	return filter;

}


//crea un filtro gaussiano de radio r
cv:: Mat createGaussianFilter(int r){
	int tam = 2*r +1;

	cv :: Mat filter(tam,tam,CV_32FC1);

	float sigma=5.0;
	const double pi = 3.1415926535897;

    double sum=0.0;
    int i,j;

    for(int i =0; i< filter.rows; i++)
    {
    	float * ptr = filter.ptr<float>(i);

    	for(int j=0; j < filter.cols; j++)
    	{

    			ptr[j] = ( exp(-(i*i + j*j) / 2* sigma * sigma) / (2*pi*sigma*sigma) );
    			sum+=ptr[j];
    	}
    }

    filter /= sum;

return filter;
}


//dado un filtro de entrada le aplica una convolucion a una imagen de entrada
void convolve( cv::Mat& in,  cv::Mat& filter, cv::Mat& out){
	

assert(!in.empty() && in.type()==CV_32FC1);
assert(!filter.empty() && filter.type()==CV_32FC1);
assert((filter.rows%2)!=0 && (filter.cols%2)!=0);

out= cv:: Mat:: zeros(in.rows,in.cols,in.type());

int r = (filter.rows-1)/2;
float sum=0.0;

for (int i = r; i < (in.rows-r); i++){

	float * outPtr = out.ptr<float>(i);

	for(int j = r; j < (in.cols-r); j++){

		for (int k=i-r, xx=0; k<=(i+r); k++,xx++){

			float * inPtr = in.ptr<float>(k);
			float * filterPtr = filter.ptr<float>(xx);

			for (int l=j-r, yy=0; l<=(j+r); l++, yy++){

				sum+= inPtr[l] * filterPtr[yy];

			}
		}

		outPtr[j]=sum;
		sum=0.0;
	
	}
}
	


}

//ejercicio de examen: aplicar un filtro de mediana para una matriz de entrada y un radio r
void medianFilter( cv::Mat& in, int r ){

assert(!in.empty() && in.type()==CV_8UC1);

int tam= (2*r) +1;

std::vector<uchar> v;

for(int i = r; i < (in.rows-r); i++)
{
	uchar * ptrfil = in.ptr<uchar>(i);

	for(int j = r; j < (in.cols-r); j++){

		
		for(int xx=i-r; xx <= i+r; xx++)
		{

			uchar * ptr = in.ptr<uchar>(xx);

			for(int yy = j-r; yy <= j+r ; yy++)
			{

				v.push_back(ptr[yy]);

			}

		}

		std::sort(v.begin(), v.end());


		ptrfil[j]=v[ (v.size()-1)/2 ];
		v.clear();



	}
}

}



//aplica un filtro de sobel sobre una matriz 
cv:: Mat sobelFilter(cv::Mat in ){

assert(!in.empty() && in.type()==CV_8UC1);

cv:: Mat grad_x, grad_y, grad;


cv::Sobel(in,grad_x,CV_8UC1,1,0);
cv::Sobel(in,grad_y,CV_8UC1,0,1);

cv::addWeighted(grad_x,0.5,grad_y,0.5,0,grad);


return grad;
}