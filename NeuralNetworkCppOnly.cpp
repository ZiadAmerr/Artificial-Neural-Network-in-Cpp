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
        void addBackwardArrow(int prevNeuronId) {
            backwardArrowList.push_back(Arrow(prevNeuronId, 0));
        }
        void printArrowList(string direction="forward") {
            cout << '[';
            for(auto it = backwardArrowList.begin(); it != backwardArrowList.end(); it++)
                cout << "N#" << it->getNextNeuronId() << "(" << it->getWeight() <<"), ";
            cout << ']';
        }
        int getLayerId() {
            return layerId;
        }
        void setActivation(double activation) {
            this->activation = activation;
        }
        // ********* UNFINISHED *********
        void setWeights(vector<double> weights) {
            if(weights.size() != backwardArrowList.size()) {
                cerr << "CAN NOT USE WEIGHTS FOR NEURON, DIM MISMATCH.";
                exit(1);
            }
            for(int i=0; i<weights.size(); i++)
                backwardArrowList.at(i).setWeight(weights.at(i));
        }
    };
    vector<vector<Neuron>> neurons;
    
    // Neuron and layer handling
    Neuron _getNeuron(int neuronId, int layerIdx) {
        Neuron n;
        for (int i = 0; i < neurons.size(); i++) {
            n = neurons.at(layerIdx).at(i);
            if (n.getNeuronId() == neuronId)
                return n;
        }
        
        // If not found
        cerr << "Error! Neuron not found!" << endl;
        exit(1);
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
    static double _relu(double x) {
        if(x > 0)
            return x;
        else
            return 0;
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
    
    // Weights handling
    double _dot(vector<double> weights, vector<double> activations) {
        double activation = 0;
        for(int i=0; i<weights.size(); i++)
            activation += weights.at(i)*activations.at(i);
        
        return activation;
    }
    vector<double> _strToDouble(vector<string> v) {
        vector<double> doubleVector(v.size());
        transform(v.begin(), v.end(), doubleVector.begin(), [] (const string& val) {
            return stod(val);
        });
        return doubleVector;
    }
    vector<vector<double>> _reshape(int dim, vector<double> v) {
        vector<vector<double>> myVec;
        vector<double> temp;
        for(int i=1; i<=v.size(); i++) {
            temp.push_back(v.at(i-1));
            if(i%dim == 0) {
                myVec.push_back(temp);
                temp.clear();
            };
        };
        return myVec;
    };
    vector<vector<double>> _getWeightsMatrix(const char* path, int dim) {
        vector<double> weightsVector = _strToDouble(_loadWeightsFromFile(path));
        return _reshape(dim, weightsVector);
    };
    void _setLayerWeights(vector<vector<double>> W, int layerIdx) {
        int n_neurons = int(neurons.at(layerIdx).size());
        if(n_neurons != W.size()) {
            cerr << "DIMENSION MISMATCH! N NEURONS DIFFERENT THAN WEIGHTS MATRIX" << endl;
            cerr << "N neurons = " << n_neurons << "\nW size = " << W.size() << endl;
            exit(1);
        }
        for(int i=0; i<n_neurons; i++) {
            neurons.at(layerIdx).at(i).setWeights(W.at(i));
        }
    }
    
    // Activations handling
    vector<int> _flatten(vector<vector<int>> image) {
        vector<int> flattenedImage;
        for(int i=0; i<image.size(); i++)
            for(int j=0; j<image.at(i).size(); j++)
                flattenedImage.push_back(image.at(i).at(j));
        return flattenedImage;
    }
    vector<double> _normalize(vector<int> flattenedImage) {
        vector<double> normalized;
        for(int i=0; i<flattenedImage.size(); i++) {
            normalized.push_back(double(flattenedImage.at(i))/255.0);
        }
        return normalized;
    }
    int _getArgmax() {
        double maxActivation=-1, activation;
        int argmax = 0;
        int lastLayerIdx = int(neurons.size()-1);
        for(int i=0; i<neurons.at(lastLayerIdx).size(); i++) {
            activation = neurons.at(lastLayerIdx).at(i).getActivation();
            if(activation > maxActivation) {
                maxActivation = activation;
                argmax = i;
            };
        };
        return argmax;
    }
    
    // File handling
    vector<string> _loadWeightsFromFile(const char* path) {
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
        return fileAsString;
    };
    vector<string> _loadWeightsFromFile(string path_str) {
        return _loadWeightsFromFile(path_str.c_str());
    };
    vector<int> _loadImageFromFile(string path_str) {
        const char* path = path_str.c_str();
        // Open file from path
        ifstream myFile(path);
        
        vector<string> fileAsString;
        vector<int> fileAsInt;
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
            fileAsInt.push_back(stoi(fileAsString.at(i)));
        };
        
        return fileAsInt;
    };
    
    // Model handling
    void _computeLastLayer() {
        vector<double> lastActivations;
        int indexOfLastLayer = int(neurons.size()-1);
        for(int i=0; i<neurons.at(indexOfLastLayer).size(); i++) {
            lastActivations.push_back(neurons.at(indexOfLastLayer).at(i).getActivation());
        }
        
        vector<double> finalActivations = _softmax(lastActivations);
        // _printVector(finalActivations);
        for(int i=0; i<finalActivations.size(); i++)
            neurons.at(indexOfLastLayer).at(i).setActivation(finalActivations.at(i));
    };
    void _calcActivation(Neuron& myNeuron, function<double(double)> activationFunction) {
        if(myNeuron.getLayerId() == 0) {
            cerr << "ERROR DO NOT TRY TO CALC ACTIVATION OF NEURON IN FIRST LAYER" << endl;
            exit(1);
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
        
        myNeuron.setActivation(z);
    }
    void _computeLayerActivation(int layerIdx, function<double(double)> activationFunction) {
        for(int i=0; i<neurons.at(layerIdx).size(); i++)
            _calcActivation(neurons.at(layerIdx).at(i), activationFunction);
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
    int _predict(vector<int> image) {
        // Flatten image then normalize it
        vector<double> normalized = _normalize(image);
        
        // Initialize model with image
        _initializeModel(normalized);
        
        // Forward pass
        for(int i=1; i<neurons.size()-1; i++) {
            _computeLayerActivation(i, _relu);
        }
        
        // Last layer activations
        _computeLayerActivation(int(neurons.size()-1), _same);
        
        // Apply softmax
        _computeLastLayer();
        
        // GET ARGMAX AND RETURN IT AS INTEGER ***************
        return _getArgmax();
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
    int infer(string path) {
        vector<int> image = _loadImageFromFile(path);
        return _predict(image);
    }
    void printActivations(int layerIdx) {
        if(layerIdx >= neurons.size() or layerIdx < 0) {
            cerr << "Layer ID invalid" << endl;
            exit(1);
        }
        for(int i=0; i<neurons.at(layerIdx).size(); i++) {
            cout << neurons.at(layerIdx).at(i).getActivation() << " ";
        }
        cout << endl;
    }
    void loadPretrainedModel(string stringPath) {
        string path_temp;
        const char* path;
        for(int i=1; i<neurons.size(); i++) {
            path_temp = stringPath + "weights" + to_string(i) + ".weights";
            path = path_temp.c_str();
            vector<vector<double>> W = _getWeightsMatrix(path, int(neurons.at(i-1).size()));
            _setLayerWeights(W, i);
        }
        
    };
};
