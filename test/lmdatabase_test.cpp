#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include "database.hpp"
#include "hidden_markov_model.hpp"
#include <sstream>
#include <CppUTest/TestHarness.h>

using namespace marfix_stt;

TEST_GROUP(lmdatabase_test)
{
    HiddenMarkovModel hmm1_;
    std::string temp;
    std::string ph;
    std::vector<std::string> all_words;

    std::vector<std::string> states_;
    std::unordered_map<std::string, std::unordered_map<std::string, double>> transition_probabilities;

};
TEST(lmdatabase_test, putting_data)
{
    std::cout << "putting data in lmdb" << std::endl;
    Lmdb lm1("WTP");
    lm1.Put("one", "w ah n");

    lm1.Put("two", "t uw");

    lm1.Put("three", "th r iy");

    lm1.Put("four", "f ao r");

    lm1.Put("five", "f ay v");

    lm1.Put("six", "s ih k s");

    lm1.Put("seven", "s eh v ax n");

    lm1.Put("eight", "ey t");

    lm1.Put("nine", "n ay n");

    lm1.Put("zero", "z iy r ow");
}
TEST(lmdatabase_test, transition_prob_first_time)
{
    all_words = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "zero"};

    for (size_t k = 0; k < all_words.size(); k++) {
        std::vector<std::string> phonemes_;
        Lmdb lm1("WTP");

        temp = lm1.Get(all_words[k]);

        std::cout << temp << std::endl;

        std::istringstream sstr(temp);

        while (std::getline(sstr, ph, ' ')) {
            phonemes_.push_back(ph);
        }

        states_ = hmm1_.AssignPhonemeStates(phonemes_);
        std::cout << "States" << std::endl;

        for (size_t i = 0; i < states_.size(); i++) {
            std::cout << states_[i] << std::endl;
        }

        transition_probabilities = hmm1_.AssignTransitionProbabilities();
        Lmdb lm2("WTP");

        for (size_t i = 0; i < states_.size(); i++) {
            for (size_t j = 0; j < states_.size(); j++) {
                std::ostringstream serialized;
                boost::archive::text_oarchive oa(serialized);
                oa << transition_probabilities[states_[i]][states_[j]];
                lm2.Put(all_words[k] + " " + states_[i] + "->" + states_[j], serialized.str());
            }
        }
    }
}
TEST(lmdatabase_test, read_all_words)
{
    std::cout << "read values" << std::endl;
    all_words = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "zero"};
    Lmdb lm1("WTP");

    for (size_t i = 0; i < all_words.size(); i++) {
        std::cout << all_words[i] + "-> " << lm1.Get(all_words[i]) << std::endl;
    }
}
