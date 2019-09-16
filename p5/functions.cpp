
int main(){

        
//--------------De aqui se saca los centros de los clusters----------------------------------------------------------------------------------------------------

/*
train_descs-> descriptores
keywords-> el numero de key words -> que será el numero de clusters 
dict_runs-> numero de intentos
*/


cv::Mat keyws;
cv::Mat labels;

double compactness = cv::kmeans
(train_descs, keywords.getValue(), labels,cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 10, 1.0),dict_runs.getValue(),
                                        cv::KmeansFlags::KMEANS_PP_CENTERS, //cv::KMEANS_RANDOM_CENTERS,
                                        keyws);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------





void sacar_centros(const cv:: Mat & desc, int keywords, cv:: TermCriteria :: termscrit, cv:: Mat & labels, cv:: Mat & keyws, int trials, cv::KmeansFlags:: flag){



cv:: kmeans(desc, keywords, labels, termscrit, trials, flag, keyws); 

}




//----------Crear diccionario y Entrenarlo--------------------------------        
		cv::Mat indexes(keyws.rows, 1, CV_32S);

		for (int i = 0; i < keyws.rows; ++i)
			indexes.at<int>(i) = i;

        cv::Ptr<cv::ml::KNearest> dict = cv::ml::KNearest::create();
        dict->setAlgorithmType(cv::ml::KNearest::BRUTE_FORCE);
        dict->setIsClassifier(true);
        dict->train(keyws, cv::ml::ROW_SAMPLE, indexes);
        
//------------------------------------------------------------------------








//----------------------Se crea el clasificador -----------------------------------
        
        cv::Ptr<cv::ml::StatModel> classifier;
        
        if(classifierType.getValue()=="knn"){
          
            cv::Ptr<cv::ml::KNearest> knnClassifier = cv::ml::KNearest::create();
            knnClassifier->setAlgorithmType(cv::ml::KNearest::BRUTE_FORCE);
            knnClassifier->setDefaultK(kneigh.getValue());
            knnClassifier->setIsClassifier(true);
            
            classifier = knnClassifier;
        

        }else if(classifierType.getValue()=="svm"){
                
			cv::Ptr<cv::ml::SVM> svmClassifier = cv::ml::SVM::create();
			svmClassifier->setType(cv::ml::SVM::C_SVC);
			svmClassifier->setKernel(nucleo);
			svmClassifier->setC(margin.getValue());
			svmClassifier->setTermCriteria(cv::TermCriteria(cv::TermCriteria::MAX_ITER, 100, 1e-6));
			
			classifier = svmClassifier;
		}
            
//----------------------------------------------------------------------------------------------------------      



//-----------------------------------------Entrenar clasificador--------------------------------------------        
        cv::Mat train_labels(train_labels_v);
        classifier->train(train_bovw, cv::ml::ROW_SAMPLE, train_labels);
//----------------------------------------------------------------------------------------------------------




//--------Predecir clasificador------------------------------        
        cv::Mat predicted_labels;
        classifier->predict(test_bovw, predicted_labels);
//-----------------------------------------------------------






//---------------------test---------------------------------------------------------------------------

        cv::Mat bovw = compute_bovw(dict,100, descriptors);


		classifier->predict(bovw, predicted_labels);

		std::cout<<"Image categorie: "<<categories[predicted_labels.at<float>(0,0)] << std::endl;
		
//----------------------------------------------------------------------------------------------------














cv::Mat bovw = compute_bovw(dict, keyws.rows, descriptors);




cv::Mat compute_bovw (const cv::Ptr<cv::ml::KNearest>& dict, const int dict_size, cv::Mat& img_descs, bool normalize)
{

    cv::Mat bovw = cv::Mat::zeros(1, dict_size, CV_32F);
    cv::Mat vwords;

    CV_Assert(img_descs.type()==CV_32F);
    
    dict->findNearest(img_descs, 1, vwords);
    
    CV_Assert(vwords.depth()==CV_32F);
    
    for (int i=0;i<img_descs.rows;++i)
        bovw.at<float>(vwords.at<float>(i))++;
    
    if (normalize)
        bovw /= float(img_descs.rows);
    
    return bovw;
}



void vecino_mas_cercano(const std::vector<cv::Mat> & src, const std::vector<cv::Mat> & dst, std::vector<int> & match)
{
		//Escribe aquí tu código.
		//Write here your code.

		//--- crear clasificador
		cv::Ptr<cv::ml::StatModel> classifier;
		cv::Ptr<cv::ml::KNearest> knnClassifier = cv::ml::KNearest::create();
		knnClassifier->setAlgorithmType(cv::ml::KNearest::BRUTE_FORCE);
		knnClassifier->setDefaultK(k);
		knnClassifier->setIsClassifier(true);

		classifier = knnClassifier;



		cv::Mat train_labels(match);
		classifier->train(src, cv::ml::ROW_SAMPLE, train_labels);

		classifier->findNearest(src,1,dst);


}







cv:: Ptr<cv::ml::KNearest> dict= cv::ml::KNearest::create();
dict->setAlgorithmType(cv::ml::KNearest::BRUTE_FORCE ); 	 	
dict->setIsClassifier(true);

cv:: Mat indexes(keyws.rows,1, cv:: CV_32S);

for (int i = 0; i < keyws.rows; ++i)
	indexes.at<int>(i)=i;


dict->train(keyws,cv::ml::ROW_SAMPLE,indexes);

//--------------------------------------------------------------------
cv:: Ptr<cv::ml::KNearest> classifier= cv::ml::KNearest::create();
classifier->setAlgorithmType(cv::ml::KNearest::BRUTE_FORCE );
classifier-> setDefaultK(k);	 	
classifier->setIsClassifier(true);


classifier->train(bovw, cv::ml::ROW_SAMPLE ,labels);

//------------------------------------------------------------------


classifier->predict(bovw, predicted_labels);

categories[predicted_labels.at<float>(0,0)];














cv::Mat compute_bovw (const cv::Ptr<cv::ml::KNearest>& dict, const int dict_size, cv::Mat& img_descs, bool normalize)
{

    cv::Mat bovw = cv::Mat::zeros(1, dict_size, CV_32F);
    cv::Mat vwords;

    CV_Assert(img_descs.type()==CV_32F);
    
    dict->findNearest(img_descs, 1, vwords);
    
    CV_Assert(vwords.depth()==CV_32F);
    
    for (int i=0;i<img_descs.rows;++i)
        bovw.at<float>(vwords.at<float>(i))++;
    
    if (normalize)
        bovw /= float(img_descs.rows);
    
    return bovw;
}
















}