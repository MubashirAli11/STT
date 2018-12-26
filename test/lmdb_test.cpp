#include <iostream>
#include "test_lmdb.hpp"
#include <CppUTest/TestHarness.h>

TEST_GROUP(lmdb_t)
{
    void setup() {
        MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();
    }
    void teardown() {
        MemoryLeakWarningPlugin::turnOnNewDeleteOverloads();
    }
};
TEST(lmdb_t, Storing_data)
{
    marfix_stt::test_lmdb tb;

    tb.create_lmdb("bugdb2Test");
    tb.insert_bug_data(1, 150, 1, 200, 10, 100, 1000);
    // tb.setDbName("bugdbTest");
    std::vector<std::vector <double>> data = tb.readAll(3);
    std::cout << "Displaying\n";

    for (unsigned int i = 0; i < data.size(); i++) {
        std::cout << data[i][0] << "\t" << data[i][1] << "\t" << data[i][2] << std::endl ;
        //   std::cout<<data[i][0]<< "\t"<<data[i][1]<<std::endl ;
    }

}
