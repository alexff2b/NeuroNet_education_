#include "iaMatrix.h"

iaMatrix::iaMatrix() : iaMatrix(0, 0) {

}

iaMatrix::iaMatrix(int n, int m) : iaMatrix(n, m, nullptr) {

}

iaMatrix::iaMatrix(int n, int m, const double values[]) {
	this->n = n;
	this->m = m;
	this->vector = (n != 0 ? new iaVector[n]() : nullptr);
	for (int i = 0; i < n; i++) {		//
		this->vector[i].m = m;
		this->vector[i].value = new double[m]();
		if (values != nullptr) {
			for (int j = 0; j < m; j++) {
				this->vector[i].value[j] = *values;
				values++;
			}
		}
	}
}

iaMatrix::~iaMatrix() {
	n = 0;
	m = 0;
}
