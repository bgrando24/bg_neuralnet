# BG's NeuralNet

A simple implementation of an Artificial Neural Network from the ground-up, in C++

# Artificial Neural Networks: A crash-course

Artificial Neural Networks (ANN) are a machine learning model inspired by the biological neurons in our brains.

## At its most basic, an ANN is made up from...

-   **Perceptrons (neurons/nodes)**: The fundamental 'unit' of an ANN. A perceptron receives inputs and applies specified functions in order to product an output
-   **Connections (edges/links)**: Connections link together perceptrons. Since ANNs are a graph-based model, these are the edges of a graph
-   **Weights**: Each connection between perceptrons has a _weight_, which is simply a number we can adjust in order to 'tune' the overall network. They represent the '_strength_' of the connection between two perceptrons, again similar to neurons in our brains.
-   **Bias**: A bias belongs to individual perceptrons, and is another number that can be adjusted to 'tune' the overall network. A bias is added to the weighted sum of a perceptron's input values, then the resulting value is passed to the _activation function_.
-   **Activation function**: A mathematical function that takes the weighted sum of the inputs _and_ the bias value, and returns the perceptron's final output value. Typically activation functions 'squeeze' the numerical value into a rane between 0 and 1, or -1 and 1. This in turn represents how 'strongly' the perceptron has fired
-   **Layers**: Perceptrons are grouped together into '_layers_' which help represent the hierarichical processing of the input data. Loosely, a layer can be defined as a set of perceptrons that receive inputs from the same group of previous perceptrons, and pass on their outputs to the same set of succeeding perceptrons. Layers allow the NN to 'learn' increasingly complex features. More layers = more perceptrons, but more isn't always necessarily 'better'.  
-   **Input layer**: The set of perceptrons that recieve the raw, initial input values from the feature vector
-   **Hidden layers**: The proper definition of a hidden layer is "any layer in a NN that is not an input or output layer". In other words, it is a layer of perceptrons that receives input values via the immediately previous layer (which could be either another hidden layer or the input layer), and passes on its output to the next immediate layer (which again could be another hidden layer, or the final output layer)
-   **Output layer**: The set of perceptrons that produce the final output values from the whole NN process, also called "_logits_"


## Common mathematical functions for ANNs
### In perceptrons:
-   **Activation functions**: Used to model the 'strength' of a given perceptron's output
    - _Recitified Linear Unit_ (ReLU): Output is positive if input is positive, otherwise output is zero
    - _(Binary) Step Function_: 'Squashes' the input value so that the output value is one of two possible output values, nothing in between. For example **either** 0 or 1, or **either** -1 or 1
    - _Sigmoid function_: Again 'squashes' the input into a given output range, but this time with a smoothed "S" shaped curve. The output is **not** binary this time, but the gradient between the lower and upper bounds for the output is steep (i.e. favours an output at the lower or upper bound, but also allows for output values in between). 