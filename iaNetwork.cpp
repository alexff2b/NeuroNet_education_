#include "iaNetwork.h"


iaNetwork::iaNetwork() : iaNetwork(1) {

}
iaNetwork::iaNetwork(int layersCount) : iaNetwork(layersCount, 0) {

}

iaNetwork::iaNetwork(int layersCount, int sizes[]) {

//	random_device randonGenerator;
//	normal_distribution<> dist(-0.5, 0.5);
//
//	this->layersNumber = layersCount;
//	this->weights = new iaMatrix[layersCount];
//	this->layers = new iaLayer[layersCount];
//	this->deltas = new iaVector[layersCount];
//
//	for (int l = 1; l < layersCount; l++) {
//
//		//		weights[l - 1] = new iaMatrix(sizes[l], sizes[l - 1], rd);
//
//		this->layers[l - 1].x = iaVector(sizes[l - 1], 0);			// Создание вектора для входа слоя
//		this->layers[l - 1].z = iaVector(sizes[l], 0);				// Создание вектора для выхода слоя
//		this->layers[l - 1].fD = iaVector(sizes[l], 0);			// Создание вектора для производной активации слоя
//
//		this->deltas[l - 1] = iaVector(sizes[l], 0);				// Создание вектора для дельт ошибок слоя
//	}
}

iaNetwork::~iaNetwork() {

}


