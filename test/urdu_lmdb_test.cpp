#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "database.hpp"
#include "hidden_markov_model.hpp"
#include <sstream>
#include <CppUTest/TestHarness.h>

using namespace marfix_stt;

TEST_GROUP(urdu_lmdb_test)
{
    HiddenMarkovModel hmm1_;
    std::string ph;
    std::string temp;
    std::vector<std::string> all_words;
    std::string cnt;
    std::vector<std::string> states_;
    std::unordered_map<std::string, std::unordered_map<std::string, double>> transition_probabilities;
};

TEST(urdu_lmdb_test, putting_data)
{

    std::cout << "putting data in lmdb" << std::endl;
    Lmdb lm1("UWTP");

    lm1.Put("ایک", "e_ k");

    lm1.Put("دو", "d_ o_");

    lm1.Put("تین", "t_ i_ n");

    lm1.Put("چار", "tsh a_ r");

    lm1.Put("پانچ", "p A tsh");

    lm1.Put("چھ", "tshh e_");

    lm1.Put("سات", "s a_ t_");

    lm1.Put("آٹھ", "a_ th");

    lm1.Put("نو", "n c o_");

    lm1.Put("دس", "d_ c s");

}

TEST(urdu_lmdb_test, transition_prob_first_time)
{
    cnt = "count";
    all_words.push_back("ایک");
    all_words.push_back("دو");
    all_words.push_back("تین");
    all_words.push_back("چار");
    all_words.push_back("پانچ");
    all_words.push_back("چھ");
    all_words.push_back("سات");
    all_words.push_back("آٹھ");
    all_words.push_back("نو");
    all_words.push_back("دس");

    for (size_t index = 0; index < all_words.size(); index++) {
        std::vector<std::string> phonemes_;
        Lmdb lm1("UWTP");
        temp = lm1.Get(all_words[index]);
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
        Lmdb lm2("UWTP");

        for (size_t i = 0; i < states_.size(); i++) {
            for (size_t j = 0; j < states_.size(); j++) {

                std::ostringstream serialized;
                boost::archive::text_oarchive oa(serialized);
                oa << transition_probabilities[states_[i]][states_[j]];
                std::string serialized_data = serialized.str();
                lm2.Put(all_words[index] + " " + states_[i] + "->" + states_[j], serialized_data);

                std::ostringstream serialized2;
                boost::archive::text_oarchive oa2(serialized2);
                oa2 << 0;
                std::string serialized_data2 = serialized2.str();
                lm2.Put(all_words[index] + " " + cnt + " " + states_[i], serialized_data2);

                std::ostringstream serialized3;
                boost::archive::text_oarchive oa3(serialized3);
                oa3 << 0;
                std::string serialized_data3 = serialized3.str();
                lm2.Put(all_words[index] + " " + cnt + " " + states_[i] + "->" + states_[j], serialized_data3);
            }
        }
    }
}

TEST(urdu_lmdb_test, read_all_words)
{
    std::cout << "read values" << std::endl;
    all_words.push_back("ایک");
    all_words.push_back("دو");
    all_words.push_back("تین");
    all_words.push_back("چار");
    all_words.push_back("پانچ");
    all_words.push_back("چھ");
    all_words.push_back("سات");
    all_words.push_back("آٹھ");
    all_words.push_back("نو");
    all_words.push_back("دس");
    Lmdb lm1("UWTP");

    for (size_t i = 0; i < all_words.size(); i++) {
        std::cout << all_words[i] + "-> " << lm1.Get(all_words[i]) << std::endl;
    }
}

TEST(urdu_lmdb_test, load_lmdb_data)
{
    hmm1_.LoadData();
}
