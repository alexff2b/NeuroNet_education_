
#include "iaNetwork.h"

netSetings::netSetings() : netSetings(0) {

}

netSetings::netSetings(int n) {
    this->numberOfLayers = n;
    this->sizes = (n != 0 ? new int[n]() : nullptr);
}

netSetings::netSetings(int n, int s[]) : netSetings(n) {
    for (int j = 0; j < this->numberOfLayers; j++) {
        this->sizes[j] = s[j];
    }
}

iaNetwork::iaNetwork() : iaNetwork(0) {     // Call constructor with one paremeter as 0 size of network

}

iaNetwork::iaNetwork(int layersCount) {
	this->layersNumber = layersCount - 1;                                                       // Set number of layers
	this->weights = (this->layersNumber != 0 ? new iaMatrix[this->layersNumber]() : nullptr);   // Create matrix for weights with 0 sizes for layers
	this->layers = (this->layersNumber != 0 ? new iaLayer[this->layersNumber]() : nullptr);	    // Create layers with 0 sizes
	this->deltas = (this->layersNumber != 0 ? new iaVector[this->layersNumber]() : nullptr);    // Create vectors of deltas with 0 sizes for layers
}

iaNetwork::iaNetwork(int layersCount, int sizes[]) : iaNetwork(layersCount) {   // Call constructor with one parameter before

	random_device randomGenerator;
	normal_distribution<double> dist(-0.5, 0.5);	
    
	for (int l = 1; l < layersCount; l++) {     // Layers
        int x_size = sizes[l];
        int y_size = sizes[l - 1];
        int matrixSize = x_size * y_size;
        double* randomNumbers = new double[matrixSize]();
        for (int i = 0; i < sizes[l]; i++) {
            int index;
            for (int j = 0; j < sizes[l - 1]; j++) {
                index = i * sizes[l - 1] + j;
                randomNumbers[index] = dist(randomGenerator);
            }
        }
        this->weights[l - 1] = iaMatrix(sizes[l], sizes[l - 1], randomNumbers);     // Create Matrix of weights in layer [l - 1]
        delete[] randomNumbers;
		this->layers[l - 1].x = iaVector(sizes[l - 1]);			// Create Vector for inputs in layer [l - 1]
		this->layers[l - 1].z = iaVector(sizes[l]);				// Create Vector for outputs in layer [l - 1]
		this->layers[l - 1].fD = iaVector(sizes[l]);			// Create Vector for activation derivative in layer [l - 1]
		this->deltas[l - 1] = iaVector(sizes[l]);				// Create Vector for errors deltas in layer [l - 1]
    }
}

iaNetwork::iaNetwork(netSetings setings) : iaNetwork(setings.numberOfLayers, setings.sizes) {

}

iaNetwork::~iaNetwork() {

}

iaVector iaNetwork::ForwardPropogation(iaVector inputVector, activation foncActiv) { // Получение выхода сети (прямое распространение)
 
    for (int l = 0; l < this->layersNumber; l++) {                              // Layers
        if (l == 0) {                                                           // To first input layer:
            for (int i = 0; i < inputVector.sizeOfVector(); i++) {              // Nets in first layer
                this->layers[l].x[i] = inputVector[i];                          // Get end save inputs for net [i]
            }
        } else {                                                                // To other layrs:
            for (int i = 0; i < this->layers[l - 1].z.sizeOfVector(); i++) {    // Nets in layer [l]
                this->layers[l].x[i] = this->layers[l - 1].z[i];                // Get and save inputs for net [i] from previus layer
            }
        }
        for (int i = 0; i < this->weights[l].numberOfVectors(); i++) {          // Nets in layer [l]
            double y = 0;                                                       // Reset output of net [i]
            for (int j = 0; j < this->weights[l].sizeOfVectors(); j++) {        // Inputs of net [i]
                y += this->weights[l][i][j] * this->layers[l].x[j];             // Weighted sum of the input calculation
            }

            switch (foncActiv) {
            case Hyperbolic_Tangent: {          // Hyperbolic Tangent (-1, 1)
                this->layers[l].z[i] = tan(y);                              // Activation 
                this->layers[l].fD[i] = 1 - pow(this->layers[l].z[i], 2);   // Derivative
                break; }
            case Arctangent: {                  // Arctangent 
                this->layers[l].z[i] = atan(y);             // Activation
                this->layers[l].fD[i] = 1 / (y * y + 1);    // Derivative
                break; }
            case Sigmoid: {                     // Logistic, sigmoid (0, 1)
                this->layers[l].z[i] = 1 / (1 + exp(-y));                   // Activation
                this->layers[l].fD[i] = layers[l].z[i] * (-layers[l].z[i]); // Derivative
                break; }
            case ReLu: {                        // ReLU [0, y)
                this->layers[l].z[i] = y > 0 ? y : 0;       // Activation
                this->layers[l].fD[i] = y > 0 ? 1 : 0;      // Derivative
                break; }
            case Gaussian: {                    // Gaussian (0, 1]
                this->layers[l].z[i] = exp(-y * y);             // Activation
                this->layers[l].fD[i] = -2 * y * exp(-y * y);   // Derivative
                break; }
            case Sin: {                         // Sinus [-1, 1]
                this->layers[l].z[i] = sin(y);      // Activation 
                this->layers[l].fD[i] = cos(y);     // Derivative
                break; }
            case Sinc: {                        // Sinc [~-0.217234, 1]
                this->layers[l].z[i] = (y == 0 ? 1 : sin(y) / y);               // Activation
                this->layers[l].fD[i] = (y == 0 ? 0 : cos(y) / y - sin(y) / y); // Derivative
                break; }
            default: {                          // Identity (-, +)
                this->layers[l].z[i] = y;       // Activation
                this->layers[l].fD[i] = 1;      // Derivative
                break; }
            }
        }
    }
    return layers[layersNumber - 1].z;  // Возврат результата
}

