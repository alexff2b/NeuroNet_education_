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

iaVector::iaVector() : iaVector(0) { }

iaVector::iaVector(int m) {
	this->m = m;
	this->value = (m != 0 ? new double[m]() : nullptr);
}

iaVector::iaVector(int m, const double values[]) : iaVector(m) {
	for (int j = 0; j < this->m; j++)	this->value[j] = values[j];
}

iaVector::iaVector(iaVector& otherVector) : iaVector(otherVector.m, otherVector.value) { }

iaVector::~iaVector() {}

int iaVector::sizeOfVector() {
	return m;
}

#ifdef DEBUG
void iaVector::printVector() {
	std::cout << "Address m : (" << & m << ")\tAddress value : (" << &value << ")" << std::endl;
	for (int j = 0; j < m; j++)
		std::cout << "(" << & value[j] << ") : \t" << value[j] << std::endl;
	std::cout << std::endl;
}
#endif // DEBUG
