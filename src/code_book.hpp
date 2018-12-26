#ifndef CODE_BOOK_HPP
#define CODE_BOOK_HPP
#include <string>
#include<vector>
#include <caffe/caffe.hpp>
#include <caffe/util/db_lmdb.hpp>


namespace marfix_stt {
    class code_book {
    public :
        code_book(bool);
        void insert(const std::string& key, const std::string& value);
        void update(const std::string& key);
        void remove(const std::string& key);
        caffe::Datum read(const std::string& key);
        std::vector<std::vector<double>> readAll(long);
    };
}
#endif // CODE_BOOK_HPP
