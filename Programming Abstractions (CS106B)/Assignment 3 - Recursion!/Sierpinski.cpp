/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <math.h>
#include "gwindow.h"
#include "gtypes.h"
#include "simpio.h"
using namespace std;

void drawTriangle(GWindow gw, GPoint p1, GPoint p2, GPoint p3){
	//drawing triangle on points p1, p2 and p3
	gw.drawLine(p1, p2);
	gw.drawLine(p2, p3);
	gw.drawLine(p3, p1);
}

void drawSierpinski(GWindow gw, GPoint p1, GPoint p2, GPoint p3, int N){
	if(N >= 0){
		drawTriangle(gw, p1, p2, p3);
		N--;
		//new points' coordinates for small triangles
		double leftX = (p1.getX() + p2.getX()) / 2.0;
		double rightX = (p2.getX() + p3.getX()) / 2.0;
		double middleX = (p1.getX() + p3.getX()) / 2.0;
		double middleY = (p1.getY() + p2.getY()) / 2.0;
		double downY = p1.getY();
		//new points for small triangles
		GPoint p01(leftX, middleY);
		GPoint p02(rightX, middleY);
		GPoint p03(middleX, downY);
		//drawing smaller triangles with smaller N. (N--)
		drawSierpinski(gw, p1, p01, p03, N);
		drawSierpinski(gw, p01, p2, p02, N);
		drawSierpinski(gw, p03, p02, p3, N);
	}
}

int main() {
	GWindow gw;
	//gathering information
	int N = getInteger("N: ");
	int length = getInteger("length: ");
	//centered points' coordinates
	double x = (gw.getWidth() - length) / 2.0;
	double y = gw.getHeight() / 2.0 + length / (2 * (double)sqrt(3.0));
	double y0 = gw.getHeight() / 2.0 - length /(double)sqrt(3.0);
	//centered points
	GPoint p1(x, y);
	GPoint p2(gw.getWidth() / 2, y0);
	GPoint p3(x + length, y);

	drawSierpinski(gw, p1, p2, p3, N);
    return 0;
}