void iaNetwork::BackwardPropogation(iaVector outputVector, double* error) {             
    *error = 0;                                                                         // Reset error
    int last = this->layersNumber - 1;                                                  // Setting the previous layer before the last
    for (int i = 0; i < outputVector.sizeOfVector(); i++) {                             // Nets in layer [last]
        double err = this->layers[last].z[i] - outputVector[i];                         // Error calculation
        this->deltas[last][i] = err * this->layers[last].fD[i];                         // Delta calculation
        *error = err * err / 2;                                                         // Amount of error calculation (standard deviation)
    }
    for (int l = last; l > 0; l--) {                                                    // Reverse layers
        for (int j = 0; j < this->weights[l].sizeOfVectors(); j++) {                    // Nets in layer [l]
            this->deltas[l - 1][j] = 0;                                                 // Reset delta of net in layer
            for (int i = 0; i < this->weights[l].numberOfVectors(); i++) {              // Inputs in net [j]
                this->deltas[l - 1][j] += this->weights[l][i][j] * this->deltas[l][i];  // Correcting delta for net [j] in layer [l - 1] 
            }
            this->deltas[l - 1][j] *= this->layers[l - 1].fD[j];                        // Finali correcting delta for net [j] in layer [l - 1]
        }
    }
}

void iaNetwork::UpdateWeights(double alpha) {                                                   
    for (int l = 0; l < this->layersNumber; l++) {                                              // Layers
        for (int i = 0; i < this->weights[l].numberOfVectors(); i++) {                          // Nets in layer [l]
            for (int j = 0; j < this->weights[l].sizeOfVectors(); j++) {                        // Inputs in net [i]
                this->weights[l][i][j] -= alpha * this->deltas[l][i] * this->layers[l].x[j];    // Updatind weight for input [i] in net [j] of layer [l] 
            }
        }
    }
}

void iaNetwork::Train(iaMatrix X, iaMatrix Y, double alpha, double eps, int epochs) {
    int epoch = 1;                                          // Set epoch as first
    double error;                                           // Error in epoch
    do {
        error = 0;                                          // Reset error
        for (int i = 0; i < X.numberOfVectors(); i++) {     // Input vectors of the training set
            ForwardPropogation(X[i], Gaussian);             // Forwardpropogation 
            BackwardPropogation(Y[i], &error);              // Backpropagating
            UpdateWeights(alpha);                           // Updating weights
        }
        cout << "Epoch:\t" << epoch << "\t\tError:\t" << error << endl;
        SaveError(epoch, error);
        epoch++;                                            // Increase the epoch number
    } while (epoch <= epochs && error > eps);               // Execute until the epochs limit or the error reaches an acceptable value 
    SaveWeights();
}

void iaNetwork::SaveError(int epoch, double error) {
    ofstream fError;
    fError.open("setings/errors.txt");              // Open file to save errors in
    if (fError.is_open()) {                         // If file is open:
        fError << epoch << "\t" << error << endl;   // Save nunber of epoch and error for this epoch 
    }
    fError.close();                                 // Close file
}

void iaNetwork::SaveWeights() {
    ofstream fWeights;
    fWeights.open("setings/weights.txt");                                       // Open file to save weights in
    if (fWeights.is_open()) {                                                   // If file is open:
        for (int l = 0; l < this->layersNumber; l++) {                          // Layers
            for (int i = 0; i < this->weights[l].numberOfVectors(); i++) {      // Nets in layer [l]
                for (int j = 0; j < this->weights[l].sizeOfVectors(); j++) {    // Inputs in net [i]
                    fWeights << this->weights[l][i][j] << "\t";                 // Save weight for input [j] of net [i] in layer [l]
                }
                fWeights << endl;                                               // New line in file
            }
        }       
    }
    fWeights.close();                                                           // Close file
}

void iaNetwork::LoadWeights() {
    ifstream fWeights;
    fWeights.open("setings/weights.txt");                                       // Open file to load weights from
    if (fWeights.is_open()) {                                                   // If file is open:
        for (int l = 0; l < this->layersNumber; l++) {                          // Layers
            for (int i = 0; i < this->weights[l].numberOfVectors(); i++) {      // Nets in layer [l]
                for (int j = 0; j < this->weights[l].sizeOfVectors(); j++) {    // Inputs in net [i]
                    fWeights >> this->weights[l][i][j];                         // Load weight for input [j] of net [i] in layer [l]
                }
            }
        }
    }
    fWeights.close();                                                           // Close file
}