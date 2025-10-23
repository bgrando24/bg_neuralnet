#include <iostream>
#include <spdlog/spdlog.h>
#include <vector>
// spdlog::info("Hello from spdlog!");

/**
    * Basic building blocks
       * Activation function + its derivative for back-propagation (struct?)
       * Inputs: feature vector of numerical values
       * Perceptrons: We will assume dense layers, receives M inputs, produces N outputs, weights can be a matrix of M x N size

    * Basic structure:
       * Input layer: can this just be the raw feature vector that feeds into the first hidden layer? No transformations are done on the input layer
       * Hidden layer: array of N neurons, receives inputs from M number inputs from previous layer -> for each neuron in the next layer, provide output value + weight
       * Connections: How to model these? Which neuron do the weights 'belong' to, the input or output?
       * Output layer: Needs to output raw values, do we apply activation function here too? I think so
*/

// Defines the structure of a given activation function, provides both the base function and its derivative
struct ActivationFunction
{
    // std::function is any callable object (function/method)
    // syntax is: <return-type(argument-type)>
    std::function<double(double)> f;  // activation function itself
    std::function<double(double)> df; // derivative of activation function for back-propagation
};

// Models a single perceptron unit
class Perceptron
{
private:
    double bias;

public:
    ActivationFunction activation;

    Perceptron(double start_bias, ActivationFunction activation)
    {
        this->bias = start_bias;
        this->activation = activation;
    }
};

int main()
{

    return 0;
}