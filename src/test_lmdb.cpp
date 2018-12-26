#include "test_lmdb.hpp"
#include<random>
using namespace caffe::db;

marfix_stt::test_lmdb::test_lmdb()
{

}

void marfix_stt::test_lmdb::setDbName(std::string name)
{
    db_name = name;
}

std::string marfix_stt::test_lmdb::getDbName()
{
    return db_name;
}

void marfix_stt::test_lmdb::create_lmdb(std::string name)
{
    LMDB lmdb;
    lmdb.Open(name, Mode::NEW);
    lmdb.Close();
    setDbName(name) ;
}

void marfix_stt::test_lmdb::insert_dummy_data(int x1, int x2, int y1, int y2 , int count)
{
    int label , counter = 0;
    float x, y;
    LMDB lmdb;
    lmdb.Open(db_name, Mode::WRITE);
    LMDBTransaction* transaction = lmdb.NewTransaction();

    for (int i = 0 ; i <= count ; i++) {
        caffe::Datum d;
        d.set_channels(1);
        d.set_height(1);
        d.set_width(2);
        x = get_random_number(x1, x2);
        y = get_random_number(y1, y2);
        label = x + y;
        std::cout << "X = " << x << "Y = " << y << "label = " << label << std::endl ;
        d.add_float_data(x);
        d.add_float_data(y);
        d.set_label(label);
        std::string key_str = std::to_string(i);
        const std::string& value = d.SerializeAsString();
        d.Clear();
        transaction->Put(key_str, value);

        if (++counter % 1000 == 0) {
            transaction->Commit();
        }

    }

    if (count % 1000 != 0) {
        transaction->Commit();
    }

    lmdb.Close();

}

void marfix_stt::test_lmdb::insert_bug_data(int red_min, int red_max, int blue_min, int blue_max, int green_min, int green_max, int count)
{
    int label , counter = 0;
    int r, b, g;
    LMDB lmdb;
    lmdb.Open(db_name, Mode::WRITE);
    LMDBTransaction* transaction = lmdb.NewTransaction();

    for (int i = 0 ; i <= count ; i++) {
        caffe::Datum d;
        d.set_channels(1);
        d.set_height(1);
        d.set_width(3);
        r = get_random_number(red_min, red_max);
        b = get_random_number(blue_min, blue_max);
        g = get_random_number(green_min, green_max);
        label = get_bug(r, g, b);
        std::cout << "R = " << r << " G = " << g << " B = " << b << " label = " << label << std::endl ;
        d.set_label(label);
        d.add_float_data(r);
        d.add_float_data(g);
        d.add_float_data(b);
        std::string key_str = std::to_string(i);
        const std::string& value = d.SerializeAsString();
        d.Clear();
        transaction->Put(key_str, value);

        if (++counter % 1000 == 0) {
            transaction->Commit();
        }

    }

    if (count % 1000 != 0) {
        transaction->Commit();
    }

    lmdb.Close();

}

int marfix_stt::test_lmdb::get_bug(int red, int green, int blue)
{
    if (red >= 100 && blue <= 50 && green < red) {
        return 1;
    }

    else if (red < blue && blue >= 100 && green <= 50) {
        return 3;
    }

    else if (red <= 50 && blue < green && green >= 100) {
        return 2;
    }

    else {
        return 0;
    }
}
int marfix_stt::test_lmdb::get_random_number(int min, int max)
{
    std::random_device rd;
    std::mt19937_64 ed(rd());
    std::uniform_real_distribution<> dist(min, max);
    int random = dist(ed);
    return random;
}

std::vector<std::vector <double>> marfix_stt::test_lmdb::readAll(long vlen)
{
    std::vector<std::vector<double>> data;
    LMDB lmdb;
    lmdb.Open(db_name, Mode::READ);
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
