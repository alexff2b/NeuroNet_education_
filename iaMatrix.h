/* **************************************************************************************************** *
 *	Company	: iA
 *	File	: 
 *	Author	: Aleksandr IUSHKEVICH
 *	Project	: Simple NeuroNet
 *	Version	: ???
 *
 *	Сreated	: October 2021
 *
 *	Description:	
 *
 * **************************************************************************************************** */
#pragma once

#include <iostream>
#include "iaVector.h"

class iaMatrix {
public:

	iaVector* vector;

	iaMatrix();										// Default constructor
	iaMatrix(int n);								// Constructor by one size (n * n)
	iaMatrix(int n, int m);							// Constructor by two sizes (n * m)
	iaMatrix(int n, int m, const double values[]);	// Constructor with values
	iaMatrix(iaMatrix& otherMatrix);				// Constructor of copy

	~iaMatrix();									// Destructor

	int numberOfVectors();
	int sizeOfVectors();
	void printMatrix();

	iaVector& operator [](int i) { return vector[i]; }
	iaVector* operator & (int i) { return &vector[0]; }

private:
	int n;		// counts of inputs		
	int m;		// counts of neurones
};
