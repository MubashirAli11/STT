#include "filter_bank.hpp"
#include <CppUTest/TestHarness.h>

TEST_GROUP(filter_bank)
{

};

TEST(filter_bank, create_filter_bank_test)
{
    using namespace marfix_stt;
    FilterBank fb(26);
    fb.Create();
}
