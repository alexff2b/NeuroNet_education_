/* **************************************************************************************************** *
 *	Company	: iA
 *	File	: iaMatrix.cpp
 *	Author	: Aleksandr IUSHKEVICH
 *	Project	: Simple NeuroNet
 *	Version	: ???
 *
 *	Сreated	: October 2021
 *
 *	Description:
 *
 * **************************************************************************************************** */
#include "iaMatrix.h"

iaMatrix::iaMatrix() : iaMatrix(0) { }	// Call constructor by one size with size 0

iaMatrix::iaMatrix(int n) : iaMatrix(n, n) { }	// Call constructor by two sizes with size n (square matrix)

iaMatrix::iaMatrix(int n, int m) {
	this->n = ((n == 0 && m > 0) ? 1 : n);								// Set number of nets
	this->m = ((n > 0 && m == 0) ? 1 : m);								// Set number of inputs in net
	this->vector = (this->n != 0 ? new iaVector[this->n]() : nullptr);	// Create vector of vectors with size 0
	for (int i = 0; i < this->n; i++) {									// Vectors:
		this->vector[i] = iaVector(this->m);							// Recreate Vector [i] with size m
	}
}

iaMatrix::iaMatrix(int n, int m, const double values[]) : iaMatrix(n, m) {	// Call constructor by two sizes before with sizes n and m
	for (int i = 0; i < n; i++) {			// Vectors:
		for (int j = 0; j < m; j++) {		// Values if vector [i]:
			this->vector[i][j] = *values;	// Save value [j] in vector [i]
			values++;						// Incrise pointer for input values
		}
	}
}

iaMatrix::iaMatrix(iaMatrix& otherMatrix) : iaMatrix(otherMatrix.n, otherMatrix.m) {	//  Call constructor by two sizes with sizes of other matrix
	for (int i = 0; i < this->n; i++) {						// Vectors:
		this->vector[i] = iaVector(otherMatrix.vector[i]);	// Create vector [i] as copy of vector [i] from other matrix
	}
}

iaMatrix::~iaMatrix() { }

int iaMatrix::numberOfVectors() {
	return n;
}

int iaMatrix::sizeOfVectors() {
	return m;
}

void iaMatrix::printMatrix() {
	std::cout << "Matrix : \nNumber of Vecros - " << n << "\nSize of Vectors - " << m << "\nAddress - " << this << std::endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			std::cout << "(" << &vector[i][j] << ") : " << vector[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}
