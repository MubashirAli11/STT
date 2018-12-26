#include "stt_common.hpp"
#include "viterbi_decoder.hpp"
#include "hidden_markov_model.hpp"
#include <CppUTest/TestHarness.h>


using namespace marfix_stt;

TEST_GROUP(viterbi_decoder_test)
{

    ViterbiDecoder vd1;
    std::vector<std::string> phonemes;
    std::vector<std::vector<double>> mlp_probabilities;
    std::vector<std::string> path;
    HiddenMarkovModel hmm;

};

TEST(viterbi_decoder_test, calculate_viterbi_probabilities)
{
    phonemes = {"e_", "k"};

    mlp_probabilities.resize(40, std::vector<double>(16));

    for (int i = 0; i < 40; i++) {
        for (size_t j = 0; j < 16; j++) {
            mlp_probabilities[i][j] = marfix_stt::CommonUtility::GetRandomNumber(0, 1);
        }
    }

    path = vd1.CalculateViterbiProbabilties(phonemes, mlp_probabilities);
    std::cout << "Viterbi Probabilities" << std::endl;

    for (int i = 0 ; i < 40; i++) {
        for (size_t j = 0; j < phonemes.size(); j++) {
            std::cout << std::to_string(i) + "|" + phonemes[j] << "->" << vd1.GetViterbiProbabilities()[phonemes[j] + "|" + std::to_string(i)] << std::endl;
        }
    }

    std::cout << "Path" << std::endl;

    for (size_t i = 0; i < path.size(); i++) {
        std::cout << path[i] + "->";
    }

    std::cout << std::endl;
}
