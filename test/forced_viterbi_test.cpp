#include "forced_viterbi.hpp"
#include <CppUTest/TestHarness.h>

using namespace marfix_stt;

TEST_GROUP(forced_viterbi_test)
{

    std::pair<std::string, std::vector<std::string>> word_phonemes_pair;
    std::vector<std::vector<double>> mlp_probabilities;
    int no_of_frames;
    std::vector<std::string> path;
};

TEST(forced_viterbi_test, forced_path)
{
    ForcedViterbi fv("UWTP");
    fv.LoadData();
    no_of_frames = 40;
    word_phonemes_pair.first = "ایک";
    word_phonemes_pair.second = {"e_", "k"};
    mlp_probabilities.resize(no_of_frames, std::vector<double>(16));

    for (int i = 0; i < 40; i++) {
        for (size_t j = 0; j < 16; j++) {
            mlp_probabilities[i][j] = marfix_stt::CommonUtility::GetRandomNumber(0, 1);
        }
    }

    for (int i = 0; i < 10; i++) {
        path = fv.GetPath(word_phonemes_pair, mlp_probabilities);

        for (size_t i = 0; i < path.size(); i++) {
            std::cout << path[i] + "->";
        }

        std::cout << std::endl;
        /////mlp working
        fv.UpdateTransitionsCount(mlp_probabilities);
    }

    ////again do it for other sound files of same word
    //and finally update trasition probabilities
    fv.UpdateTransitionsProbabilities();
}



