
#ifndef FUNCIONES_P5
#define FUNCIONES_P5

#include <string>
#include <opencv2/core.hpp>
#include <opencv2/ml.hpp>


cv::Mat extractSIFTDescriptors(const cv::Mat& img, const int ndesc);
cv::Mat extractSURFDescriptors(const cv::Mat& img, const int thresh);
void entrenar_diccionario(const cv:: Mat indexes, cv:: Mat keyws);
void entrenar_calsificadorKN(const int k, const cv:: Mat train_bovw, cv:: Mat & train_labels);
cv::Mat compute_bovw (const cv::Ptr<cv::ml::KNearest>& dict, const int dict_size, cv::Mat& img_descs);
cv::Mat compute_bovw2(const std::vector<int> & words, int dict_size);
void vecino_mas_cercano(const std::vector<cv::Mat> & src, const std::vector<cv::Mat> & dst, std::vector<int> & match);
cv::Mat compute_confusion_matrix(int n_categories, const cv::Mat& true_labels, const cv::Mat& predicted_labels);
void cargarClasificador(const string classFile);
void cargarDiccionario(const string dictFile);

/*
EJERCICIO FRECUENTE DE EXAMEN
-Enunciado: Ejecutar el algoritmo kmeans++ 3 veces con k clusters y devolver la mejor iteración de las tres.

Esttodo lo hace una función que solo tienes que poner los parámetros.

*/
void ejecutar_kmeans(cv:: TermCriteria termcrit, std::vector<cv::Point2f> points, int k);
#endif //__COMMON_CODE_HPP__
