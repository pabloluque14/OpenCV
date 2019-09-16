#include <opencv2/videoio.hpp>
#include <vector>
#include <iostream>
#include <opencv2/core/core.hpp> 
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "funciones.hpp"

using namespace std;

const cv::String keys =
    "{@rows          |<none>| number of rows       }"
    "{@cols          |<none>| number of cols       }"
    "{@size          |<none>| size                 }"
    "{@intrinsics    |<none>| intrinsics .yml file }"
    "{@inputVideo    |<none>| imput video          }"
    ;

int main(int argc,char **argv){



	cv::CommandLineParser parser(argc, argv, keys);

	int rows = parser.get<int>(0);  
	int cols = parser.get<int>(1);
	int size = parser.get<int>(2);
	std::string intrinsics = parser.get<std::string>(3);
	std::string inputVideo = parser.get<std::string>(4);


	cv:: Mat frame;
	vector<cv::Point2f> corners;

	cv:: Mat cameraMatrix, distortionCoefficient;

	cv:: Mat rvec, tvec;


	vector<cv:: Point3f> ThreeDpoints;

	for (int i = 0; i < cols; ++i){ // aqui van cols
		for (int j = 0; j < rows; ++j){ // aqui van rows
			ThreeDpoints.push_back(cv:: Point3f(j*size, i*size, 0)); // aqui va j e i

		}
	}


	cv::VideoCapture video(inputVideo); // Se abre el video y se le pasa el nombre

	while(video.read(frame)){ 


		bool control =detectar_tablero(frame, cv:: Size(rows,cols),corners ,cv:: TermCriteria());

		if (control== true){

		//------------Leer cameraMatrix y distortionCoefficient------------ 


			cv:: FileStorage fs(intrinsics, cv:: FileStorage::READ);


				fs["camera_matrix"]>>cameraMatrix;
				fs["distortion_coefficients"] >> distortionCoefficient;


		//------------------------------------------------------------------

		//------------Vector de Traslacion y Rotacion-----------------------  

		cv::solvePnP(ThreeDpoints,corners,cameraMatrix,distortionCoefficient,rvec,tvec);



		//-----------------------------------------------------------------            


		//Van a ser los puntos en 3D que queremos pasar al plano de la imagen
		std::vector<cv::Point3f> pointsProjected;
		


		pointsProjected.push_back(cv::Point3f((rows/2)*size,(cols/2)*size,0));
      	pointsProjected.push_back(cv::Point3f(((rows/2)+1)*size,(cols/2)*size,0));
      	pointsProjected.push_back(cv::Point3f((rows/2)*size,((cols/2)+1)*size,0));
      	pointsProjected.push_back(cv::Point3f((rows/2)*size,(cols/2)*size,-size));

      	/*
		pointsProjected.push_back(cv::Point3f(2*size,2*size,0)); //defPoints[0]->> centro 
		pointsProjected.push_back(cv::Point3f(3*size,2*size,0));//defPoints[1]->> punto para eje x
		pointsProjected.push_back(cv::Point3f(2*size,3*size,0));//defPoints[2]->> punto para eje y 
		pointsProjected.push_back(cv::Point3f(2*size,2*size,-size));//defPoints[3]->> punto para eje z */

		std::vector<cv::Point2f> defPoints;//Vector donde se guardarán los puntos en 2D definitivos que queremos calcular 

		/*La función calcula las proyecciones de puntos 3D al plano de la imagen dados los parámetros intrínsecos y extrínsecos de la cámara.*/ 
		cv::projectPoints(pointsProjected,rvec,tvec,cameraMatrix,distortionCoefficient,defPoints);




		//Imprimimos las lineas
		cv::Scalar Red(255,0,0);
		cv::line(frame,defPoints[0],defPoints[3], Red,5); //X

		cv::Scalar Green(0,255,0);
		cv::line(frame,defPoints[0],defPoints[2], Green,5); //Y

		cv::Scalar Blue(0,0,255);
		cv::line(frame,defPoints[0],defPoints[1], Blue,5); //Z





		}   
		cv::imshow("Video", frame);
		if (cv::waitKey(5) >= 0)
		break;


	}




  }
