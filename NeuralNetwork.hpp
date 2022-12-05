//
//  NeuralNetwork.hpp
//  Project
//
//  Created by Ziad Amerr on 05/12/2022.
//

#ifndef NeuralNetwork_hpp
#define NeuralNetwork_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

class NeuralNetwork {
private:
    
    
    class Neuron {
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
        
        int neuronId, layerId;
        double activation;
        vector<Arrow> arrowList;
        
        // ************************* PHASE 2 *************************
        // vector<Arrow> forwardArrowList;
        // vector<Arrow> backwardArrowList;
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
    };
    
    
    
    vector<vector<Neuron>> neurons;
    
    bool _checkIfNeuronExists(int neuronId, int layerIdx);
    
    Neuron _getNeuron(int neuronId, int layerIdx);
    
    void _initializeLayer(int numberOfNeurons, int layerIdx);
    
    void _connectLayers(int firstLayerId);
    
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
    
    NeuralNetwork(vector<int> neuronsPerLayer);
    
    void printNetwork(string detailed = "undetailed");
    
    
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


#endif /* NeuralNetwork_hpp */
