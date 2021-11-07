#pragma once

#include <iostream>
#include <fstream>
#include <random>

#include "iaVector.h"
#include "iaMatrix.h"

using namespace std;

struct netSettings {

	netSettings();
	netSettings(int n);
	netSettings(int n, int s[]);

	int numberOfLayers;
	int* sizes;
	//char* weightsFile;
};

class iaNetwork {
public:
	enum activation {
		Hyperbolic_Tangent,
		Arctangent,
		Sigmoid,
		ReLu,
		Gaussian,
		Sin,
		Sinc
	};

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
	iaNetwork(netSettings settings);

	~iaNetwork();

	iaVector ForwardPropogation(iaVector inputVector, activation foncActiv);
	void BackwardPropogation(iaVector outputVector, double *error);
	void UpdateWeights(double alpha);
	void Train(iaMatrix X, iaMatrix Y, double alpha, double eps, int epochs);

private:
	void SaveError(int epoch, double error);
	void SaveWeights();
	void LoadWeights();
};