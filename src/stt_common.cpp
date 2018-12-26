#include "stt_common.hpp"
using namespace marfix_stt;


void LmdbStream::ReadData(Lmdb& lm1, std::string word, std::vector<std::string> phonemes, std::map<std::string, std::map<std::string, double>>& transition_counts, std::map<std::string, double>& state_i)
{
    std::string cnt = "count";

    for (size_t i = 0; i < phonemes.size(); i++) {
        for (size_t j = 0; j < phonemes.size(); j++) {
            std::istringstream deserialized2;
            deserialized2.str(lm1.Get(word + " " + cnt + " " + phonemes[i]));
            boost::archive::text_iarchive ia2(deserialized2);
            ia2 >> state_i[phonemes[i]];

            std::istringstream deserialized3;
            deserialized3.str(lm1.Get(word + " " + cnt + " " + phonemes[i] + "->" + phonemes[j]));
            boost::archive::text_iarchive ia3(deserialized3);
            ia3 >> transition_counts[phonemes[i]][phonemes[j]];
        }
    }
}
void marfix_stt::LmdbStream::WriteData(Lmdb& lm1, std::string word, std::vector<std::string> phonemes, std::map<std::string, std::map<std::string, double>>& transition_counts, std::map<std::string, double>& state_i)
{
    std::string cnt = "count";

    for (size_t i = 0; i < phonemes.size(); i++) {
        for (size_t j = 0; j < phonemes.size(); j++) {

            std::ostringstream serialized2;
            boost::archive::text_oarchive oa2(serialized2);
            oa2 << state_i[phonemes[i]];
            lm1.Put(word + " " + cnt + " " + phonemes[i], serialized2.str());

            std::ostringstream serialized3;
            boost::archive::text_oarchive oa3(serialized3);
            oa3 << transition_counts[phonemes[i]][phonemes[j]];
            lm1.Put(word + " " + cnt + " " + phonemes[i] + "->" + phonemes[j], serialized3.str());




        }
    }
}

std::unordered_map<std::string, std::unordered_map<std::string, double>> LmdbStream::ReadTransitionProbability(marfix_stt::Lmdb& lm1, std::string word, std::vector<std::string> phonemes)
{
    std::unordered_map<std::string, std::unordered_map<std::string, double>> transition_probabilities;

    for (size_t i = 0; i < phonemes.size(); i++) {
        for (size_t j = 0; j < phonemes.size(); j++) {
            std::istringstream deserialized2;
            deserialized2.str(lm1.Get(word + " " + phonemes[i] + "->" + phonemes[j]));
            boost::archive::text_iarchive ia2(deserialized2);
            ia2 >> transition_probabilities[phonemes[i]][phonemes[j]];
        }
    }

    return transition_probabilities;
}


void LmdbStream::WriteTransitionProbability(Lmdb& lm1, std::string word, std::vector<std::string> phonemes, std::unordered_map<std::string, std::unordered_map<std::string, double>> transition_probabilities)
{

    std::cout << "updated transition probabilities" << std::endl;

    for (size_t i = 0; i < phonemes.size(); i++) {
        for (size_t j = 0; j < phonemes.size(); j++) {
            std::ostringstream serialized;
            boost::archive::text_oarchive oa(serialized);
            oa << transition_probabilities[phonemes[i]][phonemes[j]];
            lm1.Put(word + " " + phonemes[i] + "->" + phonemes[j], serialized.str());


        }
    }
}

double CommonUtility::GetRandomNumber(double min, double max)
{
    std::random_device rd;
    std::mt19937_64 ed(rd());
    std::uniform_real_distribution<> dist(min, max);
    double random = dist(ed);
    return random;
}

std::vector<std::string> CommonUtility::SplitString(std::string str)
{
    std::string splitted_string;
    std::istringstream sstr(str);
    std::vector<std::string> splitted_strings;

    while (std::getline(sstr, splitted_string, ' ')) {
        splitted_strings.push_back(splitted_string);
    }

    return splitted_strings;
}
std::vector<int> Argmax(const std::vector<double>& v, int N)
{
    std::vector<std::pair<double, int>> pairs;

    for (size_t i = 0; i < v.size(); ++i) {
        pairs.push_back(std::make_pair(v[i], i));
    }

    std::partial_sort(pairs.begin(), pairs.begin() + N, pairs.end(), CommonUtility::PairCompare);

    std::vector<int> result;

    for (int i = 0; i < N; ++i) {
        result.push_back(pairs[i].second);
    }

    return result;
}

std::vector<std::vector<double>> HybridApproach::GiveScaledEmissionProbability(std::vector<std::vector<double>> mlp_probabilities)
{
    std::vector<std::vector<double>> scaled_probabilities;
    scaled_probabilities.resize(mlp_probabilities.size(), std::vector<double>(mlp_probabilities[0].size()));
    double value;
    std::vector<double> prob;

    for (size_t i = 0; i < mlp_probabilities[0].size(); i++) {
        value = 0;

        for (size_t j = 0; j < mlp_probabilities.size(); j++) {
            value += mlp_probabilities[j][i];
        }

        prob.push_back(value);
    }

    for (size_t i = 0; i < mlp_probabilities.size(); i++) {
        for (size_t j = 0; j < mlp_probabilities[i].size(); j++) {
            scaled_probabilities[i][j] = mlp_probabilities[i][j] / prob[j];
        }
    }

    return scaled_probabilities;
}





