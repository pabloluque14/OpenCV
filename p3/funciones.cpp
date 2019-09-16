#include "funciones.hpp"

/**
 * @brief Detecta un tablero y devuelve sus esquinas refinadas a nivel de subpixel.
Dada un imagen busca un tablero de tamaño FxC y si lo encuentra, extrae sus esquinas y las refina.

@param[in] img, es la imagen donde buscar.
@param[in] tam, es el tamaño del tablero en Cols x Filas cuadrados.
@param[out] esquinas, vector con las (Cols-1)*(Filas-1) esquinas refinadas.
@param[in] termcrit, criterio de terminación para el algoritmo de refinado de esquinas.
@return true si encuentra el tablero, falso en caso contrario.
@pre img.type()=CV_8UC1
*/
bool detectar_tablero(const cv::Mat& img, const cv::Size& tam, std::vector<cv::Point2f>& esquinas,const cv::TermCriteria& termcrit  )
{

	bool detectado=false;

//Pon tu código aquí.-------------------
	
	
	cv:: Mat imgGray;

	cv::cvtColor(img,imgGray,CV_RGB2GRAY);

	detectado=findChessboardCorners(img,tam,esquinas);

//-------Para refinar los corners--------------------------------------------------
	if(detectado == true){

			cornerSubPix(imgGray,esquinas,tam,cv::Size(-1,-1),termcrit);

	}
//--------------------------------------------------------------------

// -------------------------------------------------
    return detectado;

}

