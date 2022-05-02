#include "vector.h"

int main()
{
	cout << "Creating array M1" << endl;
	double* arr = new double[3];
	createVector(arr);
	Vector M1(arr[0], arr[1], arr[2]);
	printVector(M1);
	delete[] arr;

	double x;
	cout << "Creating array M2" << endl;
	cout << "Enter one coordinate: "; cin >> x;
	Vector M2(x);
	printVector(M2);

	Vector M3;
	cout << "Creating array M3" << endl << "M3 = M2 + M1 = ";
	M3 = M1 + M2;
	printVector(M3);
	cout << "Length of vector M3: " << M3.getLength() << endl;
	double scalarProduct = M1 * M3;

	cout << "Scalar product of M1 and M3 is: " << scalarProduct << endl;

}