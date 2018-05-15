/*
Author: Adelson Dias (adelsondias@live.com)

To compile: g++ q6.cpp -o q6 `pkg-config --cflags --libs opencv`
To execute: ./q6 images/.jpg
*/

#include <iostream>
#include <opencv2/opencv.hpp>
#include <highgui.h>

using namespace cv;
using namespace std;


void contraharmonic_filter(Mat image, Mat mediaImage, int fil_size, float p){

    int filter_window[fil_size*fil_size];
    int e = fil_size / 2;
    int k;
    for(int i = e ; i<=image.rows-e ; i++){
        for(int j = e ; j<image.cols-e ; j++){
            k = 0;
            for(int i_fil = 0; i_fil<fil_size ; i_fil++){
                for(int j_fil = 0 ; j_fil<fil_size ;j_fil++){
                    filter_window[k] = image.at<uchar>(i+i_fil-e, j+j_fil-e);
                    k++;
                }
            }
            double sum = 0;
	    double contraharmonic_sum = 0;
            for(int w = 0 ; w<fil_size*fil_size; w++){
		contraharmonic_sum += pow(filter_window[w], p+1);
                sum = pow(filter_window[w],p)+sum;
            }
	    mediaImage.at<uchar>(i, j) = int (contraharmonic_sum/sum);
        }
    }
}

void median_filter(Mat image, Mat median_img, int fil_size){

    int filter_window[fil_size*fil_size];
    int e = fil_size / 2;
    int k;
    for(int i = e ; i<= image.rows-e ; i++){
        for(int j = e ; j<image.cols-e ; j++){
            k = 0;
            for(int i_fil = 0; i_fil<fil_size ; i_fil++){
                for(int j_fil = 0 ; j_fil<fil_size ; j_fil++){
                    filter_window[k] = image.at<uchar>(i+i_fil-e, j+j_fil-e);
                    k++;
                }
            }
            sort(filter_window, filter_window+(fil_size*fil_size));
	    int median = (fil_size*fil_size)/2;
            median_img.at<uchar>(i, j) = filter_window[median];
        }
    }
}


int main(int argc, char** argv){

    Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    if(!image.data){
        cout << "Image error\n";
    }

    Mat chmean_img = image.clone();
    contraharmonic_filter(image, chmean_img, 3, -2);

    Mat median_img = image.clone();
    median_filter(image, median_img, 5);


    namedWindow("Original Image");
    imshow("Original Image", image);
    namedWindow("ContraHarmonicMean Image");
    imshow("Media Image",chmean_img);
    namedWindow("Median Image");
    imshow("Median Image",median_img);

    waitKey();
    return 0;
}


