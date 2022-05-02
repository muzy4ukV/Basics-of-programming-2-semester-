#pragma once

#include <iostream>
#include <math.h>
#include <string>
using namespace std;


class Vector {
private:
	double x;
	double y;
	double z;
public:
	Vector();
	Vector(double);
	Vector(double, double, double);
	Vector(Vector& vector1);
	double getX() { return x; }
	double getY() { return y; }
	double getZ() { return z; }
	double getLength();
	Vector operator+(Vector);
	friend double operator*(Vector& vector1, Vector& vector2);
};

void createVector(double* arr);
void printVector(Vector& vector1);
