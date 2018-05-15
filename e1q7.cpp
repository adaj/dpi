/*
Author: Adelson Dias (adelsondias@live.com)

To compile: g++ q7.cpp -o q7 `pkg-config --cflags --libs opencv`
To execute: ./q7 images/.jpg
*/

#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <highgui.h>

using namespace cv;
using namespace std;


void highboost_filter(Mat image, Mat highboost_img, double k){
    double kernel[3][3] = {
                          {1/9.0,1/9.0,1/9.0},
                          {1/9.0,1/9.0,1/9.0},
                          {1/9.0,1/9.0,1/9.0}
                          }; 

    Mat lowpass_img = image.clone();
    for (int i = 1; i < image.rows-1; i++){
	for (int j = 1; j < image.cols-1; j++){

            lowpass_img.at<uchar>(i,j) = (kernel[0][0] * image.at<uchar>(i-1,j-1) + 
                                            kernel[0][1] * image.at<uchar>(i-1,j) +
                                            kernel[0][2] * image.at<uchar>(i-1,j+1) +
                                            kernel[1][0] * image.at<uchar>(i,j-1) +
                                            kernel[1][1] * image.at<uchar>(i,j) +
                                            kernel[1][2] * image.at<uchar>(i,j+1) +
                                            kernel[2][0] * image.at<uchar>(i+1,j-1) +
                                            kernel[2][1] * image.at<uchar>(i+1,j) +
                                            kernel[2][2] * image.at<uchar>(i+1,j+1)
                                            ); 
		}
	}  
    highboost_img = (k*image) - lowpass_img;
}


int main(int argc, char** argv){
    
    Mat image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
    if(!image.data){
    cout << "Image error\n";
    }

    Mat highboost_img = image.clone();

    highboost_filter(image, highboost_img, 2.0);

    namedWindow("Original",WINDOW_NORMAL);
    imshow("Original", image);
    namedWindow("Result",WINDOW_NORMAL);
    imshow("Result", highboost_img);

    waitKey();
    return 0;

}



