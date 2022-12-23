//
//  main.cpp
//  Project
//
//  Created by Ziad Amerr on 04/12/2022.
//

#include <iostream>
#include <sstream>
#include "../NeuralNetworkCppOnly.cpp"
#include "../data.cpp"
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
    // myNetwork.printNetwork("backward");
    
    Keys keys;
    // Predict image
    
    
    
    int predicted, sum, total_n=0, total_sum=0;
    for(int j=0; j<10; j++) {
        sum=0;
        total_n += keys.get(j).size();
        for(int i=0; i<keys.get(j).size(); i++) {
            predicted = myNetwork.infer("Project/test_set/" + to_string(j) + "_img_" + to_string(keys.get(j).at(i)) + ".csv");
            // cout << "The number is: " <<  predicted << endl; // << " i=" + to_string(keys.at(i)) << endl;
            if(predicted == j) {
                sum += 1;
                total_sum += 1;
            }
        }
        cout << "Accuracy classifying: " << to_string(j) << " is " + to_string(double(sum)/keys.get(j).size()*100) + "%" << endl;
    }
    cout << "Model finished inference with Accuracy = " + to_string(double(total_sum)/total_n*100) + "%" << endl;
    
    
    // myNetwork.printActivations(1);
    return 1;
}
