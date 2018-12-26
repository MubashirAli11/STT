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

#include "forward_likelihood.hpp"


void marfix_stt::ForwardLikelihood:: CalculateForwardProbabilities(std::string word, std::vector<std::string> phonemes, std::vector<std::vector<double>> mlp_probabilities)
{
    forward_probabilities_.clear();
    hmm_.AssignPhonemeStates(phonemes);
    hmm_.AssignInitialProbabilities();
    hmm_.AssignFinalProbabilities();
    hmm_.AssignTransitionProbabilities();
    hmm_.AssignEmissionProbabilities(mlp_probabilities);
    word_ = word;
    int probabiity_list_index;
    int difference;
    int states_index;
    double selected_value_index;
    double probability;
    std::vector<double> probabilities_list;
    std::vector<double> hold_values;
    std::vector<std::string> observations = hmm_.GetObservations();

    for (size_t i = 0; i < hmm_.GetStates().size(); i++) {
        probabilities_list.push_back(hmm_.GetInitialProbabilities()[hmm_.GetStates()[i]]*hmm_.GetEmissionProbabilities()[hmm_.GetStates()[i]][observations[0]]);
        forward_probabilities_.insert(std::make_pair(hmm_.GetStates()[i] + "|" + observations[0], probabilities_list[i]));
    }

    observations.erase(observations.cbegin());

    for (size_t i = 0; i < observations.size(); i++) {
        states_index = 0;

        for (size_t j = 0; j < hmm_.GetStates().size(); j++) {
            probabiity_list_index = 0;
            difference = 0;

            for (size_t k = 0; k < hmm_.GetStates().size(); k++) {
                probability = hmm_.GetTransitionProbabilities()[hmm_.GetStates()[k]][hmm_.GetStates()[j]] * hmm_.GetEmissionProbabilities()[hmm_.GetStates()[j]][observations[i]];
                probabilities_list.push_back(probability * probabilities_list[probabiity_list_index++]);
            }

            difference = probabilities_list.size() - hmm_.GetStates().size();
            selected_value_index = 0;

            for (size_t l = 0; l < hmm_.GetStates().size(); l++) {
                selected_value_index += probabilities_list[difference++];
            }

            forward_probabilities_.insert(std::make_pair(hmm_.GetStates()[states_index++] + "|" + observations[i], selected_value_index));
            hold_values.push_back(selected_value_index);
        }

        probabilities_list.clear();

        for (size_t n = 0; n < hmm_.GetStates().size(); n++) {
            probabilities_list.push_back(hold_values[n]);
        }

        hold_values.clear();
    }

    int fn = observations.size() - 1;
    double final_state_prob = 0;

    for (size_t i = 0; i < hmm_.GetStates().size(); i++) {
        final_state_prob += hmm_.GetFinalProbabilities()[hmm_.GetStates()[i]] * forward_probabilities_[hmm_.GetStates()[i] + "|" + observations[fn]];
    }

    forward_probabilities_.insert(std::make_pair("final state", final_state_prob));

}
