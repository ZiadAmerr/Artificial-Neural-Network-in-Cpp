//
//  NeuralNetwork.cpp
//  Project
//
//  Created by Ziad Amerr on 04/12/2022.
//
#include <iostream>
#include <vector>
#include <math.h>
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
        
        // ************************* PHASE 2 *************************
        // vector<Arrow> forwardArrowList;
        // vector<Arrow> backwardArrowList;
        
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
                
                // currentNeuron.addArrow(otherNeuron.getId())
                neurons.at(firstLayerId).at(i).addArrow(neurons.at(firstLayerId+1).at(j).getNeuronId());
            };
        }
    };
    
public:
    class Activations {
    public:
        static double Sigmoid(double z) {
            return 1.0 / (1.0 + exp(-z));
        }
        
        static double ReLU(double z) {
            if (z < 0)
                return 0;
            else
                return z;
        }
        
        static double Linear(double z) {
            return z;
        }
        
        static double Step(double z) {
            if (z < 0)
                return 0;
            else
                return 1;
        }
        
        static double LeakyReLU(double z, double negativeSlope) {
            return z > 0 ? z : negativeSlope * z;
        }
    };
    
    NeuralNetwork(vector<int> neuronsPerLayer) {
        for(int i=0; i<neuronsPerLayer.size(); i++)
            _initializeLayer(neuronsPerLayer.at(i), i);
        
        for(int i=0; i<neuronsPerLayer.size()-1; i++)
            _connectLayers(i);
    }
    
    void printNetwork(string detailed = "undetailed") {
        Neuron n;
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
};




