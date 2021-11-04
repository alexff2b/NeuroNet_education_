#pragma once

#include <iostream>
#include <random>

#include "iaVector.h"
#include "iaMatrix.h"

using namespace std;

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

	iaVector ForwardPropogation(iaVector inputVector);
	void BackwardPropogation(iaVector outputVector, double *error);
	void UpdateWeights(double alpha);
	void Train(iaMatrix X, iaMatrix Y, double alpha, double eps, int epochs);
	void InitWeigths(iaMatrix newWeights);

	


//	double& operator [] (int j) { return value[j]; }

//	double* operator & (int j) { return &value[j]; }

private:
protected:
};