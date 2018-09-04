/*The name of the following program is "histogram" and is written in C++ programming Language.
The following code is used to perform following tasks: 
1. OTSU Thresholding Algorithm and OTSU threshold value
2. Save the OTSU thresholded image
3. Display the histogram for an image which is taken as an input from the user
4. The code will ask for a threshold value from user and will perform binary threshold with the help of that threshold value.
5. To store the data required to plot histogram in a .txt file

Input:  
  1. The input will be an image from the user in jpg or png format
  2. An integer Threshold value for binary thresholding ranging between 0 to 255

Output: 
  1. Otsu Thresholded Image will be displayed to the user.
  2. Gray Scale image will be displayed to the user.
  3. Histogram for the gray scale image will be displayed to the user.
  4. Binary thresholded image will be displayed.
  5. A histogramOutput.txt file will be generated in the pwd of user which would contain the data required to plot the histogram

Execution Steps:
1. Compile the code:
In terminal go to the folder in which this code is stored and type the following command:
g++ histogram.cpp -o histogram `pkg-config --cflags --libs opencv`

2.Run the compiled code:
After successfull compilation of the code, execute the following command to run the code:
./histogram  */

#include<iostream>
#include<fstream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(){
  double th;
  Mat thresholdOtsu;
  char input[100];
  
  //Accept the input image name from user 
  cout<<"Enter the full image name:";
  cin>>input;
 
 
  Mat image = imread(input, CV_LOAD_IMAGE_GRAYSCALE);
  //Validate the input image name given by user
  if(image.empty()){
    cout<<"Specified image file does not exist";
  }else{
    int t=1;
    
    // allcoate memory for no of pixels for each intensity value
    int histogram[256];

    // initialize all intensity values to 0
    for(int i = 0; i < 256; i++){
      histogram[i] = 0;
    }

    // calculate the no of pixels for each intensity values
    for(int y = 0; y < image.rows; y++){
      for(int x = 0; x < image.cols; x++){
        histogram[(int)image.at<uchar>(y,x)]++;
      }
    }
    
    //To redirect the output of histogram values to histogramOutput.txt file
    freopen( "histogramOutput.txt", "w", stdout );
    int total = 0;
    for(int i = 0; i < 256; i++){
      cout<<i<<"-"<<histogram[i]<<"  ";
      total += histogram[i];
    }
    cout<<"\n"<<total;

    //draw the histogram
    int hist_w = 512; 
    int hist_h = 400;
    int bin_w = cvRound((double) hist_w/256);

    Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255, 255, 255));

    //find the maximum intensity element from histogram
    int max = histogram[0];
    for(int i = 1; i < 256; i++){
      if(max < histogram[i]){
        max = histogram[i];
      }
    }

    //normalize the histogram between 0 and histImage.rows
    for(int i = 0; i < 255; i++){
      histogram[i] = ((double)histogram[i]/max)*histImage.rows;
    }


    //Draw the intensity line for histogram
    for(int i = 0; i < 255; i++){
      line(histImage, Point(bin_w*(i), hist_h), Point(bin_w*(i), hist_h - histogram[i]), Scalar(0,0,0), 1, 8, 0);
    }

    //Display histogram
    namedWindow("Intensity Histogram", CV_WINDOW_AUTOSIZE);
    imshow("Intensity Histogram", histImage);

    //Display the grayscale image
    namedWindow("Image", CV_WINDOW_AUTOSIZE);
    imshow("Image", image);
    
    //Display OTSU thresholded image
    th = threshold(image, thresholdOtsu,0,255, CV_THRESH_BINARY | CV_THRESH_OTSU);
    
    //Redirect the output to console again
    freopen("CON", "w", stdout);
    
    cout<<"Otsu Threshold value is: "<<th;
    imshow("OTSU Thresholded Image", thresholdOtsu);
    imwrite("OTSU thresholded image.jpg", thresholdOtsu);
    	
    waitKey(25);
    
    //Accept threshold value from user
    Mat thresholdBinary;
    cout<<"\nEnter 0 to exit"; 
    cout<<"\nEnter Threshold:";
    cin>>t;
	
    //Code to accept input(threshold value) from user and display thresholded binary image
    do{
      threshold(image, thresholdBinary, t, 255, CV_THRESH_BINARY);
      imshow("Binary Thresholded Image", thresholdBinary);
      waitKey(500);
      cout<<"\nEnter 0 to exit"; 
      cout<<"\nEnter Threshold:";
      cin>>t;
    }while(t!=0);

  }
  return 0;
}

