#ifndef LMDBCURSOR_H
#define LMDBCURSOR_H

#include<string>
#include "database.hpp"

namespace marfix_stt {
    class LmdbCursor {
    public:
        LmdbCursor(const Lmdb& lmdb);
        std::string GetCurrentValue();
        std::string GetCurrentKey();
        void SeekToFirst();
        void SeekToNext();
        bool IsValid();
        ~LmdbCursor()
        {
            mdb_cursor_close(cursor_);
            mdb_txn_abort(txn_);
        }

    private:
        void Seek(MDB_cursor_op op)
        {
            int status = mdb_cursor_get(cursor_, &mdb_key_, &mdb_value_, op);

            if (status == MDB_NOTFOUND) {
                valid_ = false;
            }

            else {
                valid_ = true;
            }
        }
        MDB_cursor* cursor_;
        MDB_val mdb_key_, mdb_value_;
        MDB_txn* txn_;
        bool valid_;
    };
}
#endif // LMDBCURSOR_H
