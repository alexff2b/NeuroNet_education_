/* **************************************************************************************************** *
 *	Company	: iA
 *	File	: neuro.cpp
 *	Author	: Aleksandr IUSHKEVICH
 *	Project	: Simple NeuroNet
 *	Version	: ???
 *	
 *	Сreated	: October 2021
 * 
 *	Description:	Study of simple neuro network with back propogation
 *					This file contain the main program in firs step used to test
 *					classes for network (iaVector, iaMatrix, iaNetwork)
 *					In second step the main program relise work with network classes.
 * 
 * **************************************************************************************************** */
#include <iostream>
#include <fstream>
#include <random>

#include "iaVector.h"
#include "iaMatrix.h"
#include "iaNetwork.h"

using namespace std;


int main() {
    cout << "Hello World!\n";

	netSettings netwokrSettings;
	ifstream fSettings;
	 
	fSettings.open("settings/settings.txt");
	if (fSettings.is_open()) {
		int n;
		fSettings >> n;
		int* s = new int[n]();
		cout << "Layers : " << n << endl;
		for (int i = 0; i < n; i++) {
			fSettings >> s[i];
			cout << "Neurons in layer " << i << " : " << s[i] << endl;
		}
		netwokrSettings = netSettings(n, s);
	}
	else {
		return 1;
	}
	fSettings.close();
	
	// ----- XOR -----  Use Gauss
	double matrix_X[16][4]{
		{ 0, 0, 0, 0 },		// 0
		{ 0, 0, 0, 1 },		// 1
		{ 0, 0, 1, 0 },		// 1
		{ 0, 0, 1, 1 },		// 0
		{ 0, 1, 0, 0 },		// 1
		{ 0, 1, 0, 1 },		// 0
		{ 0, 1, 1, 0 },		// 0
		{ 0, 1, 1, 1 },		// 0
		{ 1, 0, 0, 0 },		// 1
		{ 1, 0, 0, 1 },		// 0
		{ 1, 0, 1, 0 },		// 0
		{ 1, 0, 1, 1 },		// 0
		{ 1, 1, 0, 0 },		// 0
		{ 1, 1, 0, 1 },		// 0
		{ 1, 1, 1, 0 },		// 0
		{ 1, 1, 1, 1 } };	// 0
	double matrix_Y[16][1]{
		{ 0.0 },		// 0
		{ 1.0 },		// 1
		{ 1.0 },		// 1
		{ 0.0 },		// 0
		{ 1.0 },		// 1
		{ 0.0 },		// 0
		{ 0.0 },		// 0
		{ 1.0 },		// 1
		{ 1.0 },		// 1
		{ 0.0 },		// 0
		{ 0.0 },		// 0
		{ 1.0 },		// 1
		{ 0.0 },		// 0
		{ 1.0 },		// 1
		{ 1.0 },		// 1
		{ 0.0 } };		// 0
		

	iaMatrix X(16, 4, *matrix_X);
	iaMatrix Y(16, 1, *matrix_Y);

	iaNetwork network(netwokrSettings);
	//network.loadWeights();

	iaVector outputs(netwokrSettings.sizes[netwokrSettings.numberOfLayers - 1]);

	network.Train(X, Y, 0.5, 1e-6, 1000000);

	cout << "X1\tX2\tX3\tX4\tAnswer" << endl;
	for (int i = 0; i < 16; i++) {
		iaVector outputs;
		outputs = network.ForwardPropogation(X[i], iaNetwork::Gaussian);
		cout << X[i][0] << "\t" << X[i][1] << "\t" << X[i][2] << "\t" << X[i][3] << "\toutput : " << outputs[0] << endl;
	}
	//network.SaveWeights();

	return 0;
}