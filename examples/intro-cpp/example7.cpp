// =================================================================
//
// File: example7.cpp
// Author: Pedro Perez
// Description: This file implements the code  will generate a
//				fractal image. Uses OpenCV, to compile:
//				g++ example7.cpp `pkg-config --cflags --libs opencv`
//
//				The time this implementation takes will be used as the
//				basis to calculate the improvement obtained with
//				parallel technologies.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "utils.h"

#define WIDTH		1920
#define HEIGHT		1080
#define SCALEX		0.500
#define SCALEY		0.500
#define MAX_COLOR 	255
#define RED_PCT		0.2
#define GREEN_PCT	0.4
#define BLUE_PCT	0.7

using namespace std;
using namespace cv;

class MyComplex {
private:
	float real, img;

public:
	MyComplex(float r, float i) : real(r), img(i) {}

	float magnitude2() const {
		return (real * real) + (img * img);
	}

	MyComplex operator*(const MyComplex &a) {
		return MyComplex( ((real * a.real) - (img * a.img)),
		 				((img * a.real) + (real * a.img)) );
	}

	MyComplex operator+(const MyComplex &a) {
		return MyComplex( (real + a.real),
		 				(img + a.img) );
	}
};


class JuliaSet {
private:
	Mat &img;

	int juliaValue(int x, int y, int width, int height) {
		int k;
		float jx = SCALEX * (float) (width / 2 - x) / (width / 2);
		float jy = SCALEY * (float) (height / 2 - y) / (height / 2);
		MyComplex c(-0.8, 0.156);
		MyComplex a(jx, jy);

		for (k = 0; k < 200; k++) {
		    a = a*a + c;
		    if (a.magnitude2() > 1000) {
		        return 0;
		    }
		}
		return 1;
	}

public:
	JuliaSet(Mat &image) : img(image) {}

	void doTask() {
		int value;

		for(int i = 0; i < img.rows; i++) {
			for(int j = 0; j < img.cols; j++) {
				value = juliaValue(i, j, img.rows, img.cols);
				img.at<cv::Vec3b>(i,j)[RED] =
          (unsigned char) (MAX_COLOR * RED_PCT * value);
				img.at<cv::Vec3b>(i,j)[GREEN] =
          (unsigned char) (MAX_COLOR * GREEN_PCT * value);
				img.at<cv::Vec3b>(i,j)[BLUE] =
          (unsigned char) (MAX_COLOR * BLUE_PCT * value);
			}
		}
	}
};

int main(int argc, char* argv[]) {
    double ms;
    Mat img = Mat(HEIGHT, WIDTH, CV_8UC3);

	ms = 0;
	JuliaSet obj(img);
    for (int i = 0; i < N; i++) {
        start_timer();

		obj.doTask();

		ms += stop_timer();
    }

    cout << "avg time = " << setprecision(15) << (ms / N) << " ms" << endl;
	namedWindow("CPU Julia | c(-0.8, 0.156)", WINDOW_AUTOSIZE);
    imshow("CPU Julia | c(-0.8, 0.156)", img);

	waitKey(0);

    return 0;
}
