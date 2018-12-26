#ifndef BEST_HIDDEN_STATE_SEQUENCE_H
#define BEST_HIDDEN_STATE_SEQUENCE_H


#include<vector>
#include<iostream>
#include<string>
#include<unordered_map>
#include<algorithm>
#include<map>


#include "hidden_markov_model.hpp"
#include "viterbi_decoder.hpp"

namespace marfix_stt {

    class BestHiddenStateSequence {
    private:
        HiddenMarkovModel hmm_;
        ViterbiDecoder vd1_;
        std::vector<std::string> path_;
    public:
        std::vector<std::string>FindBestPath(std::vector<std::string> phonemes, std::vector<std::vector<double>> mlp_probabilities);
    };
}

#endif // BEST_HIDDEN_STATE_SEQUENCE_H
