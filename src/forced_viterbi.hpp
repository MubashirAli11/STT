#ifndef FORCEDVITERBI_H
#define FORCEDVITERBI_H

#include<vector>
#include<iostream>
#include<string>
#include <unordered_map>
#include <algorithm>
#include <map>
#include "viterbi_decoder.hpp"
#include "hidden_markov_model.hpp"
#include "stt_common.hpp"
#include "best_hidden_state_sequence.hpp"

namespace marfix_stt {
    class ForcedViterbi {
    private:
        /**
         * @brief for storing probabilities which are maximum than other transactions...
        *
        */
        std::unordered_map<std::string, double> viterbi_probabilities_;
        ViterbiDecoder vd1_;
        BestHiddenStateSequence bhss_;
        HiddenMarkovModel hmm_;
        std::vector<std::string> path_;
        std::vector<std::string> phonemes_;
        std::string word_;
        int no_of_frames_;
        Lmdb lm1_;

        std::map<std::string, std::map<std::string, double>> CalculateTransitionCounts(std::vector<std::string> path, std::map<std::string, double>& state_i, std::map<std::string, std::map<std::string, double>> transition_counts);
        /**
        * @brief trained transition probabilities from transition counts ...

        */
        double TrainTransitionProbabilities(std::map<std::string, std::map<std::string, double>> transition_counts, std::string state_i, std::string state_j, std::map<std::string, double> state);
    public:

        /**
         * @brief counts of phoneme transition in each frames...

         */
        ForcedViterbi(std::string db_path);
        void LoadData();

        std::vector<std::string> GetPath(std::pair<std::string, std::vector<std::string>> word_phonemes_pair , std::vector<std::vector<double>> mlp_probabilities);


        void UpdateTransitionsCount(std::vector<std::vector<double>> mlp_probabilities);

        void UpdateTransitionsProbabilities();


    };
}

#endif // FORCEDVITERBI_H
