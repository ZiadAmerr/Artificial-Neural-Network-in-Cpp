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
    vector<int> NeuralNetworkParams = {
        20,
        10,
        5,
        1
    };
    
    NeuralNetwork myNetwork = NeuralNetwork(NeuralNetworkParams);
    
    myNetwork.printNetwork("backward");
    return 0;
}
