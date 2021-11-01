#include "iaVector.h"

iaVector::iaVector() : iaVector(0) {

}

iaVector::iaVector(int m) : iaVector(m, nullptr) {

}

iaVector::iaVector(int m, double values[]) {

	this->m = m;
	this->value = (m != 0 ? new double[m]() : nullptr); 
	for (int j = 0; j < m; j++)	this->value[j] = (values != nullptr ? values[j] : 0);
}

iaVector::~iaVector() {

	m = 0;
	delete[] value;
}