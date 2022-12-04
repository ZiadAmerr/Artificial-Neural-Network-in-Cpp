//
//  main.cpp
//  Project
//
//  Created by Ziad Amerr on 04/12/2022.
//

#include <iostream>
#include "../NeuralNetwork.cpp"
using namespace std;

int main(int argc, const char * argv[]) {
    vector<int> NeuralNetworkParams = {
        10,
        8,
        4,
        1,
        1
    };
    
    NeuralNetwork myNetwork = NeuralNetwork(NeuralNetworkParams);
    
    myNetwork.printNetwork();
    
    return 0;
}