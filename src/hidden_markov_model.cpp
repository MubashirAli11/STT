#include "hidden_markov_model.hpp"


void marfix_stt::HiddenMarkovModel::LoadData()
{
    std::cout << "LoadingData" << std::endl;
    std::string ph;
    std::string temp;
    std::vector<std::string> all_words;
    std::string cnt;
    std::vector<std::string> states;
    std::vector<std::string> phonemes_;
    std::unordered_map<std::string, std::unordered_map<std::string, double>> transition_probabilities;
    cnt = "count";
    WordDataset wd_("words");

    for (wd_.SeekToFirst(); wd_.IsValid(); wd_.SeekToNext()) {

        phonemes_.clear();

        phonemes_ = wd_.Phonemes();

        states = AssignPhonemeStates(phonemes_);

        transition_probabilities = AssignTransitionProbabilities();
        Lmdb lm2("UWTP");

        for (size_t i = 0; i < states.size(); i++) {
            for (size_t j = 0; j < states.size(); j++) {

                std::ostringstream serialized;
                boost::archive::text_oarchive oa(serialized);
                oa << transition_probabilities[states[i]][states[j]];
                std::string serialized_data = serialized.str();
                lm2.Put(wd_.GetCurrentKey() + " " + states[i] + "->" + states[j], serialized_data);

                std::ostringstream serialized2;
                boost::archive::text_oarchive oa2(serialized2);
                oa2 << 0;
                std::string serialized_data2 = serialized2.str();
                lm2.Put(wd_.GetCurrentKey() + " " + cnt + " " + states[i], serialized_data2);

                std::ostringstream serialized3;
                boost::archive::text_oarchive oa3(serialized3);
                oa3 << 0;
                std::string serialized_data3 = serialized3.str();
                lm2.Put(wd_.GetCurrentKey() + " " + cnt + " " + states[i] + "->" + states[j], serialized_data3);
            }
        }
    }
}
std::vector<std::string> marfix_stt::HiddenMarkovModel::AssignPhonemeStates(std::vector<std::string> phonemes)
{
    states_.clear();
    states_.resize(phonemes.size());
    states_ = phonemes;
    return states_;
}

std::unordered_map<std::string, double> marfix_stt::HiddenMarkovModel::AssignInitialProbabilities()
{
    int one_probability = 1;
    int zero_probabilitiy = 0;
    initial_probabilities_.clear();

    for (size_t i = 0; i < states_.size(); i++) {
        if (i == 0) {
            initial_probabilities_.insert(std::make_pair(states_[i], one_probability));
        }

        else {
            initial_probabilities_.insert(std::make_pair(states_[i], zero_probabilitiy));
        }
    }

    return initial_probabilities_;
}


std::unordered_map<std::string, double> marfix_stt::HiddenMarkovModel::AssignFinalProbabilities()
{
    double probabilities = 0.5;
    int zero_probabilitiy = 0;
    final_probabilities_.clear();

    for (size_t i = 0; i < states_.size(); i++) {
        if (i == states_.size() - 1) {
            final_probabilities_.insert(std::make_pair(states_[i], probabilities));
        }

        else {
            final_probabilities_.insert(std::make_pair(states_[i], zero_probabilitiy));
        }

    }

    return final_probabilities_;
}


std::unordered_map<std::string, std::unordered_map<std::string, double>> marfix_stt::HiddenMarkovModel::AssignTransitionProbabilities()
{
    double probabilities = 0.5;
    double zero_probabilitiy = 0;
    size_t k;
    transition_probabilities_.clear();
    std::unordered_map<std::string, double> temp;

    for (size_t i = 0; i < states_.size(); i++) {
        k = i + 1;
        temp.clear();

        for (size_t j = 0; j < states_.size(); j++) {
            if (i == states_.size() - 1 && j == states_.size() - 1) {
                temp[states_[j]] = probabilities;
            }

            else if (i == j || k == j) {
                temp[states_[j]] = probabilities;
            }

            else {
                temp[states_[j]] = zero_probabilitiy;
            }
        }

        transition_probabilities_.insert(std::make_pair(states_[i], temp));
    }

    return transition_probabilities_;
}

std::unordered_map<std::string, std::unordered_map<std::string, double>> marfix_stt::HiddenMarkovModel::AssignEmissionProbabilities(std::vector<std::vector<double>> mlp_probabilities)
{
    PhonemeDataset phoneme_dataset("phonemes");
    size_t ph_index;
    std::unordered_map<std::string, double> temp;
    emission_probabilities_.clear();

    for (size_t i = 0; i < states_.size(); i++) {
        temp.clear();

        for (size_t j = 0; j < mlp_probabilities.size(); j++) {
            if (i == 0) {
                observations_.push_back(std::to_string(j));
            }

            ph_index = phoneme_dataset.Phoneme(states_[i]);
            temp[observations_[j]] = mlp_probabilities[j][ph_index];
        }

        emission_probabilities_.insert(std::make_pair(states_[i], temp));
    }

    return emission_probabilities_;
}





