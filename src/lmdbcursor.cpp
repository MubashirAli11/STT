#include "lmdbcursor.hpp"
using namespace marfix_stt;

LmdbCursor::LmdbCursor(const marfix_stt::Lmdb& lmdb)
{
    valid_ = false;
    MDB_dbi dbi;
    int rc = 0;

    rc = mdb_txn_begin(lmdb.env_, NULL, MDB_RDONLY, &txn_);
    rc = mdb_dbi_open(txn_, NULL, 0, &dbi);
    rc = mdb_cursor_open(txn_, dbi, &cursor_);

    if (rc == MDB_SUCCESS) {
        std::cout << "Lmdb Cursor Opened.\n";
    }

}

bool LmdbCursor::IsValid()
{
    return valid_;
}

void LmdbCursor::SeekToFirst()
{
    Seek(MDB_FIRST);
}

void LmdbCursor::SeekToNext()
{
    Seek(MDB_NEXT);
}

std::string LmdbCursor::GetCurrentValue()
{
    std::string str((char*)mdb_value_.mv_data, mdb_value_.mv_size);
    return str;
}

std::string LmdbCursor::GetCurrentKey()
{
    std::string str((char*)mdb_key_.mv_data, mdb_key_.mv_size);
    return str;
}
