#include "baum_welch.hpp"
using namespace marfix_stt;

void BaumWelch::Initializations(std::string word, std::vector<std::string> phonemes, std::vector<std::vector<double>> mlp_probabilities)
{
    word_ = word;
    hmm_.AssignPhonemeStates(phonemes);
    hmm_.AssignInitialProbabilities();
    hmm_.AssignFinalProbabilities();
    hmm_.AssignTransitionProbabilities();
    hmm_.AssignEmissionProbabilities(mlp_probabilities);
    fl_.CalculateForwardProbabilities(word_, phonemes, mlp_probabilities);
    bl_.CalculateBackwardProbabilities(word_, phonemes, mlp_probabilities);
}


double BaumWelch::CalculateForwardBackwardProbabilities(std::string from, std::string to)
{

    double all_forw_back_prob = fl_.GetForwardProbabilities()["final state"];
    double transition_from_state;
    double expected_transitions = 0;
    double expected_transitions_i_j = 0;
    double at_state_i = 0;

    for (size_t i = 0; i < hmm_.GetObservations().size() - 1; i++) {
        for (size_t j = 0; j < hmm_.GetStates().size(); j++) {
            all_forw_back_prob = 0;

            for (size_t k = 0; k < hmm_.GetStates().size(); k++) {
                for (size_t l = 0; l < hmm_.GetStates().size(); l++) {
                    all_forw_back_prob += fl_.GetForwardProbabilities()[hmm_.GetStates()[k] + "|" + hmm_.GetObservations()[i]] * hmm_.GetTransitionProbabilities()[hmm_.GetStates()[k]][hmm_.GetStates()[l]] * hmm_.GetEmissionProbabilities()[hmm_.GetStates()[l]][hmm_.GetObservations()[i + 1]] * bl_.BackwardProbabilities()[hmm_.GetStates()[l] + "|" + hmm_.GetObservations()[i + 1]];
                }
            }

            transition_from_state = fl_.GetForwardProbabilities()[from + "|" + hmm_.GetObservations()[i]] * hmm_.GetTransitionProbabilities()[from] [hmm_.GetStates()[j]] * hmm_.GetEmissionProbabilities()[hmm_.GetStates()[j]][hmm_.GetObservations()[i + 1]] * bl_.BackwardProbabilities()[hmm_.GetStates()[j] + "|" + hmm_.GetObservations()[i + 1]];
            at_state_i = transition_from_state / all_forw_back_prob;
            expected_transitions += at_state_i;

            if (hmm_.GetStates()[j] == to) {
                expected_transitions_i_j += at_state_i;
            }
        }
    }

    calculated_transition_probability_ = expected_transitions_i_j / expected_transitions;
    return calculated_transition_probability_;
}
