// =================================================================
//
// File: Example2.java
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

class Sin implements Function {
	public double eval(double x) {
		return Math.sin(x);
	}
}

public class Example2 {
	private static final int RECTS = 1_000_000_000;
	private double start, dx, result;
	private Function fn;
	
	public Example2(double a, double b, Function fn) {
		this.start = Math.min(a, b);
		this.dx = (Math.max(a,b) - Math.min(a, b)) / RECTS;
		this.fn = fn;
	}
	
	public double getResult() {
		return result;
	}
	
	public void calculate() {
		double x;
		
		x = start;
		result = 0;
		for (i = 0; i < RECTS; i++) {
			result += fn(x + (i * dx));
		}
		return (result * dx);
	}
	
	public static void main(String args[]) {
		long startTime, stopTime;
		double ms;
		
		System.out.printf("Starting...\n");
		ms = 0;
		Example2 e = new Example2(0, Math.PI, new Sin());
		for (int i = 0; i < Utils.N; i++) {
			startTime = System.currentTimeMillis();
			
			e.calculate();
			
			stopTime = System.currentTimeMillis();
			
			ms += (stopTime - startTime);
		}
		System.out.printf("result = %.5f\n", e.getResult());
		System.out.printf("avg time = %.5f\n", (ms / Utils.N));
	}
}
			
