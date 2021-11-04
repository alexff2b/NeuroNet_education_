
#include "iaNetwork.h"


iaNetwork::iaNetwork() : iaNetwork(0) {

}

iaNetwork::iaNetwork(int layersCount) {
	this->layersNumber = layersCount;
	this->weights = (this->layersNumber != 0 ? new iaMatrix[this->layersNumber]() : nullptr);
	this->layers = (this->layersNumber != 0 ? new iaLayer[this->layersNumber]() : nullptr);	
	this->deltas = (this->layersNumber != 0 ? new iaVector[this->layersNumber]() : nullptr);
}

iaNetwork::iaNetwork(int layersCount, int sizes[]) : iaNetwork(layersCount) {

	random_device randomGenerator;
	normal_distribution<double> dist(-0.5, 0.5);	

	for (int l = 1; l < layersCount; l++) {
		int x_size = sizes[l];
		int y_size = sizes[l - 1];
		double *randomNumbers = new double[x_size * y_size];
		for (int i = 0; i < sizes[l]; i++) {
			for (int j = 0; j < sizes[l - 1]; j++) {
				randomNumbers[i * sizes[l - 1] + j] = dist(randomGenerator);
				//cout << i * sizes[l - 1] + j << "\t" << randomNumbers[j + i] << "\t";
			}
			cout << endl;
		}
		this->weights[l - 1] = iaMatrix(sizes[l], sizes[l - 1], randomNumbers);

		this->layers[l - 1].x = iaVector(sizes[l - 1]);			// Создание вектора для входа слоя
		this->layers[l - 1].z = iaVector(sizes[l]);				// Создание вектора для выхода слоя
		this->layers[l - 1].fD = iaVector(sizes[l]);			// Создание вектора для производной активации слоя

		this->deltas[l - 1] = iaVector(sizes[l]);				// Создание вектора для дельт ошибок слоя

		delete[] randomNumbers;
	}
}

iaNetwork::~iaNetwork() {

}

iaVector iaNetwork::ForwardPropogation(iaVector inputVector) { // Получение выхода сети (прямое распространение)
    
    for (int l = 0; l < this->layersNumber; l++) {                      // Перебор слоев
        if (l == 0) {                                                   // Если активный слой нулевой
            for (int i = 0; i < inputVector.sizeOfVector(); i++)        // Перебор нейронов
                this->layers[l].x[i] = inputVector[i];                  // Получить входные сигналы
        } else {                                                        // иначе если это внутренный или выходной слои
            for (int i = 0; i < this->layers[l - 1].z.sizeOfVector(); i++)    // Перебор нейронов
                this->layers[l].x[i] = this->layers[l - 1].z[i];        // Получить входные сигналы от предыдущего слоя
        }
        for (int i = 0; i < this->weights[l].numberOfVectors(); i++) {        // Перебор нейронов
            double y = 0;                                               // Выход функции активации нейрона
            for (int j = 0; j < this->weights[l].sizeOfVectors(); j++)        // Перебор входов в нейрон
                y += this->weights[l][i][j] * this->layers[l].x[j];                 // Подсчет взвешенной суммы входных сигналов
            
            this->layers[l].z[i] = tan(y);                                    // Активация функции гиперболическим тангенсом (-1, 1)
            //layers[k].z[i] = 1 / (1 + Math.Exp(-y));                  // Активация функции сигмойдной функцией (0, 1)
            //layers[k].z[i] = y > 0 ? y : 0;                           // Активация функции ReLU [0, y)
            //layers[k].z[i] = Math.Exp(- y * y);                       // Активация функции Гаусса (0, 1]
            //layers[k].z[i] = Math.Sin(y);

            this->layers[l].fD[i] = 1 - this->layers[l].z[i] * this->layers[l].z[i];      // Производная гиперболического тангенса
            //layers[k].deltaF[i] = layers[k].z[i] * (1 - layers[k].z[i]);            // Производная сигмойдной функции
            //layers[k].deltaF[i] = y > 0 ? 1 : 0;                          // Производная функции ReLU
            //layers[k].deltaF[i] = -2 * y * Math.Exp(- y * y);             // Производная функции Гаусса
            //layers[k].deltaF[i] = Math.Cos(y);
        }
    }
    return layers[layersNumber - 1].z;                                      // Возврат результата
}

