#include "stt_common.hpp"
#include "word_decoder.hpp"
#include <CppUTest/TestHarness.h>

using namespace marfix_stt;

TEST_GROUP(word_decoder_test)
{

    std::vector<std::vector<double>> mlp_probabilities;
    std::string spoken_word;
    int no_of_frames;
};
TEST(word_decoder_test, decode_word)
{
    WordDecoder wd("UWTP");
    mlp_probabilities.resize(40, std::vector<double>(16));

    for (int i = 0; i < 40; i++) {
        for (size_t j = 0; j < 16; j++) {
            mlp_probabilities[i][j] = marfix_stt::CommonUtility::GetRandomNumber(0, 1);
        }
    }

    no_of_frames = 40;
    std::cout << mlp_probabilities[0][10] << std::endl;
    spoken_word = wd.Decode(mlp_probabilities);
    std::cout << "Recognized Word is " << spoken_word << std::endl;

}
