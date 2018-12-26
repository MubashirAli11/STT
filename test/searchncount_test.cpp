#include <vector>
#include <string>
#include <iostream>
#include "searchncount.hpp"
#include <CppUTest/TestHarness.h>

using namespace marfix_stt;

TEST_GROUP(searchncount)
{
    void setup() {
    }
    void teardown() {
    }
};

TEST(searchncount, count_unique2)
{
    std::vector<std::string> sen;
    sen.push_back("*S* a a b *E* *S* a *S*");
    SearchNCount snc(sen);
    //std::cout<<snc.GetUniqueCounts("dot","*E*","*S*");
}

TEST(searchncount, count_unique1)
{
    std::vector<std::string> sen;
    sen.push_back("جیر ابو ظہبی کے شیخ زید اسٹیڈیم میں کھیلے جا رہے ٹیسٹ میں پاکستان کے کپتان مصباح الحق نے ٹاس جیت کر پہلے بیٹنگ کا فیصلہ کیا جیرا");
    SearchNCount snc(sen);
    std::cout << snc.GetUniqueCounts("dot", "بیٹنگ");
}

TEST(searchncount, count_nonunique)
{
    std::vector<std::string> sen;
    sen.push_back("My name is monis");
    sen.push_back("My best friend name is monis");
    sen.push_back("I am 22 years old");
    sen.push_back("Too old to be old");
    SearchNCount snc(sen);
    //    std::cout<<snc.GetNonUniqueCounts("My","name","is");
}
