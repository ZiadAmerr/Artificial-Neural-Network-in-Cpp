//
//  NeuralNetwork.cpp
//  Project
//
//  Created by Ziad Amerr on 04/12/2022.
//
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <filesystem>
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
        void setActivation(double activation) {
            this->activation = activation;
        }
    };
    vector<vector<Neuron>> neurons;
    void _calcActivation(Neuron myNeuron, function<double(double)> activationFunction) {
        if(myNeuron.getLayerId() == 0) {
            cerr << "ERROR DO NOT TRY TO CALC ACTIVATION OF NEURON IN FIRST LAYER" << endl;
            return;
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
        
        double z = _dot(weights, previousActivations);
        
        z = activationFunction(z);
        
        myNeuron.setActivation(z);
    }
    double _dot(vector<double> weights, vector<double> activations) {
        double activation = 0;
        for(int i=0; i<weights.size(); i++)
            activation += weights.at(i)*activations.at(i);
        
        return activation;
    }
//     vector<double> layerActivation(vector<Neuron> neurons) {
//        for neuron in neurons:
//            neuron.activation = getActivation(neuron)
//    }
//
//    for i in range(4):
//        layerActivation()
    void _computeLayerActivation(int layerIdx, function<double(double)> activationFunction) {
        Neuron myNeuron;
        for(int i=0; i<neurons.at(layerIdx).size(); i++)
            _calcActivation(neurons.at(layerIdx).at(i), activationFunction);
    };
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
    void _initializeModel(vector<double> flattenedImage) {
        if(flattenedImage.size() != neurons.at(0).size()) {
            cerr << "FLATTENED IMAGE SIZE SHOULD BE EQUAL TO NUMBER OF NEURONS IN FIRST LAYER" << endl;
            cerr << "SHAPES " << flattenedImage.size() << " AND " << neurons.at(0).size() << " DO NOT MATCH" << endl;
            exit(1);
            return;
        }
        for(int i=0; i<neurons.at(0).size(); i++)
            neurons.at(0).at(i).setActivation(flattenedImage.at(i));
    }
    static double _relu(double x) {
        if(x > 0)
            return x;
        else
            return 0;
    }
    void _computeLastLayer() {
        vector<double> lastActivations;
        int indexOfLastLayer = int(neurons.size()-1);
        for(int i=0; i<neurons.at(indexOfLastLayer).size(); i++) {
            lastActivations.push_back(neurons.at(indexOfLastLayer).at(i).getActivation());
        }
        
        vector<double> finalActivations = _softmax(lastActivations);
        _printVector(finalActivations);
        for(int i=0; i<finalActivations.size(); i++)
            neurons.at(indexOfLastLayer).at(i).setActivation(finalActivations.at(i));
    }
    vector<double> _softmax(vector<double> a) {
        double exp_sum = 0;
        for(int i=0; i<a.size(); i++) {
            exp_sum += exp(a.at(i));
        }
        vector<double> activations;
        for(int i=0; i<a.size(); i++) {
            activations.push_back(exp(a.at(i))/exp_sum);
        }
        return activations;
    }
    void _printVector(vector<double> v) {
        for(int i=0; i<v.size(); i++)
            cout << v.at(i) << " ";
        cout << endl;
    }
    static double _same(double x) {
        return x;
    }
public:
    NeuralNetwork(vector<int> neuronsPerLayer) {
        if(neuronsPerLayer.size() < 3) {
            cerr << "Error! The designed neural network has to have at least 3 layers";
            exit(1);
        }
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
    void printSummary() {
        for(int layerIdx=0; layerIdx<neurons.size(); layerIdx++) {
            cout << "Layer " << layerIdx << " has " << neurons.at(layerIdx).size() << " neurons." << endl;
        }
    };
    
    // ************************* PHASE 2 *************************
    int predict(vector<vector<double>> image) {
        vector<double> flattenedImage;
        for(int i=0; i<image.size(); i++)
            for(int j=0; j<image.at(i).size(); j++)
                flattenedImage.push_back(image.at(i).at(j));
        
        _initializeModel(flattenedImage);
        
        for(int i=1; i<neurons.size()-1; i++) {
            _computeLayerActivation(i, _relu);
        }
        _computeLayerActivation(int(neurons.size()-1), _same);
        _computeLastLayer();
        
        // GET ARGMAX AND RETURN IT AS INTEGER ***************
        
        return 0;
    }
    
    // ************************* PHASE 2 *************************
    // Load pretrained model from JSON file
    // void loadWeightsFromFile(JSONFile file);

    // ************************* PHASE 2 *************************
    // Load pretrained model from JSON file
    vector<string> loadWeightsFromFile(const char* path) {
        // Open file from path
        ifstream myFile(path);
        
        vector<string> fileAsString;
        string line;
        
        if(myFile) {
            while(true) {
                myFile >> line;
                if(myFile.eof())
                    break;
                fileAsString.push_back(line);
            };
        } else {
            perror(path);
        };
        for(int i=0; i<fileAsString.size(); i++) {
            cout << i << ": " << fileAsString.at(i) << endl;
        }
        return fileAsString;
    };
    void split (string str, char seperator, string myList[]) {
        int currIndex = 0, i = 0;
        int startIndex = 0, endIndex = 0;
        string subStr;
        while (i <= str.length()) {
            if (str[i] == seperator || i == str.length()) {
                endIndex = i;
                subStr = "";
                subStr.append(str, startIndex, endIndex - startIndex);
                myList[currIndex] = subStr;
                currIndex += 1;
                startIndex = endIndex + 1;
            }
            i++;
        }
    }
};
