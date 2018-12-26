#ifndef VITERBIDECODER_HPP
#define VITERBIDECODER_HPP


#include<vector>
#include<iostream>
#include<string>
#include<unordered_map>
#include<algorithm>
#include<map>
#include<string>
#include "hidden_markov_model.hpp"
#include "decoder.hpp"

namespace marfix_stt {
    class ViterbiDecoder: public Decoder {
    private:
        /**
         * @brief for storing probabilities which are maximum than other transactions...
         *
         */
        std::unordered_map<std::string, double> viterbi_probabilities_;
        std::vector<std::string> path_;
        HiddenMarkovModel hmm_;
    public:

        std::vector<std::string> CalculateViterbiProbabilties(std::vector<std::string> phonemes, std::vector<std::vector<double>> mlp_probabilities);

        ///Getters and Setters

        void ViterbiProbabilities(std::unordered_map<std::string, double> viterbi_probabilities)
        {
            this->viterbi_probabilities_ = viterbi_probabilities;
        }

        std::unordered_map<std::string, double> GetViterbiProbabilities()
        {
            return this->viterbi_probabilities_;
        }
    };
}

#endif // VITERBIDECODER__HPP
