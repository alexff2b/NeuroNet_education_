#pragma once

#include <iostream>
#include <random>

#include "iaVector.h"
#include "iaMatrix.h"

class iaNetwork {
public:
	int layersNumber;

	struct iaLayer {
	public:
		iaVector x;
		iaVector z;
		iaVector fD;
	};

	iaMatrix* weights;
	iaLayer* layers;
	iaVector* deltas;


	iaNetwork();
	iaNetwork(int layersCount);
	iaNetwork(int layersCount, int sizes[]);

	~iaNetwork();

//	double& operator [] (int j) { return value[j]; }

//	double* operator & (int j) { return &value[j]; }

private:
protected:
};