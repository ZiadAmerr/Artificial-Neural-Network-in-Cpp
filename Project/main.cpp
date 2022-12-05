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
        28,
        16,
        16,
        10
    };
    
    NeuralNetwork myNetwork = NeuralNetwork(NeuralNetworkParams);
    
    return 0;
}
