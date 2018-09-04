#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <stdio.h>

using namespace std;
using namespace cv;

int main(int argc, const char** argv)
{
	Mat inputImage = imread(argv[1], CV_LOAD_IMAGE_UNCHANGED);
	Mat grayImage;
	Mat thresholdBinary;
	Mat thresholdInverseBinary;
	Mat thresholdTruncate;

	//to convert BGR image to grayscale image
	cvtColor(inputImage, grayImage, CV_BGR2GRAY);
	imshow("Original Image", inputImage);
	imshow("Grayscale Image", grayImage);
	imwrite("Gray Rangoli.jpg", grayImage);

	//to convert grayscale image to threshold(binary) image
	threshold(grayImage, thresholdBinary, 100, 255, CV_THRESH_BINARY);
	imshow("Binary Thresholded Image", thresholdBinary);
	imwrite("Threshold Binary.jpg", thresholdBinary);
	
	//to convert grayscale image to threshold(truncate) image
	threshold(grayImage, thresholdTruncate, 100, 100, CV_THRESH_TRUNC);
	imshow("Truncate Thresholded Image", thresholdTruncate);
	imwrite("Thresholded Truncate.jpg", thresholdTruncate);

	//to convert grayscale image to threshold(truncate) image
	threshold(grayImage, thresholdInverseBinary, 100, 255, CV_THRESH_BINARY_INV);
	imshow("Inverse Binary Thresholded Image", thresholdInverseBinary);
	imwrite("Thresholded Inverse Binary.jpg", thresholdInverseBinary);

	waitKey(0);

	return 0;
}