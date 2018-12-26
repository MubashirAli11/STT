#include "stt_common.hpp"
#include "best_hidden_state_sequence.hpp"
#include <CppUTest/TestHarness.h>


using namespace marfix_stt;

TEST_GROUP(best_hidden_state_sequence_test)
{
    BestHiddenStateSequence bhss1;
    std::vector<std::string> phonemes;
    std::vector<std::vector<double>> mlp_probabilities;
    int no_of_frames;
    std::vector<std::string> path;
};

TEST(best_hidden_state_sequence_test , find_best_path)
{
    std::cout << "Best State Sequence" << std::endl;
    no_of_frames = 40;
    phonemes = {"e_", "k"};
    mlp_probabilities.resize(no_of_frames, std::vector<double>(16));

    for (int i = 0; i < 40; i++) {
        for (size_t j = 0; j < 16; j++) {
            mlp_probabilities[i][j] = marfix_stt::CommonUtility::GetRandomNumber(0, 1);
        }
    }

    path = bhss1.FindBestPath(phonemes, mlp_probabilities);
    std::cout << "Path" << std::endl;

    for (size_t i = 0; i < path.size(); i++) {
        std::cout << path[i] + "->";
    }

    std::cout << std::endl;
}
