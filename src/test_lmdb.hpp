#ifndef TEST_LMDB_H
#define TEST_LMDB_H

#include <caffe/caffe.hpp>
#include <caffe/util/db_lmdb.hpp>

namespace marfix_stt {

    class test_lmdb {
    public :
        test_lmdb();

        void create_lmdb(std::string name);
        void insert_dummy_data(int x1, int x2, int y1, int y2, int count);
        void setDbName(std::string name);
        void insert_bug_data(int red_min, int red_max, int blue_min, int blue_max, int green_min, int green_max, int count);
        std::string getDbName();
        int get_bug(int red, int green, int blue);
        // void update(const std::string& key);
        //void remove(const std::string& key);
        //caffe::Datum read(const std::string& key);
        std::vector<std::vector<double>> readAll(long);

    private:
        std::string db_name;
        int get_random_number(int min , int max);


    };
}
#endif // TEST_LMDB_H
