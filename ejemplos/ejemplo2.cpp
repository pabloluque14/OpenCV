#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


/*
EJERCICIO DE EXAMEN 

SE TRATA DE BUSCAR EL PIXEL MÁS LUMINOSO DE UNA IMAGEN Y DEVOLVER SU POSISION X E Y,
Y ADEMÁS SUS VALORES R,G Y B. (aunque yo lo que he hecho es devolver el valor del pixel que es casi
lo mismo, el ejercicio está hecho de tres formas diferentes)

LA LUMINOSIDAD DE UN PIXEL SE CALCULA CON R+G+B/3.


*/


int main() {

cv:: Mat img;

img = cv:: imread("puppy.bmp");

if (img.empty()){

	std::cout << "No se lee la imagen"<<std:: endl;
}

cv:: namedWindow("Imagen original");
cv:: imshow("Imagen original",img);


uchar max=0;

int x = 0;
int y = 0;

cv:: Vec3b pixel;

for (int i=0; i < img.rows; i++){


	for(int j=0; j < img.cols ; j++){

		
		pixel= img.at<cv:: Vec3b>(i,j);

		uchar B = pixel[0];
		uchar G = pixel[1];
		uchar R = pixel[2];

		uchar current_pixel= (B+G+R) / 3;

		if (current_pixel > max){

			max = current_pixel;
			x=i;
			y=j;
		}


	}
}


std:: cout << "max: "<< (int)max <<"\nx :"<< x<< "\ny: "<< y << std::endl;


max=0;
x = 0;
y = 0;

for (int i=0; i < img.rows; i++){

	cv:: Vec3b * imgPtr = img.ptr<cv:: Vec3b>(i);

	for(int j=0; j < img.cols ; j++){

		uchar B = imgPtr[j][0];
		uchar G = imgPtr[j][1];
		uchar R = imgPtr[j][2];

		uchar current_pixel= (B+G+R) / 3;

		if (current_pixel > max){

			max = current_pixel;
			x=i;
			y=j;
		}


	}
}


std:: cout << "max: "<< (int)max <<"\nx :"<< x<< "\ny: "<< y << std::endl;


//Como lo hice en el examen

uchar r = 0;
uchar g = 0;
uchar b = 0;
x = 0;
y = 0;

//Escribe tu código desde aquí.

uchar max1=(r+g+b);
max=0;

uchar r1;
uchar g1;
uchar b1;


for (int i = 0; i < img.rows; ++i)
{
    const uchar * ptrIn=img.ptr<uchar>(i);

    for (int j = 0; j < img.cols; ++j, ptrIn++)
        {
            r=ptrIn[0];
            g=ptrIn[1];
            b=ptrIn[2];

            max= ((r+g+b)/3);


            if(max > max1){

                max1=max;
            }


        }

}



for (int l = 0; l < img.rows; ++l)
{
    const uchar * ptrIn1=img.ptr<uchar>(l);

    for (int k = 0; k < img.cols; ++k, ptrIn1++)
        {
            r=ptrIn1[0];
            g=ptrIn1[1];
            b=ptrIn1[2];

            max= ((r+g+b)/3);

            if(max==max1){
                x=l;
                y=k;

                r1=r;
                g1=g;
                b1=b;

            }


        }

}


std:: cout << "max: "<< (int)max1 <<"\nx :"<< x<< "\ny: "<< y << std::endl;


 
return 0;

}