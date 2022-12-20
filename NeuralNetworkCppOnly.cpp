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
        // ************************* PHASE 2 *************************
        vector<Arrow> forwardArrowList;
        vector<Arrow> backwardArrowList;
        
        
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
        double getActivation() {
            return activation;
        }
        vector<Arrow> getForwardArrowList() {
            return forwardArrowList;
        }
        vector<Arrow> getBackwardArrowList() {
            return backwardArrowList;
        }
        vector<double> getConnectedWeights() {
            vector<double> weights;
            for(auto it = backwardArrowList.begin(); it != backwardArrowList.end(); it++) {
                weights.push_back(it->getWeight());
            }
            return weights;
        }
        void addForwardArrow(int nextNeuronId) {
            forwardArrowList.push_back(Arrow(nextNeuronId, 0));
        }
        void addBackwardArrow(int prevNeuronId) {
            backwardArrowList.push_back(Arrow(prevNeuronId, 0));
        }
        void printArrowList(string direction="forward") {
            vector<Arrow> arrowList = (direction == "forward") ? forwardArrowList : backwardArrowList;
            cout << '[';
            for(auto it = arrowList.begin(); it != arrowList.end(); it++)
                cout << "N#" << it->getNextNeuronId() << ", ";  // << "(" << it->getWeight() <<")
            cout << ']';
        }
        int getLayerId() {
            return layerId;
        }
    };
    
    vector<vector<Neuron>> neurons;
    
    double _calcActivation(Neuron myNeuron) {
        if(myNeuron.getLayerId() == 0) {
            cerr << "ERROR DO NOT TRY TO CALC ACTIVATION OF NEURON IN FIRST LAYER" << endl;
            return 0;
        }
        
        // Our vectors
        vector<double> weights;
        vector<double> previousActivations;
        int currentLayerId = myNeuron.getLayerId();
        
        
        
        weights = myNeuron.getConnectedWeights();
        
        // Let's loop through all neurons in the PREVIOUS layer
        for(int i=0; i<neurons.at(currentLayerId-1).size(); i++) {
            previousActivations.push_back(neurons.at(currentLayerId-1).at(i).getActivation());
        }
        
        
        return _dot(weights, previousActivations);
    }
    
    double _dot(vector<double> weights, vector<double> activations) {
        double activation = 0;
        for(int i=0; i<weights.size(); i++)
            activation += weights.at(i)*activations.at(i);
        
        return activation;
    }
    
//        vector<double> layerActivation(vector<Neuron> neurons) {
//            for neuron in neurons:
//                neuron.activation = getActivation(neuron)
//        }
//
//        for i in range(4):
//            layerActivation()
    
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
        
        for(int i=0; i<numberOfNeurons; i++)
            myVec.push_back(Neuron(i, layerIdx));
        
        neurons.push_back(myVec);
    }
    void _connectLayers(int currentLayerId) {
//        // Loop through the current layers neurons
//        for(int i=0; i<neurons.at(currentLayerId).size()-1; i++) {
//
//            // Connect each neuron with ALL the neurons in the NEXT layer
//            for(int j=0; j<neurons.at(currentLayerId+1).size(); j++) {
//
//                // currentNeuron.addForwardArrow(otherNeuron.getId())
//                neurons.at(currentLayerId).at(i).addForwardArrow(neurons.at(currentLayerId+1).at(j).getNeuronId());
//            };
//        };
        
        for(int i=0; i<neurons.at(currentLayerId).size(); i++) {
        
            // Connect each neuron with ALL the neurons in the PREVIOUS layer
            for(int j=0; j<neurons.at(currentLayerId-1).size(); j++) {
                
                // currentNeuron.addBackwardArrow(otherNeuron.getId())
                neurons.at(currentLayerId).at(i).addBackwardArrow(neurons.at(currentLayerId-1).at(j).getNeuronId());
            };
        };
    };
    
public:
    NeuralNetwork(vector<int> neuronsPerLayer) {
        for(int i=0; i<neuronsPerLayer.size(); i++)
            _initializeLayer(neuronsPerLayer.at(i), i);
        
        for(int i=1; i<neuronsPerLayer.size(); i++) {
            _connectLayers(i);
        }
            
    }
    
    void printNetwork(string detailed="none") {
        Neuron n;
        for(int i=0; i<neurons.size(); i++) {
            cout << "Layer " << i << endl;
            for(int j=0; j<neurons.at(i).size(); j++) {
                n = neurons.at(i).at(j);
                cout << "  ";
                
                if(detailed == "backward" and i != 0) {
                    n.printArrowList("backward");
                    cout << "-->";
                };
                
                cout << "N#" << n.getNeuronId();
                
                
                if(detailed == "forward") {
                    cout << "-->";
                    n.printArrowList("forward");
                };
                if(detailed == "backward") {
                    if(i!=0) {
                        cout << endl;
                    }
                }
            }
            cout << endl;
        }
    }
    
    // Prints summary of the network, n_layers, n_neurons per layer
    void printSummary() {
        for(int layerIdx=0; layerIdx<neurons.size(); layerIdx++) {
            cout << "Layer " << layerIdx << " has " << neurons.at(layerIdx).size() << " neurons." << endl;
        }
    };
    
    // ************************* PHASE 2 *************************
    // Load pretrained model from JSON file
    // void loadWeightsFromFile(JSONFile file);

    // ************************* PHASE 2 *************************
    // Infer model on image and produce output, returns the most confident integer
    // int infer(Image img);
};
