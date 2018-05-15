/*
Author: Adelson Dias (adelsondias@live.com)

To compile: g++ q5.cpp -o q5 `pkg-config --cflags --libs opencv`
To execute: 
*/

#include <iostream>
#include <opencv2/opencv.hpp>
#include <highgui.h>

using namespace cv;
using namespace std;


int main(int argc, char** argv){

    Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    Mat new_image = image.clone();

    if(!image.data){
        cout << "Image path error\n";
	return -1;
    }

    //histogram calculation
    int histogram[256] = { };
    for(int i = 0; i < image.rows; i++){
        for(int j = 0; j < image.cols; j++){
            histogram[(int)image.at<uchar>(i,j)]++;
        }
    }

    //probabilities calculation
    float prk[256];
    for(int i = 0; i < 256; i++){
        prk[i] = (float)histogram[i] / (image.rows * image.cols);
    }

    //comutative histogram
    int comhist[256];
    comhist[0] = histogram[0];
    for(int i = 1; i < 256; i++){
        comhist[i] = histogram[i] + comhist[i-1];
    }
    float alpha = 255.0/(image.rows * image.cols); 
    int sk[256];
    for(int i = 0; i < 256; i++){
        sk[i] = cvRound((double)comhist[i] * alpha);
    }

    //writing new image
    for(int y = 0; y < image.rows; y++){
        for(int x = 0; x < image.cols; x++){       
            new_image.at<uchar>(y,x) = saturate_cast<uchar>(sk[image.at<uchar>(y,x)]);
        }
    }

    namedWindow("Image");
    imshow("Image", image);

    namedWindow("Equilized Image");
    imshow("Equilized Image",new_image);

    waitKey();
    return 0;
}
