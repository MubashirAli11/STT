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

#include "multilayerperceptron.hpp"

using namespace marfix_stt;

namespace {
    double getRandomNumber(double min, double max)
    {
        std::random_device rd;
        std::mt19937_64 ed(rd());
        std::uniform_real_distribution<> dist(min, max);
        double random = dist(ed);
        return random;
    }
}

marfix_stt::MultilayerPerceptron::MultilayerPerceptron(std::vector<std::vector<double>> training_input, std::vector<std::vector<double>> training_output, unsigned long hidden_layers, std::vector<unsigned long> hidden_neurons_each_layer)
{

    input_ = training_input;
    output_ = training_output;
    hidden_layers_ = hidden_layers;
    hidden_neurons_each_layer_ = hidden_neurons_each_layer;

    //build initial synapes
    for (size_t i = 0; i < hidden_layers_ + 1; i++) {
        std::vector<std::vector<double>> synapei;
        unsigned long synape_rows, synape_columns;

        if (i == 0) {
            synape_rows = input_[0].size();
            synape_columns = hidden_neurons_each_layer_[0];
        }

        else if (i == hidden_layers_) {
            synape_rows = hidden_neurons_each_layer_[i - 1];
            synape_columns = output_[0].size();
        }

        else {
            synape_rows = hidden_neurons_each_layer_[i - 1];
            synape_columns = hidden_neurons_each_layer_[i];
        }

        for (size_t i = 0; i < synape_rows; i++) {
            std::vector<double> temp;

            for (size_t j = 0; j < synape_columns; j++) {
                temp.push_back(getRandomNumber(-0.5, 0.5));
            }

            synapei.push_back(temp);
        }

        synapses_.push_back(synapei);

    }
}

void marfix_stt::MultilayerPerceptron::Learn(unsigned long iterations, std::function<std::vector<std::vector<double>>(ActivationFunctions&, std::vector<std::vector<double>>, bool)> activation_function)
{
    f_activation_function_ = activation_function;
    std::vector<std::vector<std::vector<double>>> layers;
    std::vector<std::vector<std::vector<double>>> layers_error;
    std::vector<std::vector<std::vector<double>>> layers_delta;
    ActivationFunctions acf;

    for (size_t i = 0; i < iterations; i++) {
        layers.clear();
        layers.push_back(input_);

        for (size_t j = 0; j < hidden_layers_ + 1; j++) {
            layers.push_back(matrix_operations.DotMultiply(layers[j], synapses_[j]));
            layers[layers.size() - 1] = f_activation_function_(acf, layers[layers.size() - 1], false);
        }

        layers_error.clear();
        layers_error.push_back(matrix_operations.Subtract(output_, layers[layers.size() - 1]));

        if (i % 10000 == 0) {
            std::cout << "Error=" << matrix_operations.Mean(matrix_operations.Absolute(layers_error[layers_error.size() - 1])) << std::endl;
        }

        layers_delta.clear();
        layers_delta.push_back(matrix_operations.Multiply(layers_error[layers_error.size() - 1], f_activation_function_(acf, layers[layers.size() - 1], true)));

        unsigned long si = synapses_.size() - 1;
        unsigned long li = layers.size() - 2;

        for (size_t j = 0; j < hidden_layers_; j++) {

            layers_error.push_back(matrix_operations.DotMultiply(layers_delta[j], matrix_operations.Transpose(synapses_[si])));

            layers_delta.push_back(matrix_operations.Multiply(layers_error[layers_error.size() - 1], f_activation_function_(acf, layers[li], true)));
            si--;
            li--;
        }

        unsigned long ldi = 0;

        for (size_t j = synapses_.size() - 1; j > 0; j--) {
            matrix_operations.DotMultiplyAdd(matrix_operations.Transpose(layers[j]), layers_delta[ldi], synapses_[j]);
            ldi++;
        }
    }
}

void marfix_stt::MultilayerPerceptron::Test(std::vector<std::vector<double>> input)
{
    std::vector<std::vector<std::vector<double>>> layers;
    ActivationFunctions acf;
    layers.push_back(input);

    for (size_t j = 0; j < hidden_layers_ + 1; j++) {
        layers.push_back(matrix_operations.DotMultiply(layers[j], synapses_[j]));
        layers[layers.size() - 1] = f_activation_function_(acf, layers[layers.size() - 1], false);
    }

    for (size_t i = 0; i < layers[layers.size() - 1].size(); i++) {
        for (size_t j = 0; j < layers[layers.size() - 1][0].size(); j++) {
            std::cout << layers[layers.size() - 1][i][j];
        }

        std::cout << std::endl;
    }
}
