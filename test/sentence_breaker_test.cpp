#include <vector>
#include <iostream>
#include "sentence_breaker.hpp"
#include <CppUTest/TestHarness.h>


using namespace marfix_stt;

TEST_GROUP(sentence_breaker_test)
{
    SentenceBreaker SB { "sentences.in" };
};

TEST(sentence_breaker_test, break_sentence_into_words_test)
{
    std::ofstream out;
    out.open("words");
    std::vector<std::string> words = SB.GetWords();
    out << words.size() << std::endl;

    for (unsigned int i = 0; i < words.size(); i++) {
        out << words[i] << std::endl;
    }
}



TEST(sentence_breaker_test, check_words_length)
{
    std::vector<std::string> words = SB.GetWords();
    int size = words.size();
    CHECK_EQUAL(204, size);
}
