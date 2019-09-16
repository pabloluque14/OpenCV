/* 
   (c) Fundamentos de Sistemas Inteligenties en Vision
   University of Cordoba, Spain  
*/

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
//#include <unistd.h>
#include <ctype.h>
#include <cmath>

#include <tclap/CmdLine.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>

using namespace std;
using namespace cv;

/*
  Use CMake to compile
*/

int main (int argc, char * const argv[])
{

  TCLAP::CmdLine cmd("Video segmentation", ' ', "0.1");

  TCLAP::ValueArg<std::string> filename("v", "videoname", "Video path", true, "video.avi", "string");
  cmd.add(filename);
  TCLAP::ValueArg<std::string> outname("o", "outfilename", "Output video path", true, "out.avi", "string");
  cmd.add(outname);
  
  TCLAP::ValueArg<int> thres("t", "threshold", "Threshold value", false, 13, "int");
  cmd.add(thres);

  TCLAP::ValueArg<int> radius("s", "radius", "Radius value", false, 1, "int");
  cmd.add(radius);
  
  // Parse input arguments
  cmd.parse(argc, argv);

  const char * filein = 0;
  const char * fileout = 0;

  filein = filename.getValue().c_str();
  fileout = outname.getValue().c_str();
  

  std::cout << "Input stream:" << filein << endl;
  std::cout << "Output:" << fileout << endl;

  VideoCapture cap;
  VideoWriter outvideo;

  cv:: Mat frame, antFrame, diff,semiMask,finalMask, maskOpening, maskClosing,outFrame, mask, kernel;
  int cont_frames=0, r = radius.getValue();
  cap.open(filein);
  bool wasOk= true;
  std::vector<cv:: Mat> splitMask;


  int threshold=thres.getValue();

   if (!cap.isOpened())
  {
    cerr << "Error: the input stream is not opened.\n";
    abort();
  } 

cv::namedWindow("input");                 

 

  
  wasOk=cap.read(frame);

  if (!wasOk){
  
    cerr << "Error: could not read any image from stream.\n";
    abort();
  }
  
  
outvideo.open(fileout,cv::VideoWriter::fourcc('M','J','P','G'),cap.get(CAP_PROP_FPS),frame.size());
mask=cv::Mat::zeros(frame.rows,frame.cols,CV_8UC1); 

while(wasOk){
  
    
    cv::imshow ("video orginal",frame);
    cv:: waitKey(20); // Le ponemos > 0 para que se detenga en cada frame más tiempo

    if(cont_frames >= 1){

        cv::absdiff(frame,antFrame,diff);

        mask=diff > threshold;

        cv::split(mask,splitMask);

        bitwise_or(splitMask[0], splitMask[1], semiMask);
        bitwise_or(semiMask,splitMask[2],finalMask);

      if (r > 0){
        
        kernel=getStructuringElement(cv::MORPH_CROSS, cv:: Size(r,r));
        cv::morphologyEx(finalMask,maskOpening,cv::MORPH_OPEN,kernel);
        cv::morphologyEx(maskOpening,maskClosing,cv::MORPH_CLOSE,kernel);

        std::vector<cv:: Mat> v={maskClosing,maskClosing,maskClosing};

        cv::merge(v,maskClosing);

      }else{



        

       
      }

      outFrame= frame & maskClosing;
      outvideo<<outFrame;
      cv::imshow ("outputvideo", outFrame);
      cv::imshow ("Mask", maskClosing);



    }

    cont_frames++;
    frame.copyTo(antFrame);
    wasOk=cap.read(frame);
   
  
}

outvideo.release();

VideoCapture openvideo(fileout);

bool isOk= openvideo.read(frame);

if (!isOk){
  
    cerr << "Error: could not read any image from stream.\n";
    abort();
  }
cv::namedWindow("saved vifdeo");

while(isOk){

if (!frame.empty()){
  imshow("saved video",frame);
  waitKey(20);
}
openvideo.read(frame);

}
  
  return 0;
}
