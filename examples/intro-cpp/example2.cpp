// =================================================================
//
// File: example2.cpp
// Author: Pedro Perez
// Description: This file contains the code to perform the numerical 
//				integration of a function within a defined interval. 
//				The time this implementation takes will be used as 
//				the basis to calculate the improvement obtained with 
//				parallel technologies.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <cmath>
#include "utils.h"

const double PI = 3.14159265;
const int RECTS = 1000000000; //1e9

using namespace std;

double function(double x) {
	return sin(x);
}

class Integration {
private:
	double start, dx, result;
	double (*func) (double);

public:
	Integration(double a, double b, double (*fn) (double)) 
		: func(fn) {
		start = MIN_VAL(a, b);
		dx = (MAX_VAL(a, b) - MIN_VAL(a, b)) / RECTS;
	}
	
	
	double getResult() const {
		return result;
	}

	void calculate() {
		double x;

		x = start;
		result = 0;
		for (int i = 0; i < RECTS; i++) {
			result += func(x + (i * dx));
		}
		result = result * dx;
	}
};

int main(int argc, char* argv[]) {
	double ms;
	
	cout << "Starting..." << endl;
	ms = 0;
	Integration obj(0, PI, function);
	for (int i = 0; i < N; i++) {
		start_timer();
		
		obj.calculate();
		
		ms += stop_timer();
	}
	cout << "result = " << setprecision(15) << obj.getResult() << endl;
	cout << "avg time = " << setprecision(15) << (ms / N) << " ms" << endl;
	
	return 0;
}