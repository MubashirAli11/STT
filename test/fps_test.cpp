#include "fps.hpp"
#include <vector>
#include<iostream>
#include <CppUTest/TestHarness.h>


using namespace marfix_stt;

TEST_GROUP(fps)
{
};

TEST(fps, IntervalsnSelection)
{
    std::vector<double> probs;
    probs.push_back(0.6);
    probs.push_back(0.2);
    probs.push_back(0.2);
    FitnessProportionateSelection fpss(probs);
    std::map<Interval, int, IntervalComparator> probabilityIndex = fpss.GetIntervals();
    Interval s(0, 0.6);
    std::cout << "Interval=" << probabilityIndex[s] << std::endl;
    Interval s1(0.3, 0.3);
    std::cout << "Selection=" << probabilityIndex[s1];

}
