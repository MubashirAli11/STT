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

#include "hmm_trainer.hpp"
using namespace marfix_stt;

HmmTrainer::HmmTrainer(std::string db_path): lm1_(db_path)
{
}


void HmmTrainer::LoadData()
{
    hmm_.LoadData();
}



std::unordered_map<std::string, std::unordered_map<std::string, double>> HmmTrainer::TrainTransitionProbabilities(std::string word, std::vector<std::string> phonemes, std::vector<std::vector<double>> mlp_probabilities)
{
    bw_.Initializations(word, phonemes, mlp_probabilities);

    for (size_t i = 0; i < phonemes.size(); i++) {
        for (size_t j = 0; j < phonemes.size(); j++) {

            transition_probabilities_[phonemes[i]][phonemes[j]] = bw_.CalculateForwardBackwardProbabilities(phonemes[i], phonemes[j]);;

        }
    }

    LmdbStream::WriteTransitionProbability(lm1_, word_, phonemes, transition_probabilities_);

    return transition_probabilities_;
}

std::unordered_map<std::string, std::unordered_map<std::string, double>> HmmTrainer::TrainEmissionProbabilities(std::string word, std::vector<std::string> phonemes, std::vector<std::vector<double>> mlp_probabilities)
{
    bw_.Initializations(word, phonemes, mlp_probabilities);
    std::unordered_map<std::string, std::unordered_map<std::string, double>> emission_probabilities;
    return emission_probabilities;
}

