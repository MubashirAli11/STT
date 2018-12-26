#include "code_book.hpp"


using namespace marfix_stt;
using namespace  caffe::db;

marfix_stt::code_book::code_book(bool first_time)
{
    if (first_time) {
        LMDB lmdb;
        lmdb.Open("centroid_lmdb", Mode::NEW);
        lmdb.Close();
    }
}

void marfix_stt::code_book::insert(const std::string& key, const std::string& value)
{
    LMDB lmdb;
    lmdb.Open("centroid_lmdb", Mode::WRITE);
    LMDBTransaction* transaction = lmdb.NewTransaction();
    transaction->Put(key, value);
    transaction->Commit();
    lmdb.Close();
}

caffe::Datum marfix_stt::code_book::read(const std::string& key)
{
    LMDB lmdb;
    lmdb.Open("centroid_lmdb", Mode::READ);
    LMDBCursor* cursor = lmdb.NewCursor();
    caffe::Datum d;

    for (cursor->SeekToFirst(); cursor->valid(); cursor->Next()) {
        d.ParseFromString(cursor->value());

        if (cursor->key().compare(key) == 0) {
            lmdb.Close();
            return d;
        }
    }

    lmdb.Close();
    return d;
}

std::vector<std::vector<double>> marfix_stt::code_book::readAll(long vlen)
{
    std::vector<std::vector<double>> data;
    LMDB lmdb;
    lmdb.Open("centroid_lmdb", Mode::READ);
    LMDBCursor* cursor = lmdb.NewCursor();

    long k = 0;

    for (cursor->SeekToFirst(); cursor->valid(); cursor->Next()) {
        std::vector<double> temp;
        caffe::Datum d;
        d.ParseFromString(cursor->value());

        for (auto i = 0; i < vlen; i++) {
            temp.push_back(d.float_data(i));
        }

        data.push_back(temp);
        k++;
    }

    lmdb.Close();
    return data;
}
