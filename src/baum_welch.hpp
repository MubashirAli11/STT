#ifndef BAUM_WELCH_H
#define BAUM_WELCH_H


#include<vector>
#include<iostream>
#include<string>
#include<unordered_map>
#include<map>

#include "hidden_markov_model.hpp"
#include "forward_likelihood.hpp"
#include "backward_likelihood.hpp"


namespace marfix_stt {

    class BaumWelch {
        /// will use vector of double instead of double in method
    private:
        /**
        * @brief hold trained value of the transition probabilities ...
        *
        */
        double calculated_transition_probability_;
        HiddenMarkovModel hmm_;
        ForwardLikelihood fl_;
        BackwardLikelihood bl_;
        std::string word_;

    public:
        void Initializations(std::string word, std::vector<std::string> phonemes, std::vector<std::vector<double>> mlp_probabilities);

        double CalculateForwardBackwardProbabilities(std::string from, std::string to);
    };
}

#endif // BAUM_WELCH_H
