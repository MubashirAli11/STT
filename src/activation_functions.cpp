#include "activation_functions.hpp"

using namespace marfix_stt;


std::vector<std::vector<double>> ActivationFunctions::Sigmoid(std::vector<std::vector<double>> input, bool deriv)
{
    std::vector<std::vector<double>> siginp(input.size(), std::vector<double>(input[0].size(), 0.0));

    for (size_t i = 0; i < input.size(); i++) {
        for (size_t j = 0; j < input[0].size(); j++) {
            if (deriv == false) {
                siginp[i][j] = 1 / (1 + (exp(-input[i][j])));
            }

            else {
                siginp[i][j] = input[i][j] * (1 - input[i][j]);
            }
        }
    }

    return siginp;
}
