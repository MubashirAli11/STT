#include "multilayerperceptron.hpp"
#include "activation_functions.hpp"
#include "database.hpp"
#include <functional>
#include <vector>
#include <CppUTest/TestHarness.h>

using namespace marfix_stt;

TEST_GROUP(mlp)
{
    void setup() {
        MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();
    }
    void teardown() {

        MemoryLeakWarningPlugin::turnOnNewDeleteOverloads();
    }
};

TEST(mlp, test1)
{
    std::vector<std::vector<double>> Tin = {{0.8, 0.75}, {0.8, 1}};
    std::vector<std::vector<double>> Tout = {{0.78}, {0.8571}};
    MultilayerPerceptron mlp1(Tin, Tout, 1, {3});
    std::function<std::vector<std::vector<double>>(ActivationFunctions&, std::vector<std::vector<double>>, bool)> f_activation_function = &ActivationFunctions::Sigmoid;
    mlp1.Learn(200000, f_activation_function);
    std::vector<std::vector<double>> tin = {{0.8, 1}};
    std::cout << "(x+y)" << std::endl;
    mlp1.Test(tin);
    std::cout << std::endl;
}

TEST(mlp, test2)
{
    std::vector<std::vector<double>> Tin = {{1, 1}, {0, 1}, {1, 0}, {0, 0}}; //and op
    std::vector<std::vector<double>> Tout = {{1}, {0}, {0}, {0}};   // and op
    MultilayerPerceptron mlp1(Tin, Tout, 1, {3});
    std::function<std::vector<std::vector<double>>(ActivationFunctions&, std::vector<std::vector<double>>, bool)> f_activation_function = &ActivationFunctions::Sigmoid;
    mlp1.Learn(200000, f_activation_function);
    std::vector<std::vector<double>> tin = {{1, 1}};
    std::cout << "(AND)" << std::endl;
    mlp1.Test(tin);
    std::cout << std::endl;
}

TEST(mlp, test3)
{
    std::vector<std::vector<double>> Tin = {{1, 1}, {0, 1}, {1, 0}, {0, 0}}; //xor op
    std::vector<std::vector<double>> Tout = {{0}, {1}, {1}, {0}};   //xor op
    MultilayerPerceptron mlp1(Tin, Tout, 2, {3, 3});
    std::function<std::vector<std::vector<double>>(ActivationFunctions&, std::vector<std::vector<double>>, bool)> f_activation_function = &ActivationFunctions::Sigmoid;
    mlp1.Learn(60000, f_activation_function);
    std::vector<std::vector<double>> tin = {{1, 1}};
    std::cout << "(XOR)" << std::endl;
    mlp1.Test(tin);
    std::cout << std::endl;
}
