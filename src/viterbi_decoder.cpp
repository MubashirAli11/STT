#include "viterbi_decoder.hpp"



std::vector<std::string>marfix_stt::ViterbiDecoder::CalculateViterbiProbabilties(std::vector<std::string> phonemes, std::vector<std::vector<double>> mlp_probabilities)
{
    path_.clear();
    viterbi_probabilities_.clear();
    hmm_.AssignPhonemeStates(phonemes);
    hmm_.AssignInitialProbabilities();
    hmm_.AssignFinalProbabilities();
    hmm_.AssignTransitionProbabilities();
    mlp_probabilities = marfix_stt::HybridApproach::GiveScaledEmissionProbability(mlp_probabilities);
    hmm_.AssignEmissionProbabilities(mlp_probabilities);
    int index;
    int probability_list_index;
    int difference;
    int states_index;
    int max_value_index;
    std::string temp_str;
    double probabilities;
    std::string last_state;
    std::unordered_map<std::string, std::string> b_ptr;
    std::vector<double> probabilities_list;
    std::multimap<double, int> sort_prob;
    std::multimap<double, int>::iterator itr;
    std::multimap<double, int>::iterator itr2;
    std::vector<double> hold_values;
    std::multimap<double, int> final_state_prob;
    std::vector<std::string> observations = hmm_.GetObservations();


    for (size_t i = 0; i < hmm_.GetStates().size(); i++) {
        probabilities_list.push_back(hmm_.GetInitialProbabilities()[hmm_.GetStates()[i]]*hmm_.GetEmissionProbabilities()[hmm_.GetStates()[i]][observations[0]]);
    }

    for (size_t i = 0; i < hmm_.GetStates().size(); i++) {
        viterbi_probabilities_.insert(std::make_pair(hmm_.GetStates()[i] + "|" + observations[0], probabilities_list[i]));
    }

    observations.erase(observations.cbegin());

    for (size_t i = 0; i < observations.size(); i++) {
        states_index = 0;

        for (size_t j = 0; j < hmm_.GetStates().size(); j++) {
            probability_list_index = 0;
            difference = 0;

            for (size_t k = 0; k < hmm_.GetStates().size(); k++) {
                probabilities = hmm_.GetTransitionProbabilities()[hmm_.GetStates()[k]][hmm_.GetStates()[j]] * hmm_.GetEmissionProbabilities()[hmm_.GetStates()[j]][observations[i]];
                probabilities *= probabilities_list[probability_list_index];
                probabilities_list.push_back(probabilities);
                sort_prob.insert(std::make_pair(probabilities, probability_list_index++));
                last_state = hmm_.GetStates()[j];
            }

            difference = probabilities_list.size() - hmm_.GetStates().size();
            itr = sort_prob.end();
            --itr;
            max_value_index = itr->second;
            max_value_index += difference;
            b_ptr.insert(std::make_pair(hmm_.GetStates()[states_index] + "|" + observations[i], hmm_.GetStates()[itr->second]));
            viterbi_probabilities_.insert(std::make_pair(hmm_.GetStates()[states_index++] + "|" + observations[i], probabilities_list[max_value_index]));
            hold_values.push_back(probabilities_list[max_value_index]);
            sort_prob.clear();
        }

        probabilities_list.clear();
        difference = 0;

        for (size_t n = 0; n < hmm_.GetStates().size(); n++) {
            probabilities_list.push_back(hold_values[n]);
        }

        hold_values.clear();
    }

    sort_prob.clear();

    index = observations.size() - 1;

    for (size_t i = 0; i < hmm_.GetStates().size(); i++) {
        final_state_prob.insert(std::make_pair(viterbi_probabilities_[hmm_.GetStates()[i] + "|" + observations[index]]*hmm_.GetFinalProbabilities()[hmm_.GetStates()[i]], i));
    }

    itr2 = final_state_prob.end();
    itr2--;

    viterbi_probabilities_.insert(std::make_pair("final state", itr2->first));


    path_.push_back(hmm_.GetStates()[itr2->second]);
    temp_str = hmm_.GetStates()[itr2->second];

    for (int i = observations.size() - 1; i >= 0; i--) {
        temp_str = b_ptr[temp_str + "|" + observations[i]];
        path_.push_back(temp_str);
    }

    std::vector<std::string> c_path;
    std::copy(path_.rbegin(), path_.rend(), std::back_inserter(c_path));

    return c_path;
}
