#include "stt_common.hpp"
#include "hmm_trainer.hpp"
#include <CppUTest/TestHarness.h>

using namespace marfix_stt;

TEST_GROUP(hmm_trainer_test)
{

    std::vector<std::string> phonemes;
    std::vector<std::vector<double>>mlp_probabilities;
    int no_of_frames;
    std::string word;
    std::unordered_map<std::string, std::unordered_map<std::string, double>> transition_probabilities_;
};

TEST(hmm_trainer_test, calculate_forward_backward_probabilities)
{
    HmmTrainer hmmt1("UWTP");
    hmmt1.LoadData();
    std::cout << "Hmm Trainer" << std::endl;
    no_of_frames = 40;
    word = "ایک";
    phonemes = {"e_", "k"};
    mlp_probabilities.resize(no_of_frames, std::vector<double>(16));

    for (int i = 0; i < 40; i++) {
        for (size_t j = 0; j < 16; j++) {
            mlp_probabilities[i][j] = marfix_stt::CommonUtility::GetRandomNumber(0, 1);
        }
    }

    transition_probabilities_ = hmmt1.TrainTransitionProbabilities(word, phonemes, mlp_probabilities);
    std::cout << "updated_transition_probabilities" << std::endl;

    for (size_t i = 0; i < phonemes.size(); i++) {
        for (size_t j = 0; j < phonemes.size(); j++) {
            std::cout << phonemes[i] + " , " + phonemes[j] + "->" << hmmt1.GetTransitionProbabilities()[phonemes[i]][phonemes[j]] << std::endl;
        }
    }
}


