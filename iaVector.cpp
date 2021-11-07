/* **************************************************************************************************** *
 *	Company	: iA
 *	File	: iaVector.cpp
 *	Author	: Aleksandr IUSHKEVICH
 *	Project	: Simple NeuroNet
 *	Version	: ???
 *
 *	Сreated	: October 2021
 *
 *	Description:	.
 *
 * **************************************************************************************************** */
#include "iaVector.h"

iaVector::iaVector() : iaVector(0) { }	// Call  constructor by size with size 0

iaVector::iaVector(int m) {
	this->m = m;										// Set siaze of vector
	this->value = (m != 0 ? new double[m]() : nullptr);	// Create vector of values with m size
}

iaVector::iaVector(int m, const double values[]) : iaVector(m) {	// Call constructor by sizes with m size before
	for (int j = 0; j < this->m; j++) {		// Values in vector:
		this->value[j] = values[j];			// Save value in vector at index [j]
	}
}

iaVector::iaVector(iaVector& otherVector) : iaVector(otherVector.m, otherVector.value) { } // Call constructor by values with other vector values and size

iaVector::~iaVector() {}

int iaVector::sizeOfVector() {
	return m;
}

void iaVector::printVector() {

	std::cout << "Layer size : " << m << "\n" << "Address  - " << this << std::endl;
	for (int j = 0; j < m; j++)
		std::cout << "(" << &value[j] << ") : \t" << value[j] << std::endl;
	std::cout << std::endl;
}