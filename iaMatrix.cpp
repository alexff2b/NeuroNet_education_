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

iaMatrix::iaMatrix() : iaMatrix(0) { }

iaMatrix::iaMatrix(int n) : iaMatrix(n, n) { }

iaMatrix::iaMatrix(int n, int m) {
	this->n = ((n == 0 && m > 0) ? 1 : n);					// set number of neurones
	this->m = ((n > 0 && m == 0) ? 1 : m);					// set number of inputs in neuron
	this->vector = (this->n != 0 ? new iaVector[this->n]() : nullptr);	// create vector of vectors
	for (int i = 0; i < this->n; i++) {					//
		this->vector[i] = iaVector(this->m);				//
	}
}

iaMatrix::iaMatrix(int n, int m, const double values[]) : iaMatrix(n, m) {
	for (int i = 0; i < n; i++) {						//
		for (int j = 0; j < m; j++) {					//
			this->vector[i][j] = *values;				//
			values++;						//
		}
	}
}

iaMatrix::iaMatrix(iaMatrix& otherMatrix) : iaMatrix(otherMatrix.n, otherMatrix.m) {
	for (int i = 0; i < this->n; i++) {
		this->vector[i] = iaVector(otherMatrix.vector[i]);
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
