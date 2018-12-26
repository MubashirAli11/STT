#include "fps.hpp"

using namespace marfix_stt;

FitnessProportionateSelection::FitnessProportionateSelection(std::vector<double> probabilities)
{
    this->probabilities = probabilities;
    ComputeIntervals();
}


std::map<Interval, int, IntervalComparator> marfix_stt::FitnessProportionateSelection::GetIntervals()
{
    return probabilityIndex;
}


void FitnessProportionateSelection::ComputeIntervals()
{
    double interval = 0.0;

    for (unsigned int i = 0; i < probabilities.size(); i++) {
        probabilityIndex[Interval(interval, interval + probabilities[i])] = i;
        interval += probabilities[i] + 0.000001;
    }
}

int FitnessProportionateSelection::Select()
{
    std::random_device rd;
    std::mt19937_64 ed(rd());
    std::uniform_real_distribution<> dist(0, 1);
    double random = dist(ed);
    Interval select(random, random);
    return probabilityIndex[select];
}
