#include<iostream>
#include <vector>
#include "lmdbcursor.hpp"
#include "database.hpp"
#include <CppUTest/TestHarness.h>

TEST_GROUP(lmdb_wrapper)
{
    void setup() {
        MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();
    }
    void teardown() {
        MemoryLeakWarningPlugin::turnOnNewDeleteOverloads();
    }
};

TEST(lmdb_wrapper, lmdb_tc1)
{
    marfix_stt::Lmdb lmdb("Test500");
    lmdb.Put("1", "a.b");
    std::cout << lmdb.Get("1") << std::endl;

    /*std::cout<<lmdb.Get("1")<<std::endl;
    std::cout<<lmdb.Get("2")<<std::endl0;
    std::cout<<lmdb.Get("3")<<std::endl;
    std::cout<<lmdb.Get("4")<<std::endl;
    std::cout<<lmdb.Get("5")<<std::endl;
    std::cout<<lmdb.Get("6")<<std::endl;*/
}
