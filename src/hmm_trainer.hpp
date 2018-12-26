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

#ifndef HMMTRAINER_HPP
#define HMMTRAINER_HPP

#include<vector>
#include<iostream>
#include<string>
#include<unordered_map>
#include<map>

#include "hidden_markov_model.hpp"
#include "forward_likelihood.hpp"
#include "backward_likelihood.hpp"
#include "baum_welch.hpp"
#include "stt_common.hpp"

namespace marfix_stt {
    class HmmTrainer {
    private:
        HiddenMarkovModel hmm_;
        BaumWelch bw_;
        std::string word_;

        std::unordered_map<std::string, std::unordered_map<std::string, double>> transition_probabilities_;

        Lmdb lm1_;


    public:

        HmmTrainer(std::string db_path);
        void LoadData();

        std::unordered_map<std::string, std::unordered_map<std::string, double>> TrainTransitionProbabilities(std::string word, std::vector<std::string> phonemes, std::vector<std::vector<double>> mlp_probabilities);

        std::unordered_map<std::string, std::unordered_map<std::string, double>> TrainEmissionProbabilities(std::string word, std::vector<std::string> phonemes, std::vector<std::vector<double>> mlp_probabilities);


        ///Getters and Setters

        void TransitionProbabilities(std::unordered_map<std::string, std::unordered_map<std::string, double>> transition_probabilities)
        {
            this->transition_probabilities_ = transition_probabilities;
        }
        std::unordered_map<std::string, std::unordered_map<std::string, double>> GetTransitionProbabilities()
        {
            return this->transition_probabilities_;
        }

    };
}

#endif // HMMTRAINER__HPP
