#include "stt_common.hpp"
#include <CppUTest/TestHarness.h>

TEST_GROUP(likelihood_test)
{
    std::vector<std::vector<double>> mlp_probabilities;
};
TEST(likelihood_test, give_scaled_likelihood)
{
    mlp_probabilities.resize(3, std::vector<double>(3));
    mlp_probabilities = {{0.5, 0.1, 0.3}, {0.2, 0.2, 0.4}, {0.3, 0.4, 0.6}};
    std::vector<std::vector<double>> scaled_probabilities;

    scaled_probabilities = marfix_stt::HybridApproach::GiveScaledEmissionProbability(mlp_probabilities);

    for (size_t i = 0; i < scaled_probabilities.size(); i++) {
        for (size_t j = 0; j < scaled_probabilities[i].size(); j++) {
            std::cout << "-> " << scaled_probabilities[i][j] << std::endl;
        }
    }
}
