#include "code_book.hpp"
#include<string>
#include <caffe/caffe.hpp>
#include <CppUTest/TestHarness.h>

TEST_GROUP(serialization_with_lmdb)
{
    void setup() override {
        MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();

    }
    void teardown() override {
        MemoryLeakWarningPlugin::turnOnNewDeleteOverloads();
    }
};

TEST(serialization_with_lmdb, lmdb_io_with_serialization)
{
    caffe::Datum d;
    d.set_channels(1);
    d.set_height(1);
    d.set_width(1);
    d.set_label(0);
    d.add_float_data(1.545);
    d.add_float_data(4.544);
    d.add_float_data(3.577);
    const std::string& value = d.SerializeAsString();
    marfix_stt::code_book cb(true);
    caffe::Datum res = cb.read("c4");
    std::cout << res.float_data(0) << " " << res.float_data(1) << " " << res.float_data(2);
}
