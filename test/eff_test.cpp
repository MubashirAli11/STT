#include "viterbi_decoder.hpp"
#include <CppUTest/TestHarness.h>

using namespace marfix_stt;

TEST_GROUP(eff_test)
{
    std::string word;
    std::vector<std::string> phonemes;
    std::vector<std::string> states;
    std::vector<double> temp_probabilities;
    int no_frames;
    std::vector<std::string> path;
};

TEST(eff_test, return_path)
{

}
