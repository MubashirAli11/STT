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

#ifndef FORWARDLIKELIHOOD__HPP
#define FORWARDLIKELIHOOD__HPP

#include<vector>
#include<iostream>
#include<string>
#include<unordered_map>
#include<map>

#include "hidden_markov_model.hpp"

namespace marfix_stt {
    class ForwardLikelihood {
    private:
        /**
         * @brief hold all the forward probabilities for one word ...
         *
         */
        std::unordered_map<std::string, double> forward_probabilities_;

        HiddenMarkovModel hmm_;

        std::string word_;

    public:
        //// calculate forward probabilities one word at a time


        void CalculateForwardProbabilities(std::string word, std::vector<std::string> phonemes, std::vector<std::vector<double>> mlp_probabilities);


        //// Getters and Setters

        void ForwardProbabilities(std::unordered_map<std::string, double> forward_probabilities)
        {
            this->forward_probabilities_ = forward_probabilities;
        }

        std::unordered_map<std::string, double> GetForwardProbabilities()
        {
            return this->forward_probabilities_;
        }
    };
}

#endif // FORWARDLIKELIHOOD__HPP
