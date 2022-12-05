//
//  NeuralNetwork.cpp
//  Project
//
//  Created by Ziad Amerr on 05/12/2022.
//
#include <iostream>
#include <vector>
#include <math.h>
#include "NeuralNetwork.hpp"
#include "NeuralNetwork.hpp"
using namespace std;


bool NeuralNetwork::_checkIfNeuronExists(int neuronId, int layerIdx) {
    for(int i = 0; i<neurons.size(); i++)
        if(neurons.at(layerIdx).at(i).getNeuronId() == neuronId)
            return true;
    
    // If not found
    return false;
}

NeuralNetwork::Neuron NeuralNetwork::_getNeuron(int neuronId, int layerIdx) {
    Neuron n;
    for (int i = 0; i < neurons.size(); i++) {
        n = neurons.at(layerIdx).at(i);
        if (n.getNeuronId() == neuronId)
            return n;
    }
    
    // If not found
    cout << "Error! Neuron not found!" << endl;
    return n;
}

void NeuralNetwork::_initializeLayer(int numberOfNeurons, int layerIdx) {
    vector<Neuron> myVec;
    Neuron newNeuron;
    for(int i=0; i<numberOfNeurons; i++) {
        Neuron newNeuron = Neuron(i, layerIdx);
        myVec.push_back(newNeuron);
    }
    neurons.push_back(myVec);
}

void NeuralNetwork::_connectLayers(int firstLayerId) {
    // Loop through the current layers neurons
    for(int i=0; i<neurons.at(firstLayerId).size(); i++) {
        
        // Connect each neuron with ALL the neurons in the next layer
        for(int j=0; j<neurons.at(firstLayerId+1).size(); j++) {
            
            // currentNeuron.addArrow(otherNeuron.getId())
            neurons.at(firstLayerId).at(i).addArrow(neurons.at(firstLayerId+1).at(j).getNeuronId());
        };
    }
};

NeuralNetwork::NeuralNetwork(vector<int> neuronsPerLayer) {
    for(int i=0; i<neuronsPerLayer.size(); i++)
        _initializeLayer(neuronsPerLayer.at(i), i);
    
    for(int i=0; i<neuronsPerLayer.size()-1; i++)
        _connectLayers(i);
}

void NeuralNetwork::printNetwork(string detailed) {
    NeuralNetwork::Neuron n;
    for(int i=0; i<neurons.size(); i++) {
        cout << "Layer " << i << endl;
        for(int j=0; j<neurons.at(i).size(); j++) {
            n = neurons.at(i).at(j);
            cout << "  N#" << n.getNeuronId();
            
            
        
            if(detailed == "detailed" and i!=neurons.size()-1) {
                cout << "-->";
                n.printArrowList();
            } else {
                cout << endl;
            }
        }
        cout << endl;
    }
}


// ************************* PHASE 2 *************************
// Prints summary of the network, n_layers, n_neurons per layer
// void printSummary();

// ************************* PHASE 2 *************************
// Load pretrained model from JSON file
// void loadWeightsFromFile(JSONFile file);

// ************************* PHASE 2 *************************
// Infer model on image and produce output, returns the most confident integer
// int infer(Image img);




