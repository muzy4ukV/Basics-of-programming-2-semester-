#include "vector.h"

Vector::Vector() : x(0), y(0), z(0) {}

Vector::Vector(double x1) : x(x1), y(x1), z(x1) {}

Vector::Vector(double x1, double y1, double z1) : x(x1), y(y1), z(z1) {}

Vector::Vector(Vector& vector1): x(vector1.x), y(vector1.y), z(vector1.z) {}

void printVector(Vector& vector1) {
	printf_s("x: %.3f y: %.3f z: %.3f\n\n", vector1.getX(), vector1.getY(), vector1.getZ());
}

double Vector::getLength() {
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

Vector Vector::operator+(Vector vector1) {
	Vector res;
	res.x = x + vector1.x;
	res.y = y + vector1.y;
	res.z = z + vector1.z;
	return res;
}

double operator*(Vector& vector1, Vector& vector2) {
	return (vector1.x * vector2.x) + (vector1.y * vector2.y) + (vector1.z * vector2.z);
}

void createVector(double* arr) {
	string coordinates;
	cout << "Enter vector's coordinates in format [x y z]: ";
	getline(cin, coordinates);

	int pos;
	for (int i = 0; i < 3; i++)
	{
		if (i == 2)
			arr[i] = stod(coordinates);
		else {
			pos = coordinates.find(' ');
			arr[i] = stod(coordinates.substr(0, pos));
			coordinates.erase(0, pos + 1);
		}
	}

}