/*
 * Copyright 2016 <copyright holder> <email>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef MULTILAYERPERCEPTRON__HPP
#define MULTILAYERPERCEPTRON__HPP

#include <functional>
#include<vector>
#include <random>
#include<iostream>
#include "matrix.hpp"
#include "activation_functions.hpp"


namespace marfix_stt {
    /**
     * @brief ...
     * This Class builds a neural net with the specified hidden layers and neurons in them, It also trains the neural net on the specified input. The learning is supervised, therefore output is also require with every input
     */
    class MultilayerPerceptron {
    public:

        /**
         * @brief ...
         * Initializations of input, output ans synapses
         * @param training_input p_training_input:...The Input for the MLP
         * @param training_output p_training_output:...The Output for the MLP
         * @param hidden_layers p_hidden_layers:...Number of hidden layer
         * @param hidden_neurons_each_layer p_hidden_neurons_each_layer:...Number of neurons in each layer
         */
        MultilayerPerceptron(std::vector<std::vector<double>> training_input, std::vector<std::vector<double>> training_output, unsigned long hidden_layers, std::vector<unsigned long> hidden_neurons_each_layer);

        /**
         *@brief ...
         * This function performs the actual training of the neural net with specified input and output
         * @param iterations p_iterations:... The number of iterations for learning
         * @param f_activation_function_ p_f_activation_function_:... The Activation function Pointer
         */
        void Learn(unsigned long iterations, std::function<std::vector<std::vector<double>>(ActivationFunctions&, std::vector<std::vector<double>>, bool)> f_activation_function_);
        /**
             * @brief ...
             * This function returns an output of the neural net on the given input
             * @param input p_input:... The input vector
             */
        void Test(std::vector<std::vector<double>> input);

    private:
        std::vector<std::vector<double>> input_;
        std::vector<std::vector<double>> output_;
        std::vector<std::vector<std::vector<double>>> synapses_;
        unsigned long hidden_layers_;
        std::vector<unsigned long> hidden_neurons_each_layer_;
        std::function<std::vector<std::vector<double>>(ActivationFunctions&, std::vector<std::vector<double>>, bool)> f_activation_function_;
        MatrixOperations matrix_operations;
    };

}
#endif // MULTILAYERPERCEPTRON__HPP
