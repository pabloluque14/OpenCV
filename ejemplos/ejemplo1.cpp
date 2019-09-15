#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


int main() {



cv:: Mat img;

//std:: cout << " Filas de la img: "<<img.rows<<"\n Columnas de la img: "<< img.cols << "\n Tipo de la img: "<< img.type() << "\n Canales de la img: "<< img.channels()<<std::endl;


img = cv:: imread("puppy.bmp");

if (img.empty()){

	std::cout << "No se lee la imagen"<<std:: endl;
}

std:: cout << " Filas de la img: "<<img.rows<<"\n Columnas de la img: "<< img.cols << "\n Tipo de la img: "<< img.type() << "\n Canales de la img: "<< img.channels()<<std::endl;


cv:: namedWindow("Imagen original");
cv:: imshow("Imagen original",img);
//cv:: waitKey(0);



// Este codigo pasa la imagen de entrada a gris
cv:: Mat imgGray(img.rows,img.cols,CV_8UC1);
cv:: Vec3b pixel; // es un vector de tres elementos de tipo uchar de opencv.

for (int i=0; i < img.rows; i++){


	for(int j=0; j < img.cols ; j++){

		
		pixel= img.at<cv:: Vec3b>(i,j);

		uchar B = pixel[0];
		uchar G = pixel[1];
		uchar R = pixel[2];

		imgGray.at<uchar>(i,j)= (B+G+R) / 3;

		//std:: cout << (int)imgGray.at<uchar>(i,j) << std:: endl; // PARA VER VALORES DEL PIXEL!!!


	}
}

cv:: namedWindow("Imagen gris");
cv:: imshow("Imagen gris",imgGray);


std:: cout << " Filas de la img: "<<imgGray.rows<<"\n Columnas de la img: "<< imgGray.cols << "\n Tipo de la img: "<< imgGray.type() << "\n Canales de la img: "<< imgGray.channels()<<std::endl;


cv:: Mat imgGray2(img.rows,img.cols,CV_8UC1);


//Hace lo mismo pero de otra forma

for (int i=0; i < img.rows; i++){

	cv:: Vec3b * imgPtr = img.ptr<cv:: Vec3b>(i);
	uchar * imgGrayPtr = imgGray2.ptr<uchar>(i);

	for(int j=0; j < img.cols ; j++){	

		uchar B = imgPtr[j][0];
		uchar G = imgPtr[j][1];
		uchar R = imgPtr[j][2];

		imgGrayPtr[j]= (B+G+R) / 3;

		//std:: cout << (int)imgGray.at<uchar>(i,j) << std:: endl; // PARA VER VALORES DEL PIXEL!!!

	}
}




cv:: namedWindow("Imagen gris2");
cv:: imshow("Imagen gris2",imgGray2);
cv:: waitKey(0); // en waitkey la opcion 0 es esperar a pulsar cualquier tecla, si pones cualquier número son los milisegundos a esperar para cerrar la ventana

return 0;

}