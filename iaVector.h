#pragma once

#include <iostream>

class iaVector {
public:
	int m;								// Count of inputs
	double* value;						// Inputs (vector)

	iaVector();							//
	iaVector(int m);					//
	iaVector(int m, double values[]);	//

	~iaVector();						//

	double& operator [] (int j) { return value[j]; }

	double* operator & (int j) { return &value[j]; }

protected:	
private:
};
