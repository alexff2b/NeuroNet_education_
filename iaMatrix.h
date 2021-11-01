#pragma once

#include <iostream>
#include "iaVector.h"

class iaMatrix {
public:
	int n;	
	int m;
	
	iaVector* vector;

	iaMatrix();
	iaMatrix(int n, int m);
	iaMatrix(int n, int m, const double values[]);

	~iaMatrix();

	iaVector& operator [](int i) { return vector[i]; }

	iaVector* operator & (int i) { return &vector[0]; }

private:
};
