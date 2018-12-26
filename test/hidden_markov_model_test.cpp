#include "stt_common.hpp"
#include "hidden_markov_model.hpp"
#include <CppUTest/TestHarness.h>


using namespace marfix_stt;

TEST_GROUP(hidden_markov_model_test)
{
    HiddenMarkovModel hmm_;
    std::vector<std::string> phonemes;
    std::vector<std::vector<double>>mlp_probabilities;
    int no_of_frames;
    std::string word;
};
TEST(hidden_markov_model_test, hmm_test)
{
    std::cout << "Hidden Markov Model" << std::endl;
    no_of_frames = 40;
    word = "ایک";
    phonemes = {"e_", "k"};
    mlp_probabilities.resize(no_of_frames, std::vector<double>(16));

    for (int i = 0; i < 40; i++) {
        for (size_t j = 0; j < 16; j++) {
            mlp_probabilities[i][j] = marfix_stt::CommonUtility::GetRandomNumber(0, 1);
        }
    }

    hmm_.AssignPhonemeStates(phonemes);
    std::cout << "Phonemes" << std::endl;

    for (size_t i = 0; i < phonemes.size(); i++) {
        std::cout << phonemes[i] << std::endl;
    }

    std::cout << "no_of_frames" << std::endl;
    std::cout << no_of_frames << std::endl;
    hmm_.AssignInitialProbabilities();
    std::cout << "Initial Probabilities" << std::endl;

    for (size_t i = 0; i < hmm_.GetStates().size(); i++) {
        std::cout << hmm_.GetInitialProbabilities()[hmm_.GetStates()[i]] << std::endl;
    }

    hmm_.AssignFinalProbabilities();
    std::cout << "Final Probabilities" << std::endl;

    for (size_t i = 0; i < hmm_.GetStates().size(); i++) {
        std::cout << hmm_.GetFinalProbabilities()[hmm_.GetStates()[i]] << std::endl;
    }

    std::cout << "Transition Probabilities" << std::endl;
    hmm_.AssignTransitionProbabilities();

    for (size_t i = 0; i < hmm_.GetStates().size(); i++) {
        for (size_t j = 0; j < hmm_.GetStates().size(); j++) {
            std::cout << hmm_.GetStates()[i] + "-> " + hmm_.GetStates()[j] + " " << hmm_.GetTransitionProbabilities()[hmm_.GetStates()[i]][hmm_.GetStates()[j]] << std::endl;
        }
    }

    hmm_.AssignEmissionProbabilities(mlp_probabilities);
    std::cout << "Emission Probabilities" << std::endl;

    for (size_t i = 0; i < hmm_.GetObservations().size(); i++) {
        for (size_t j = 0; j < hmm_.GetStates().size(); j++) {
            std::cout << hmm_.GetObservations()[i] + "-> " + hmm_.GetStates()[j] + " " << hmm_.GetEmissionProbabilities()[hmm_.GetStates()[j]][hmm_.GetObservations()[i]] << std::endl;
        }
    }
}





