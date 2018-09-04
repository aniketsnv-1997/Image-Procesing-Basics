#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include <stdio.h>
#include <iostream>


using namespace std;
using namespace cv;

int main(int argc,const char** argv){
  Mat org_img=imread(argv[1],CV_LOAD_IMAGE_UNCHANGED);
  Mat gray_img,op_img, adaptive_img;

  cvtColor(org_img,gray_img,CV_RGB2GRAY);

  int th = threshold(gray_img,op_img,0,255, CV_THRESH_BINARY | CV_THRESH_OTSU);
  cout<<"\n"<<th;
  imshow("Orginal_image",org_img);

  imshow("Gray image",gray_img);

  imshow("OTSU image",op_img);
  imwrite("otsuimage.jpg", op_img);

	adaptiveThreshold(gray_img,adaptive_img,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY,7,11);
	
	imshow("Gaussian",adaptive_img);
	imwrite("gaussian_image.jpg", adaptive_img);
	
	waitKey(0);
	return 0;

}
