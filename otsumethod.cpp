/*The name of the following program is "rotation" and is written in C++ Programming language.
The program is used to perform following tasks:
1. Accept an image as an input from user
2. Validate the input from user
3. To display the histogram which would be used in determining the OTSU threshold
4. To display the OTSU thresholded image and the thresholding value used by it
5. To save the OTSU thresholded image

Input:
1. The name of an image with its proper extension in "imageName.extension" format.

Output:
1. An OTSU thresholded image
2. OTSU threshold value

Execution Steps:
1. Compile the code:
In terminal go to the folder in which this code is stored and type the following command:
g++ OTSU1.cpp -o otsu1 `pkg-config --cflags --libs opencv`

2.Run the compiled code:
After successfull compilation of the code, execute the following command to run the code:
./otsu1  */

#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <stdio.h>
#include <iostream>

//signature of the OTSU method
int thresholdOTSU(cv::Mat);

using namespace std;
using namespace cv;

int main(){
  char inputImage[50]; 		//declare the variable to store the user entered image name
  cout<<"Enter the name of the image along with its extension separed by a '.' from the image name. Eg. rangoli.jpg\n";
  cin>>inputImage;  		//accept the image name from user

  cv::Mat grayImage = imread(inputImage, CV_LOAD_IMAGE_GRAYSCALE);
  Mat otsuThresholdedImage;
  
  //Validate the input image name given by user
  if(grayImage.empty()){
    cout<<"Specified image file does not exist! Please enter a valid image name in the specified format!";
  }else{
    cout<<"\n"<<"The hard coded OTSU threshold value is: "<<thresholdOTSU(grayImage)<<"\n";
    int th = threshold(grayImage,otsuThresholdedImage,0,255, CV_THRESH_BINARY | CV_THRESH_OTSU);
    cout<<"\n"<<"The builtin OTSU threshold value is: "<<th<<"\n";
  }  
  return 0;
}
  

//thresholdOTSU()
int thresholdOTSU(cv::Mat grayImage){

  Ptr<CLAHE> clahe = createCLAHE();
  clahe->setClipLimit(1);

  cv::Mat sourceImage; //= grayImage;
  clahe->apply(grayImage, sourceImage); 

  //variable initialization
  int totalPixels=0, i, j, q1=0, q2=0, sum=0, sumA=0, otsuThreshold=0, value, histogram[256], maximumIntensity=256;
  double mean1=0.0, mean2=0.0, variance1=0.0, variance2=0.0, variableMaximum=0.0, betweenClassVariance=0.0, withinClassVariance=0.0, varianceOfImage=0.0; 
  
  for(i=0; i<maximumIntensity; i++){
      histogram[i] = 0;
    }

  //to count the pixes having "i" as an intensity value and storing that count at ith position in histogram
  for(i=0; i<sourceImage.rows; i++){
    for(j=0; j<sourceImage.cols; j++){
      histogram[(int)sourceImage.at<uchar>(i,j)]++;
    }
  }

  /*to print the histogram data in the form of
  "intensityValue-No. of pixels of that intensityValue" and 
  count total no of pixels in the image*/
  for(i=0; i<maximumIntensity; i++){
    cout<<i<<"-"<<histogram[i]<<"  ";
    sum += i*histogram[i];
    totalPixels +=  histogram[i];      //count total number of pixels in the image
  }
  cout<<"\n"<<totalPixels<<"\n";

  /*to get the following parameters for each of the
  intensity value from 0 to 255
  Note:0 to "i"th intensity level -> Class 1
  "i+1"th to 255th intensity level -> Class 2 "*/
  for(i=0; i<maximumIntensity; i++){
    q1 += histogram[i];    //q1 = sum of pixels for class 1
    if(q1 == 0){
      continue;
    }
      
    q2 = totalPixels - q1;     //q2 = sum of pixels for class 2
    if(q2 == 0){
      break;
    }
    sumA += i*histogram[i];   //calculate i*pdf(i) for class 1
      
    mean1 = (sumA)/q1;    //weighted mean for class 1
    mean2 = (sum - sumA)/q2;  //weighted mean for class 2
    
    variance1 = ((i - mean1)*(i - mean1))*(histogram[i]/q1);  //variance for class 1
    variance2 = ((i - mean2)*(i - mean2))*(histogram[i]/q2);  //variance for class 2

    withinClassVariance = (double)(q1*variance1 + q2*variance2);  //intraclass variance
    betweenClassVariance = (double)q1*(double)q2*(mean1 - mean2)*(mean1 - mean2);  //interclass variance

    varianceOfImage = withinClassVariance + betweenClassVariance;  //variance of the image

    /*getting the threshold value for each intensity value by maximising the interclass variance
    for each intensity*/
    if(betweenClassVariance > variableMaximum){
      otsuThreshold = i;
      variableMaximum = betweenClassVariance;
    }
  }
  return otsuThreshold;   //return the threshold value to the caller i.e. main()
}
    