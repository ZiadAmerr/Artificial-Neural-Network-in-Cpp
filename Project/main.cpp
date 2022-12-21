//
//  main.cpp
//  Project
//
//  Created by Ziad Amerr on 04/12/2022.
//

#include <iostream>
#include <sstream>
#include "../NeuralNetworkCppOnly.cpp"
using namespace std;

void print(vector<string> fileAsString) {
    for(int i=0; i<fileAsString.size(); i++) {
        cout << i << ": " << fileAsString.at(i) << endl;
    }
}
void split(string str, string myList[], int& n) {
    int i = 0;
    stringstream ssin(str);
    while(ssin.good()) {
        ssin >> myList[i];
        ++i;
    }
    n = i;
}
vector<string> getWeightList(string weightsStr) {
    vector<string> weights;
    int n=0;
    string weightsArr[1024];
    split(weightsStr, weightsArr, n);
    for(int i=0; i<n; i++) {
        weights.push_back(weightsArr[i]);
    }
    return weights;
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
    // myNetwork.printNetwork("backward");
    
    // Load pretrained model (weights)
    // myNetwork.loadPretrainedModel("Project/model.model");
    
    // Predict image
    // myNetwork.predict(image);
    
    // Get the 2D vector of activations
    // vector<vector<double>> activations = myNetwork.getActivations();
    
    
    
    vector<string> weightsMatrix = myNetwork.loadWeightsFromFile("Project/pretrainedModel/weights3.weights");
    
    // cout << weightsMatrix.at(0) << endl;
    // -1.3859201669692993
    for(int i=0)
    vector<string> w1 = getWeightList(weightsMatrix.at(0));
    
    // cout << w1.size() << endl;
    //cout << w1.at(0) << endl;
    return 0;
}
