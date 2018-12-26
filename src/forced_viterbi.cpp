#include "forced_viterbi.hpp"

marfix_stt::ForcedViterbi::ForcedViterbi(std::string db_path): lm1_(db_path)
{
}


void marfix_stt::ForcedViterbi::LoadData()
{
    hmm_.LoadData();
}

std::vector<std::string> marfix_stt::ForcedViterbi::GetPath(std::pair<std::string, std::vector<std::string>> word_phonemes_pair, std::vector<std::vector<double>> mlp_probabilities)
{

    path_ = bhss_.FindBestPath(word_phonemes_pair.second, mlp_probabilities);
    phonemes_ = word_phonemes_pair.second;
    word_ = word_phonemes_pair.first;
    return path_;
}

void marfix_stt::ForcedViterbi::UpdateTransitionsCount(std::vector<std::vector<double>> mlp_probabilities)
{
    std::map<std::string , double> state_i;
    std::map<std::string, std::map<std::string, double>> transition_counts;
    path_ = bhss_.FindBestPath(phonemes_, mlp_probabilities);
    marfix_stt::LmdbStream::ReadData(lm1_, word_, phonemes_, transition_counts, state_i);
    transition_counts = CalculateTransitionCounts(path_, state_i, transition_counts);
    marfix_stt::LmdbStream::WriteData(lm1_, word_, phonemes_, transition_counts, state_i);
}

void marfix_stt::ForcedViterbi::UpdateTransitionsProbabilities()
{
    WordDataset wd_("words");

    for (wd_.SeekToFirst(); wd_.IsValid(); wd_.SeekToNext()) {
        std::map<std::string , double> state_i;
        std::map<std::string, std::map<std::string, double>> transition_counts;
        phonemes_ = wd_.Phonemes();
        marfix_stt::LmdbStream::ReadData(lm1_, wd_.GetCurrentKey(), phonemes_, transition_counts, state_i);
        std::unordered_map<std::string, std::unordered_map<std::string, double>> transition_probabilities;

        for (size_t i = 0; i < phonemes_.size(); i++) {
            for (size_t j = 0; j < phonemes_.size(); j++) {
                transition_probabilities[phonemes_[i]][phonemes_[j]] = TrainTransitionProbabilities(transition_counts, phonemes_[i], phonemes_[j], state_i);
            }
        }

        marfix_stt::LmdbStream::WriteTransitionProbability(lm1_,  wd_.GetCurrentKey(), phonemes_, transition_probabilities);
    }
}


std::map<std::string, std::map<std::string, double>> marfix_stt::ForcedViterbi::CalculateTransitionCounts(std::vector<std::string> path, std::map<std::string, double>& state_i, std::map<std::string, std::map<std::string, double>> transition_counts)
{
    int j;

    for (size_t i = 0 ; i < path.size() - 1; i++) {
        j = i + 1;
        transition_counts[path[i]][path[j]] += 1;
        state_i[path[i]] += 1;
    }

    return transition_counts;
}

double marfix_stt::ForcedViterbi::TrainTransitionProbabilities(std::map<std::string, std::map<std::string, double>> transition_counts, std::string state_i, std::string state_j, std::map<std::string, double> state)
{
    double transition_i_j = 0;

    if (state[state_i] != 0) {
        transition_i_j = transition_counts[state_i][state_j] / state[state_i];
    }

    else {
        transition_i_j = 0;
    }

    return transition_i_j;
}
