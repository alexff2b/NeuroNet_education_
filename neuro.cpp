/* **************************************************************************************************** *
 *	Company	: iA
 *	File	: neuro.cpp
 *	Author	: Aleksandr IUSHKEVICH
 *	Project	: Simple NeuroNet
 *	Version	: ???
 *	
 *	Сreated	: October 2021
 * 
 *	Description:	Study of simple neuro network with back propogation
 *					This file contain the main program in firs step used to test
 *					classes for network (iaVector, iaMatrix, iaNetwork)
 *					In second step the main program relise work with network classes.
 * 
 * **************************************************************************************************** */
#include <iostream>

#include "iaVector.h"
#include "iaMatrix.h"
//#include "iaNetwork.h"

using namespace std;

void iaVectorTest();
void iaMatrixTest();
//void iaNetworkTest();

int main() {
    cout << "Hello World!\n";	

	// ---------- iaVector Test ----------
	//iaVectorTest();

	//  ---------- iaMatrix Test ----------
	iaMatrixTest();

	//  ---------- iaNetwork Test ----------
	//iaNetworkTest();
	

	return 0;
}

void iaVectorTest() {

	double v1[6]{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
	double* v2 = new double[15]{ 7.7, 6.6, 5.5, 4.4, 3.3, 2.2, 1.1, 0.0, -1.1, -2.2, -3.3, -4.4, -5.5, -6.6, -7.7 };

	cout << "Address v1 : (" << &v1 << ")" << endl;
	for (int i = 0; i < 6; i++)
		cout << "(" << &v1[i] << ") : " << v1[i] << endl;

	cout << "Address v2 : (" << &v2 << ")" << endl;
	for (int i = 0; i < 15; i++)
		cout << "(" << &v2[i] << ") : " << v2[i] << endl;

	cout << "Initialization of 4 vectors" << endl;
	iaVector vector1;
	iaVector vector2(2);
	iaVector vector3(6, v1);
	iaVector vector4;

	int size = 0;

	cout << "vector 1" << endl; vector1.printVector();
	cout << "vector 2" << endl; vector2.printVector();
	cout << "vector 3" << endl; vector3.printVector();
	cout << "vector 4" << endl; vector4.printVector();

	cout << "Charge first vector" << endl;

	vector1 = iaVector(15, v2);

	cout << "vector 1" << endl; vector1.printVector();
	
	cout << "Charge fourth vector" << endl;

	vector4 = iaVector(vector1);
	
	cout << "vector 1" << endl; vector1.printVector();
	cout << "vector 4" << endl; vector4.printVector();

	cout << "Swap first vector" << endl;

	size = vector1.sizeOfVector();
	for (int i = 0; i < size / 2; i++) {
		double temp = vector1[i];
		vector1[i] = vector1[size - i - 1];
		vector1[size - i - 1] = temp;
	}

	cout << "vector 1" << endl; vector1.printVector();
	cout << "vector 4" << endl; vector4.printVector();

	cout << "Swap v2 vector" << endl;

	for (int i = 0; i < 15 / 2; i++) {
		double temp = v2[i];
		v2[i] = v2[15 - i - 1];
		v2[15 - i - 1] = temp;
	}

	cout << "vector 1" << endl; vector1.printVector();
	cout << "vector 4" << endl; vector4.printVector();

	cout << "End of test" << endl;
}

void iaMatrixTest() {

	double v1[2][3]{ { 1.0, 2.0, 3.0 },  { 4.0, 5.0, 6.0 } };
	double v2[3][5]{ { -7.0, -6.0, -5.0, -4.0, -3.0 }, { -2.0, -1.0, 0.0, 1.0, 2.0 }, { 3.0, 4.0, 5.0, 6.0, 7.0 } };

	cout << "Address v1 : (" << &v1 << ")" << endl;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++)
			cout << "(" << &v1[i][j] << ") : " << v1[i][j] << "\t";
		cout << endl;
	}

	cout << "Address v2 : (" << &v2 << ")" << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++)
			cout << "(" << &v2[i][j] << ") : " << v2[i][j] << "\t";
		cout << endl;
	}

	iaMatrix matrix1;
	iaMatrix matrix2(3, 0);
	iaMatrix matrix3(2, 1);
	iaMatrix matrix4(0, 3);
	iaMatrix matrix5(2, 3, *v1);
	iaMatrix matrix6;

	cout << "matrix 1" << endl; matrix1.printMatrix();
	cout << "matrix 2" << endl; matrix2.printMatrix();
	cout << "matrix 3" << endl; matrix3.printMatrix();
	cout << "matrix 4" << endl; matrix4.printMatrix();
	cout << "matrix 5" << endl; matrix5.printMatrix();
	cout << "matrix 6" << endl; matrix6.printMatrix();

	matrix1 = iaMatrix(3, 5, *v2);

	cout << "matrix 1" << endl; matrix1.printMatrix();

	cout << endl;
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 3; j++) {
			double tempValue = v1[i][j];
			v1[i][j] = v1[2 - i - 1][3 - j - 1];
			v1[2 - i - 1][3 - j - 1] = tempValue;
		}
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++)
			cout << "(" << &v1[i][j] << ") : " << v1[i][j] << "\t";
		cout << endl;
	}

	cout << "matrix 5" << endl; matrix5.printMatrix();

	matrix6 = iaMatrix(matrix5);

	cout << "matrix 5" << endl; matrix5.printMatrix();
	cout << "matrix 6" << endl; matrix6.printMatrix();


//
//	matrix2 = iaMatrix(matrix1.n, matrix1.m);
//
//	for (int i = 0; i < matrix1.n; i++) {
//		matrix2[matrix1.n - i - 1] = iaVector(matrix1.m);
//		for (int j = 0; j < matrix1.m; j++) {
//			matrix2[matrix1.n - i - 1][matrix1.m - j - 1] = matrix1[i][j];
//		}
//	}
//
//	cout << "matrix 1" << endl; matrix1.printMatrix();
//	cout << "matrix 2" << endl; matrix2.printMatrix();
//	cout << "matrix 3" << endl; matrix3.printMatrix();
//	cout << "matrix 4" << endl; matrix4.printMatrix();
//
//	for (int i = 0; i < matrix1.n; i++)
//		for (int j = 0; j < matrix1.m; j++)
//			cout << matrix1[i][j] << " ";
//	cout << endl;
//	for (int i = 0; i < matrix1.n; i++)
//		for (int j = 0; j < matrix1.m; j++)
//			cout << matrix2[i][j] << " ";
//	cout << endl;
//
//	matrix5 = matrix4;
//
//	cout << endl;
//	cout << "Address n : (" << &matrix5.n << ")\tAddress m : (" << &matrix5.m << ")\tAddress vector : (" << &matrix5.vector << ")" << std::endl;
//	for (int i = 0; i < matrix1.n; i++)
//		for (int j = 0; j < matrix1.m; j++)
//			cout << matrix2[i][j] << " ";
//	cout << endl;
//
//	iaMatrix matrix6 = { 3, 4 };
}

//void iaNetworkTest() {
//
//}