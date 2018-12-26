#ifndef ACTIVATION_FUNCTIONS_H
#define ACTIVATION_FUNCTIONS_H

#include<vector>
#include<cmath>
#include<algorithm>

namespace marfix_stt {
    class ActivationFunctions {
    public:

        std::vector<std::vector<double>> Sigmoid(std::vector<std::vector<double>> input, bool deriv);
    };
}

#endif // ACTIVATION_FUNCTIONS_H
