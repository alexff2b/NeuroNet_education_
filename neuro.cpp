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
#include <random>

#include "iaVector.h"
#include "iaMatrix.h"
#include "iaNetwork.h"

using namespace std;

void iaVectorTest();
void iaMatrixTest();
void iaNetworkTest();

int main() {
    cout << "Hello World!\n";

	// ----- XOR -----  Use Gauss
	double matrix_X[4][2]{ { 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 1 } };
	double matrix_Y[4][1]{ { 0.0 }, { 1.0 }, { 1.0 }, { 0.0 } };

	iaMatrix X(4, 2, *matrix_X);
	iaMatrix Y(4, 1, *matrix_Y);

	int sizes[]{ 2, 3, 1 };
	int numberL = sizeof(sizes) / sizeof(sizes[0]);

	iaNetwork network(numberL, sizes);

	iaVector outputs(sizes[numberL - 1]);

	network.Train(X, Y, 0.5, 1e-7, 10000); // запускаем обучение сети 

	cout << "X1\tX2\tAnswer" << endl;
	for (int i = 0; i < 4; i++) {
		iaVector outputs;
		outputs = network.ForwardPropogation(X[i]);
		cout << X[i][0] << "\t" << X[i][1] << "\toutput : " << outputs[0] << endl;
	}



	// ---------- iaVector Test ----------
	//iaVectorTest();

	//  ---------- iaMatrix Test ----------
	//iaMatrixTest();

	//  ---------- iaNetwork Test ----------
	//iaNetworkTest();
	

	return 0;
}

void iaVectorTest() {

	double v1[6]{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
	double* v2 = new double[15]{ 7.7, 6.6, 5.5, 4.4, 3.3, 2.2, 1.1, 0.0, -1.1, -2.2, -3.3, -4.4, -5.5, -6.6, -7.7 };

	iaVector vector1;
	iaVector vector2(2);
	iaVector vector3(6, v1);
	iaVector vector4;

	int size = 0;

	vector3.printVector();

	vector1 = iaVector(15, v2);

	vector4 = iaVector(vector1);

	size = vector1.sizeOfVector();
	for (int i = 0; i < size / 2; i++) {
		double temp = vector1[i];
		vector1[i] = vector1[size - i - 1];
		vector1[size - i - 1] = temp;
	}

	for (int i = 0; i < 15 / 2; i++) {
		double temp = v2[i];
		v2[i] = v2[15 - i - 1];
		v2[15 - i - 1] = temp;
	}
}

void iaMatrixTest() {

	double v1[2][3]{ { 1.0, 2.0, 3.0 },  { 4.0, 5.0, 6.0 } };
	double v2[3][5]{ { -7.0, -6.0, -5.0, -4.0, -3.0 }, { -2.0, -1.0, 0.0, 1.0, 2.0 }, { 3.0, 4.0, 5.0, 6.0, 7.0 } };

	iaMatrix matrix1;
	iaMatrix matrix2(3, 0);
	iaMatrix matrix3(2, 1);
	iaMatrix matrix4(0, 3);
	iaMatrix matrix5(2, 3, *v1);
	iaMatrix matrix6;

	matrix5.printMatrix();

	matrix1 = iaMatrix(3, 5, *v2);

	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 3; j++) {
			double tempValue = v1[i][j];
			v1[i][j] = v1[2 - i - 1][3 - j - 1];
			v1[2 - i - 1][3 - j - 1] = tempValue;
		}
	}

	matrix6 = iaMatrix(matrix5);

	matrix2 = iaMatrix(matrix1.numberOfVectors(), matrix1.sizeOfVectors());

	for (int i = 0; i < matrix1.numberOfVectors(); i++) {
		matrix2[matrix1.numberOfVectors() - i - 1] = iaVector(matrix1.sizeOfVectors());
		for (int j = 0; j < matrix1.sizeOfVectors(); j++) {
			matrix2[matrix1.numberOfVectors() - i - 1][matrix1.sizeOfVectors() - j - 1] = matrix1[i][j];
		}
	}

	matrix5 = matrix4;

	//iaMatrix matrix6 = { 3, 4 };
}

void iaNetworkTest() {

	int numOfLayers = 3;
	int sizes[3] = { 4, 8, 1 };

	iaNetwork network(numOfLayers, sizes);

}