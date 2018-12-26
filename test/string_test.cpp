#include <sstream>
#include <string>
#include <iomanip>
#include <iostream>
#include <CppUTest/TestHarness.h>

TEST_GROUP(String_test)
{

};

TEST(String_test, split_string)
{
    /*  std::string s("The,quick,brown");
        std::stringstream ss;
        ss.str(s);
        std::string item;

        while (std::getline(ss, item, ',')) {
            std::cout << item << std::endl;
        }*/
}
TEST(String_test, trim_string)
{

}
TEST(String_test, to_string_test)
{
    double value = 0.302034020000000000000000000000000000000000000000123408210381251324e-19;
    std::cout << std::ios::fixed << std::setprecision(1000) << std::to_string(value) << std::endl;
}
