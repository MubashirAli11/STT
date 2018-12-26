#include "stt_common.hpp"
#include "backward_likelihood.hpp"
#include <CppUTest/TestHarness.h>

using namespace marfix_stt;

TEST_GROUP(backward_likelihood_test)
{
    BackwardLikelihood bl1;
    std::vector<std::string> phonemes;
    std::vector<std::vector<double>>mlp_probabilities;
    int no_of_frames;
    std::string word;
};

TEST(backward_likelihood_test, calculate_backward_probabilities)
{
    std::cout << "Backward Probabilities" << std::endl;
    no_of_frames = 40;
    word = "ایک";
    phonemes = {"e_", "k"};
    mlp_probabilities.resize(no_of_frames, std::vector<double>(16));

    for (int i = 0; i < 40; i++) {
        for (size_t j = 0; j < 16; j++) {
            mlp_probabilities[i][j] = marfix_stt::CommonUtility::GetRandomNumber(0, 1);
        }
    }

    bl1.CalculateBackwardProbabilities(word, phonemes, mlp_probabilities);

    for (int i = 0 ; i < no_of_frames; i++) {
        for (size_t j = 0; j < phonemes.size(); j++) {
            std::cout << std::to_string(i) + "|" + phonemes[j] << "->" << bl1.BackwardProbabilities()[phonemes[j] + "|" + std::to_string(i)] << std::endl;
        }
    }
}