void iaNetwork::BackwardPropogation(iaVector outputVector, double* error) { // Подготовка к обновлению весовых коэффициентов (обратное распространение)
    error = 0;                                                              // Сброс величины ошибки в ноль
    int last = this->layersNumber - 1;                                            // Установка предыдущего перед последним слоя
    for (int i = 0; i < outputVector.sizeOfVector(); i++) {                 // Перебор нейронов
        double err = this->layers[last].z[i] - outputVector[i];                   // Вычисление ошибки
        this->deltas[last][i] = err * this->layers[last].fD[i];                         // Вычисление дельты
        *error = err * err / 2;                                             // Подсчет величины ошибки (среднеквадратичное отклонение)
    }
    for (int l = last; l > 0; l--) {                                        // Обратный перебор слоев
        for (int j = 0; j < this->weights[l].sizeOfVectors(); j++) {              // Перебо нейронов
            this->deltas[l - 1][j] = 0;                                           // Сброс дельты
            for (int i = 0; i < this->weights[l].numberOfVectors(); i++)          // Перебор входов в нейрон
                this->deltas[l - 1][j] += this->weights[l][i][j] * this->deltas[l][i];        // Коррекция дельты
            this->deltas[l - 1][j] *= this->layers[l - 1].fD[j];                        // Коррекция последней дельты
        }
    }
}

void iaNetwork::UpdateWeights(double alpha) {                               // Обновление весовых коэффициентов (alpha - скорость обучения)
    for (int l = 0; l < this->layersNumber; l++) {                                // Перебор слоев
        for (int i = 0; i < this->weights[l].numberOfVectors(); i++) {            // Перебор нейронов
            for (int j = 0; j < this->weights[l].sizeOfVectors(); j++) {          // Перебор входов в нейрон
                this->weights[l][i][j] -= alpha * this->deltas[l][i] * this->layers[l].x[j];  // Обновление весового коэффициента
            }
        }
    }
}

void iaNetwork::Train(iaMatrix X, iaMatrix Y, double alpha, double eps, int epochs) {   //
    int epoch = 1;                                                                  // Установить номер эпохи первый
    double error;                                                                   // Ошибка в эпохе
    do {
        error = 0;                                                                  // Сбросить величину ошибки
        for (int i = 0; i < X.numberOfVectors(); i++) {                                        // Перебор элементов обучающего множества
            ForwardPropogation(X[i]);                                                          // Прямое распространение сигнала
            BackwardPropogation(Y[i], &error);                                              // Обратное распространение ошибки
            UpdateWeights(alpha);                                                   // Обновление весовых коэффициентов
        }
        //using (StreamWriter fwErrors = new StreamWriter("errors.txt", true)) {      //
        //    fwErrors.WriteLine(error);                                              //
        //}
        cout << "Epoch:\t" << epoch << "\t\tError:\t" << error << endl;
        epoch++;                                                                    // Увеличить номер эпохи
    } while (epoch <= epochs && error > eps);                                       // Выполнять пока не закончатся эпохи или ошибка не достигнет допостимого значенияx

    //using (StreamWriter fwWeights = new StreamWriter("weights.txt", false)) {       //
    //    error = 0;
    //    for (int k = 0; k < layersN; k++) {
    //        for (int i = 0; i < weights[k].n; i++) {                                // Перебор нейронов

    //            for (int j = 0; j < weights[k].m; j++) {                            // Перебор входов в нейрон
    //                fwWeights.Write(weights[k][i, j]);
    //                if (j < weights[k].m - 1) { fwWeights.Write("\t"); }
    //            }
    //            fwWeights.WriteLine();
    //        }
    //    }
    //}
}

void iaNetwork::InitWeigths(iaMatrix newWeights) {
    for (int l = 0; l < this->layersNumber; l++) {                          // Перебор слоев
        for (int i = 0; i < this->weights[l].numberOfVectors(); i++) {      // Перебор нейронов
            for (int j = 0; j < this->weights[l].sizeOfVectors(); j++) {    // Перебор входов в нейрон
                this->weights[l][i][j] = newWeights[l][j];                 // Обновление весового коэффициента
            }
        }
    }
}