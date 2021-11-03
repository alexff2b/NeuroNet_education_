/* **************************************************************************************************** *
 *	Company	: iA
 *	File	: iaVector.h
 *	Author	: Aleksandr IUSHKEVICH
 *	Project	: Simple NeuroNet
 *	Version	: ???
 *
 *	Сreated	: October 2021
 *
 *	Description:	Class to create a vector with size (m) and values of double type (values).
 *
 * **************************************************************************************************** */
#pragma once

#include <iostream>

#define DEBUG

class iaVector {
public:
	
	iaVector();								// Default constructor
	iaVector(int m);						// Constructor by size
	iaVector(int m, const double values[]);	// Constructor with values
	iaVector(iaVector& otherVector);		// Constructor of copy

	~iaVector();							// Destructor

	int sizeOfVector();

#ifdef DEBUG
	void printVector();						// Print all data of vector with addresses (used to debug)
#endif // DEBUG

	double& operator [] (int j) { return value[j]; }
	double* operator & (int j) { return &value[j]; }
	
private:
	int m;									// Count of inputs
	double* value;							// Inputs (vector)
};
