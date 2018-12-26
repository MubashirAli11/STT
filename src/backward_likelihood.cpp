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
 * limitations under the License.S
 */

#include "backward_likelihood.hpp"

using namespace marfix_stt;
void BackwardLikelihood::CalculateBackwardProbabilities(std::string word, std::vector<std::string> phonemes, std::vector<std::vector<double>> mlp_probabilities)
{
    backward_probabilities_.clear();
    hmm_.AssignPhonemeStates(phonemes);
    hmm_.AssignInitialProbabilities();
    hmm_.AssignFinalProbabilities();
    hmm_.AssignTransitionProbabilities();
    hmm_.AssignEmissionProbabilities(mlp_probabilities);
    word_ = word;
    std::vector<double> probabilities_list;
    std::vector<std::string> observations = hmm_.GetObservations();

    for (size_t i = 0; i < hmm_.GetStates().size(); i++) {
        probabilities_list.emplace_back(hmm_.GetFinalProbabilities()[hmm_.GetStates()[i]]);
        backward_probabilities_.insert(std::make_pair(hmm_.GetStates()[i] + "|" + observations[observations.size() - 1], probabilities_list[i]));
    }

    for (size_t i = observations.size() - 1; i > 0; i--) {
        
        size_t states_index = 0;
        std::vector<double> hold_values;
        
        for (size_t j = 0; j < hmm_.GetStates().size(); j++) {
            size_t probability_list_index = 0;
            size_t difference = 0;

            for (size_t k = 0; k < hmm_.GetStates().size(); k++) {
                double probability = hmm_.GetTransitionProbabilities()[hmm_.GetStates()[j]][hmm_.GetStates()[k]] * hmm_.GetEmissionProbabilities()[hmm_.GetStates()[k]][observations[i]];
                probabilities_list.emplace_back(probability * probabilities_list[probability_list_index++]);
            }

            difference = probabilities_list.size() - hmm_.GetStates().size();
            double select_value_index = 0;

            for (size_t l = 0; l < hmm_.GetStates().size(); l++) {
                select_value_index += probabilities_list[difference++];
            }

            int p = i;
            p--;

            backward_probabilities_.insert(std::make_pair(hmm_.GetStates()[states_index++] + "|" + observations[p], select_value_index));

            hold_values.emplace_back(select_value_index);
        }

        probabilities_list.clear();
      
        for (size_t n = 0; n < hmm_.GetStates().size(); n++) {
            probabilities_list.emplace_back(hold_values[n]);
        }
    }

    double st = 0;

    for (size_t i = 0; i < hmm_.GetStates().size(); i++) {
        st += hmm_.GetInitialProbabilities()[hmm_.GetStates()[i]] * hmm_.GetEmissionProbabilities()[hmm_.GetStates()[i]][observations[0]] * backward_probabilities_[hmm_.GetStates()[i] + "|" + observations[0]];
    }

    backward_probabilities_.insert(std::make_pair("first state", st));
}
