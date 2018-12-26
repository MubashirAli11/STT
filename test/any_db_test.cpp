#include <caffe/util/db_lmdb.hpp>
#include <CppUTest/TestHarness.h>


TEST_GROUP(any_db)
{
    void setup() override {
        MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();

    }
    void teardown() override {
        MemoryLeakWarningPlugin::turnOnNewDeleteOverloads();
    }
};
TEST(any_db, UWTP)
{

    using namespace caffe::db;

    LMDB lmdb;
    lmdb.Open("WordErrorRate", Mode::READ);
    LMDBCursor* cursor = lmdb.NewCursor();
    caffe::Datum d;

    for (cursor->SeekToFirst(); cursor->valid(); cursor->Next()) {
        std::cout << cursor->key() << " " << cursor->value() << std::endl;
    }

    lmdb.Close();

}

