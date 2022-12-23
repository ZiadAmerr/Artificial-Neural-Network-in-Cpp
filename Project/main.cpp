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

//void print(vector<string> fileAsString) {
//    for(int i=0; i<fileAsString.size(); i++) {
//        cout << i << ": " << fileAsString.at(i) << endl;
//    }
//}
//void split(string str, string myList[], int& n) {
//    n = 0;
//    stringstream ssin(str);
//    while(ssin.good()) {
//        ssin >> myList[n];
//        ++n;
//    }
//}
//vector<string> getWeightList(string weightsStr) {
//    vector<string> weights;
//    int n=0;
//    string weightsArr[1024];
//    split(weightsStr, weightsArr, n);
//    cout << n << endl;
//    for(int i=0; i<n; i++) {
//        weights.push_back(weightsArr[i]);
//    }
//    return weights;
//}


void print2(vector<vector<double>> m) {
    for(int i=0; i<m.size(); i++) {
        for(int j=0; j<m.at(i).size(); j++)
            cout << i << "-" << j << ": " << m.at(i).at(j) << endl;
        cout << endl;
    }
}


int main(int argc, const char * argv[]) {
    // Initialize network
    vector<int> NeuralNetworkParams = {28*28, 16, 16, 10};
    
    // Construct the network from the defined parameters
    NeuralNetwork myNetwork = NeuralNetwork(NeuralNetworkParams);
    
    // Load pretrained model
    myNetwork.loadPretrainedModel("Project/pretrainedModel/");
    
    // Verify the network
    myNetwork.printNetwork("backward");
    
    // Predict image
    // myNetwork.predict(image);
    
    return 1;
}
