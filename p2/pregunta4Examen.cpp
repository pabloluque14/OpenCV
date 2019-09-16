#include <opencv2/core.hpp>
#include <opencv2/ml.hpp>
#include <algorithm>
/**
 * @brief  Aplica el filtro mediana a la imagen de entrada usando una ventana de  (wsize x wsize)
 * Nota: El filtro no se aplica a los bordes
 * Nota 2: No puede usar la funcion de OpenCV cv::median_filter

 * @param in, input image. Type CV_8UC1
 * @param wsize, tamanyo filtro. (Numero impar  >=3).
 *
 * @return  imagen resultado
 */
/**
 * @brief  Applies the median filter to the input image using a window size (wsize x wsize).
 * Note: The filter is not applied to borders
 * Nota 2: Do not use the OpenCV funtion cv::median_filter
 * @param in, input image. Type CV_8UC1
 * @param wsize, filter size. (Odd number >=3).
 *
 * @return resulting image
 */
using namespace std;

cv::Mat median_filter(const cv::Mat &in, int wsize)
{


    cv:: Mat out(in.rows, in.cols, in.type());
    out=in.clone();
    int r= ((wsize-1)/2);
    std::vector<float> v;

    float aux1;


    for (int i = r; i < (in.rows-r); ++i)
    {
             float * ptrOut= out.ptr<float>(i,r);

        for (int j= r; j < (in.cols-r); ++j, ptrOut++)
        {

            for (int xx = (i-r); xx <= (i+r); ++xx)
            {

                for (int yy = (j-r); yy <= (j+r); ++yy)
                {

                    v.push_back(in.at<float>(xx,yy));

                }

            }



            for (int k = 0; k < v.size(); ++k)
            {
                for (int l = 1; l < v.size(); ++l)
                {
                    if(v[k]>v[l]){

                        aux1=v[k];
                        v[k]=v[l];
                        v[l]=aux1;

                    }
                }


            }





            //cv:: sort(v,v,cv::SORT_ASCENDING);



            out.at<float>(i,j)=v[((v.size()-1)/2)];

        }
    }



 return in;
} 
