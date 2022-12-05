//
//  main.cpp
//  Project
//
//  Created by Ziad Amerr on 04/12/2022.
//

#include <iostream>
//#include "../NeuralNetwork.cpp"
//#include "../Activations.cpp"
#include "NeuralNetwork.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    vector<int> NeuralNetworkParams = {
        16,
        8,
        4
    };
    
    NeuralNetwork myNetwork = NeuralNetwork(NeuralNetworkParams);
    
    myNetwork.printNetwork("detailed");
    
    //cout << NeuralNetwork::Activations::Sigmoid(0.5) << endl;
    
    return 0;
}
