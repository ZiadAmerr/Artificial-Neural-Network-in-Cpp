//
//  NeuralNetwork.cpp
//  Project
//
//  Created by Ziad Amerr on 04/12/2022.
//
#include <iostream>
#include <vector>
using namespace std;

class NeuralNetwork {
private:
    class Arrow {
    public:
        Arrow(int nextNeuronId, double weight=0) {
            this->nextNeuronId = nextNeuronId;
            this->weight = weight;
        }
        
        void setWeight(double w) {
            weight = w;
        }
        
        double getWeight() {
            return weight;
        }
        
        int getNextNeuronId() {
            return nextNeuronId;
        }

    private:
        int nextNeuronId;
        double weight;
    };
    
    class Neuron {
    public:
        Neuron() {
            neuronId = 0;
            layerId = 0;
            activation = 0;
        }
        
        Neuron(int neuronId, int layerId) {
            this->neuronId = neuronId;
            this->layerId = layerId;
            this->activation = 0;
        }
        
        ~Neuron() {}
        
        int getNeuronId() {
            return neuronId;
        }
        
        vector<Arrow> getArrowList() {
            return arrowList;
        }
        
        void addArrow(int nextNeuronId) {
            Arrow myArrow = Arrow(nextNeuronId, 0);
            arrowList.push_back(myArrow);
        }
        
        void printArrowList() {
            cout << '[';
            for(auto it = arrowList.begin(); it != arrowList.end(); it++)
                cout << "N#" << it->getNextNeuronId() << '(' << it->getWeight() <<"), ";
            cout << ']' << endl;
        }
        
        int getLayerId() {
            return layerId;
        }

    private:
        int neuronId, layerId;
        double activation;
        vector<Arrow> arrowList;
    };
    
    vector<vector<Neuron>> neurons;
    
    bool _checkIfNeuronExists(int neuronId, int layerIdx) {
        for(int i = 0; i<neurons.size(); i++)
            if(neurons.at(layerIdx).at(i).getNeuronId() == neuronId)
                return true;
        
        // If not found
        return false;
    }
    
    Neuron _getNeuron(int neuronId, int layerIdx) {
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
    
    void _initializeLayer(int numberOfNeurons, int layerIdx) {
        vector<Neuron> myVec;
        Neuron newNeuron;
        for(int i=0; i<numberOfNeurons; i++) {
            Neuron newNeuron = Neuron(i, layerIdx);
            myVec.push_back(newNeuron);
        }
        neurons.push_back(myVec);
    }
    
    void _connectLayers(int firstLayerId) {
        // Loop through the current layers neurons
        for(int i=0; i<neurons.at(firstLayerId).size(); i++) {
            
            // Connect each neuron with ALL the neurons in the next layer
            for(int j=0; j<neurons.at(firstLayerId+1).size(); j++) {
                neurons.at(firstLayerId).at(i).addArrow(neurons.at(firstLayerId+1).at(j).getNeuronId());
            };
        }
    };
    
public:
    NeuralNetwork(vector<int> neuronsPerLayer) {
        for(int i=0; i<neuronsPerLayer.size(); i++)
            _initializeLayer(neuronsPerLayer.at(i), i);
        
        for(int i=0; i<neuronsPerLayer.size()-1; i++)
            _connectLayers(i);
    }
    
    void printNetwork() {
        Neuron n;
        for(int i=0; i<neurons.size(); i++) {
            cout << "Layer " << i << endl;
            for(int j=0; j<neurons.at(i).size(); j++) {
                n = neurons.at(i).at(j);
                cout << "  N#" << n.getNeuronId() << "-->";
                n.printArrowList();
            }
            cout << endl;
        }
    }
    
    // Prints summary of the network, n_layers, n_neurons per layer
    // void printSummary();
    
    // Load pretrained model from JSON file
    // void loadWeightsFromFile(JSONFile file);
    
    // Infer model on image and produce output, returns the most confident integer
    // int infer(Image img);
};
