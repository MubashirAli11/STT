#include <vector>
#include <cmath>
#include <memory>
class IActivationFunction {

public:
    virtual double Apply(double) = 0;
    virtual ~IActivationFunction() {};
};
class SigmoidActivationFunction : public IActivationFunction {
    inline double Apply(double value) override
    {
        return 1 / (1 + std::exp(-value));
    };
};
class HyperbolicTangentActivationFunction : public IActivationFunction {
    inline double Apply(double value) override
    {
        return std::tanh(value);
    };
};

class ReLUActivationFunction : public IActivationFunction {
    inline double Apply(double value) override
    {
        return std::max(0.0, value);
    };
};
class Neuron {

public:
    double summation;
    double outputWeight;
    double value;
    std::vector<Neuron> attachedNeurons;
    std::shared_ptr<IActivationFunction> activationFunction;
    Neuron(): summation(0), value(0), activationFunction(new SigmoidActivationFunction) {};

    void AttachWith(const Neuron& other)
    {
        attachedNeurons.push_back(other);
        summation += other.value * other.outputWeight;
        value = activationFunction->Apply(summation);
    };
    void AttachWith(const std::vector<Neuron>& neurons)
    {
        attachedNeurons.insert(attachedNeurons.end(), neurons.begin(), neurons.end());

        for (auto i : neurons) {
            summation += i.value * i.outputWeight;
        }

        value = activationFunction->Apply(summation);
    }
};
class NeuralNetwork {
public:
    std::vector<Neuron> inputLayer;
    std::vector<Neuron> hiddenLayer;
    std::vector<Neuron> outputLayer;

    void StartLearning()
    {
    }

    bool normalize = false;

};
#include <CppUTest/TestHarness.h>
TEST_GROUP(neural_network_testing)
{

};
TEST(neural_network_testing, input_weights_on_a_hidden_neuron)
{

    Neuron hiddenNeuron;
    DOUBLES_EQUAL(0, hiddenNeuron.summation, 0.01);

    Neuron inputNeuron1;
    inputNeuron1.value = 1.0;
    inputNeuron1.outputWeight = 0.5;

    Neuron inputNeuron2;
    inputNeuron2.value = 2.0;
    inputNeuron2.outputWeight = 0.2;

    Neuron inputNeuron3;
    inputNeuron3.value = 3.0;
    inputNeuron3.outputWeight = 0.7;

    hiddenNeuron.AttachWith(inputNeuron1);
    hiddenNeuron.AttachWith(inputNeuron2);
    hiddenNeuron.AttachWith(inputNeuron3);

    DOUBLES_EQUAL(3, hiddenNeuron.summation, 0.01);
}

TEST(neural_network_testing, test_neural_network)
{
    // NeuralNetwork neuralNetwok;

    /* neuralNetwok.inputLayer();

     neuralNetwok.hiddenLayer();

     neuralNetwok.outputLayer();
     */

}
