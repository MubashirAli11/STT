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

#ifndef BACKWARDLIKELIHOOD_HPP
#define BACKWARDLIKELIHOOD_HPP

#include<vector>
#include<iostream>
#include<string>
#include<unordered_map>

#include "hidden_markov_model.hpp"

namespace marfix_stt {
    class BackwardLikelihood {
    private:
        /**
         * @brief stored backward probabilities of hmm model use in baum welch training...
         *
         */
        std::unordered_map<std::string, double> backward_probabilities_;
        HiddenMarkovModel hmm_;
        std::string word_;
    public:

        void CalculateBackwardProbabilities(std::string word, std::vector<std::string> phonemes, std::vector<std::vector<double>> mlp_probabilities);


        //// Setters and Getters

        void BackwardProbabilities(std::unordered_map<std::string, double> backward_probabilities)
        {
            this->backward_probabilities_ = backward_probabilities;
        }

        std::unordered_map<std::string, double> BackwardProbabilities()
        {
            return this->backward_probabilities_;
        }
    };
}

#endif // BACKWARDLIKELIHOOD_HPP
