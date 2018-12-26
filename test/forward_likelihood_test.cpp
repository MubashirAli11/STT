#include "stt_common.hpp"
#include "forward_likelihood.hpp"
#include <CppUTest/TestHarness.h>


using namespace marfix_stt;

TEST_GROUP(forward_likelihood_test)
{
    ForwardLikelihood fl;
    std::vector<std::string> phonemes;
    std::vector<std::vector<double>>mlp_probabilities;
    int no_of_frames;
    std::string word;
};

TEST(forward_likelihood_test, calculate_forward_probabilities)
{
    std::cout << "Forward Probabilities" << std::endl;
    no_of_frames = 40;
    word = "ایک";
    phonemes = {"e_", "k"};
    mlp_probabilities.resize(no_of_frames, std::vector<double>(16));

    for (int i = 0; i < 40; i++) {
        for (size_t j = 0; j < 16; j++) {
            mlp_probabilities[i][j] = marfix_stt::CommonUtility::GetRandomNumber(0, 1);
        }
    }

    fl.CalculateForwardProbabilities(word, phonemes, mlp_probabilities);

    for (int i = 0 ; i < no_of_frames; i++) {
        for (size_t j = 0; j < phonemes.size(); j++) {
            std::cout << std::to_string(i) + "|" + phonemes[j] << "->" << fl.GetForwardProbabilities()[phonemes[j] + "|" + std::to_string(i)] << std::endl;
        }
    }

}

