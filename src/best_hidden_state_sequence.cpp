#include "best_hidden_state_sequence.hpp"

using namespace marfix_stt;
std::vector<std::string> BestHiddenStateSequence::FindBestPath(std::vector<std::string> phonemes, std::vector<std::vector<double>> mlp_probabilities)
{
    path_ = vd1_.CalculateViterbiProbabilties(phonemes, mlp_probabilities);
    return path_;
}

