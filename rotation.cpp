/*The name of the following program is "rotation" and is written in C++ Programming language.
The program is used to perform following tasks:
1. To accept the name of an image from the user as an input
2. To accept the measure of angle in degree from the user
3. To rotate the input image by the angle given by user
4. To display the original and rotated image
5. To save the rotated image

Input:
1. The name of an image with its proper extension in "imageName.extension" format.
2. The measure of angle in degree which can be integer or a float value.

Output:
1. Display the original and as well as rotated final image
2. To save the rotated image

Execution Steps:
1. Compile the code:
In terminal go to the folder in which this code is stored and type the following command:
g++ rotation.cpp -o rotation `pkg-config --cflags --libs opencv`

2.Run the compiled code:
After successfull compilation of the code, execute the following command to run the code:
./rotation  */

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
 
using namespace cv;
using namespace std;
 
/*Function to perform rotation on an image with the following 2 parameters:
1. Image in the form of its matrix data type.
2. Measure of angle by which rotation has to be done. Can be Integer as well as float value. So double is the datatype.

The function returns rotated image in the form of its matrix representation*/
Mat rotate(Mat src, double angle)
{
  Mat dst;
  Point2f pt(src.cols/2., src.rows/2.);    
  Mat r = getRotationMatrix2D(pt, angle, 1.0);
  warpAffine(src, dst, r, Size(src.cols, src.rows));
  return dst;
}
 
 //Main function
int main(){
  char inputImage[100];
  double rotationAngle;    

  //Accept image name as an input from user
  cout<<"Enter the name of the image along with its extension separed by a '.' from the image name. \n Eg. rangoli.jpg";
  cin>>inputImage;
  
  //Accept measure of angle in degree as an input from user
  cout<<"Enter the rotation angle (in degrees)";
  cin>>rotationAngle;

  Mat source = imread(inputImage);
  
  //Validate the input image name given by user
  if(source.empty()){
  cout<<"Specified image file does not exist! Please enter a valid image name in the specified format!";
  }else{
    Mat rotatedImage;
    
    //Call to the rotate() function 
    rotatedImage = rotate(source, rotationAngle);
 
    imshow("Original Image", source);
    imshow("Rotated Image", rotatedImage);
    waitKey(0);
  }
  return 0;
}