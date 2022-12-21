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
    vector<int> NeuralNetworkParams = {8, 4, 2, 1};
    
    // Construct the network from the defined parameters
    NeuralNetwork myNetwork = NeuralNetwork(NeuralNetworkParams);
    
    // Verify the network
    myNetwork.printNetwork("backward");
    
    // Load pretrained model (weights)
    // myNetwork.loadPretrainedModel("Project/model.model");
    
    // Predict image
    // myNetwork.predict(image);
    
    // Get the 2D vector of activations
    // vector<vector<double>> activations = myNetwork.getActivations();
    
    
    
    vector<string> fileAsStr = myNetwork.loadWeightsFromFile("Project/weights2to3.weights");
    
    
    
    return 0;
}
