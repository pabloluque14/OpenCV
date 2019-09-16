
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>

#include <vector>
#include <string>

/*BLOQUE1*/


/**
 * @brief Carga una imagen y la devuelve tras aplicar un suavizado Gaussiano con la sigma indicada.

  @warning La imagen se carga siempre en monocromo, da igual si está almacenada en RGB o no.

@param[in] filename, camino del archivo en el sistema de ficheros.
@param[in] sigma, valor de sigma para el suavizado tanto para eje x como y.
@return true si la imagen se pudo cargar, false en otro caso.
*/
cv::Mat cargar_y_suavizar (const std::string& filename, float sigma);

/**
 * @brief Calcular la media y la desviación de los valores de un canal.

Dado una imagen CV_8UC1, calcular la media y la desviación de los valores almacenados.

@param[in] canal, imagen para calcular.
@param[out] media, el valor medio de los valores.
@param[out] desv, la desviación típica de los valores.
@pre img.type()==CV_8UC1
*/
void calcular_media_desviacion(const cv::Mat& img, float& media, float& desv);

/* BLOQUE 2 */

/**
 * @brief Realiza la umbralización de una imagen basada en el módulo del gradiente.
 * Dadas dos matrices CV_32FC1 que contienen el gradiente en X y el gradiente en Y, y un valor umbral,
 * calcula el módulo del gradiente y aplica dicho umbral al módulo,
 * asignando valor 1 a las posiciones de la matriz de salida que son mayores o iguales a dicho umbral,
 * y 0 en otro caso.

@param[in] gX, matrix gradiente en X
@param[in] gY, matrix gradiente en Y
@param[in] umbral, valor de umbral del módulo del gradiente
@param[out] segmentada, imagen binarizada de salida, creada fuera de la función
@pre gX.type()==CV_32FC1 && gY.type()==CV_32FC1
*/
void umbralizar_gradiente(const cv::Mat& gX, const cv::Mat& gY, float umbral, cv::Mat& segmentada);

/**
 * @brief Calcula un descriptor de imagen BOVW normalizado. Dado un vector que contiene el conjunto de identificadores de palabras visuales encontradas en una imagen, y el tamaño de diccionario usado, devuelve un descriptor BOVW normalizado (la suma de sus elementos es 1).
@param[in] wordsId, identificadores de palabras visuales
@param[in] dict_size, tamaño del diccionario usado
@return cv::Mat con una fila y tantas columnas como sean necesarias, de tipo CV_32FC1
*/
cv::Mat calcularBOVW(const std::vector<int> & wordsId, int dict_size);

/* BLOQUE 3 */

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
bool detectar_tablero(const cv::Mat& img, const cv::Size& tam, std::vector<cv::Point2f>& esquinas,
                      const cv::TermCriteria& termcrit = cv::TermCriteria(cv::TermCriteria::COUNT|cv::TermCriteria::EPS,20,0.03));



void calcular_media (const cv::Mat& img, float& r, float& g, float& b);

std::vector<float> calcular_histograma(const cv::Mat& img);

void calcular_gradiente(const cv::Mat& imgGray, cv::Mat& gX, cv::Mat& gY);
void vecino_mas_cercano(const std::vector<cv::Mat> & src, const std::vector<cv::Mat> & dst, std::vector<int> & match);
bool almacenar_calibracion(const std::string& filename,const cv::Mat& k,const cv::Mat& d,const cv::Mat& r,const cv::Mat& t);


