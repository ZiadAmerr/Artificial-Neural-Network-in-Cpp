//
//  main.cpp
//  Project
//
//  Created by Ziad Amerr on 04/12/2022.
//

#include <iostream>
#include "../NeuralNetworkCppOnly.cpp"


using namespace std;

double _dot(vector<double> weights, vector<double> activations) {
    double activation = 0;
    for(int i=0; i<weights.size(); i++)
        activation += weights.at(i)*activations.at(i);
    
    return activation;
}

int main(int argc, const char * argv[]) {
    vector<vector<double>> image = {
        {0, 1, 2, 3},
        {1, 2, 3, 4},
        {2, 3, 4, 5},
        {3, 4, 5, 6},
        {4, 5, 6, 7}
    };
    
    // Initialize network
    vector<int> NeuralNetworkParams = {28*28, 16, 16, 10};
    
    // Construct the network from the defined parameters
    NeuralNetwork myNetwork = NeuralNetwork(NeuralNetworkParams);
    
    // Load pretrained model (weights)
    // myNetwork.loadPretrainedModel("Project/model.model");
    
    // Predict image
    myNetwork.predict(image);
    
    // Get the 2D vector of activations
    // vector<vector<double>> activations = myNetwork.getActivations();
    
    
    
    // vector<string> fileAsStr = myNetwork.loadWeightsFromFile("Project/weights.weights");
    // myNetwork.printNetwork("backward");
    
    
    
    return 0;
}
