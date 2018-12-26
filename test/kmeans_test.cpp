#include "kmeans.hpp"
#include <CppUTest/TestHarness.h>


using namespace marfix_stt;

TEST_GROUP(kmeans_test)
{


};
TEST(kmeans_test, clustering)
{
    long k = 2;
    std::vector<double> a = {1.0, 1.0};
    std::vector<double> c = {0.0, 2.0};
    std::vector<std::vector<double>> features;
    std::vector<std::string> names = {"1", "2"};
    features.push_back(a);
    features.push_back(c);
    kmeans k1(k, features, names, true);
    std::vector<double> a1 = {1.0, 0.0};
    std::vector<double> b = {1.0, 0.0};
    std::vector<double> c1 = {0.0, 2.0};
    std::vector<double> d = {2.0, 4.0};
    std::vector<double> e = {3.0, 5.0};
    std::cout << k1.Update_Clusters(a1) << std::endl;
    std::cout << k1.Update_Clusters(b) << std::endl;
    std::cout << k1.Update_Clusters(c1) << std::endl;
    std::cout << k1.Update_Clusters(d) << std::endl;
    std::cout << k1.Update_Clusters(e) << std::endl;
}
