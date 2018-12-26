#include "word_decoder.hpp"


marfix_stt::WordDecoder::WordDecoder(std::string db_path): lm1_(db_path)
{
}


std::string marfix_stt::WordDecoder::Decode(std::vector<std::vector<double>> mlp_probability)
{
    HiddenMarkovModel hmm_;
    ViterbiDecoder vd_;
    WordDataset wd_("words");
    std::string spoken_word = "alif";
    std::vector<std::string> ph;
    std::vector<std::vector<double>> e_probabiities;
    std::unordered_map<std::string, std::unordered_map<std::string, double>> transition_probabilities;
    int q = 0;
    word_probability_.clear();

    for (wd_.SeekToFirst(); wd_.IsValid(); wd_.SeekToNext()) {
        ph = wd_.Phonemes();
        hmm_.AssignPhonemeStates(ph);
        hmm_.AssignInitialProbabilities();
        hmm_.AssignFinalProbabilities();

        transition_probabilities = marfix_stt::LmdbStream::ReadTransitionProbability(lm1_, wd_.GetCurrentKey(), ph);

        hmm_.TransitionProbabilities(transition_probabilities);
        mlp_probability = marfix_stt::HybridApproach::GiveScaledEmissionProbability(mlp_probability);
        hmm_.AssignEmissionProbabilities(mlp_probability);
        vd_.CalculateViterbiProbabilties(ph, mlp_probability);
        word_probability_.insert(std::make_pair(wd_.GetCurrentKey(), vd_.GetViterbiProbabilities()["final state"]));
        q++;
    }

    std::cout << q << std::endl;
    auto itr = std::max_element(word_probability_.begin(), word_probability_.end(), [](auto first, auto second) {
        return first.second < second.second;
    });
    spoken_word = itr->first;


    return spoken_word;
}
