#ifndef DATABASE_H
#define DATABASE_H

#include <sys/stat.h>
#include<string>
#include<vector>
#include<iostream>
#include "lmdb.h"


namespace marfix_stt {

    class LmdbCursor;

    class Lmdb {
    public:
        friend LmdbCursor;
        Lmdb(std::string source);
        void Put(std::string key, std::string value);
        std::string Get(std::string key);
        ~Lmdb()
        {
            mdb_env_close(env_);
        }
    private:
        MDB_env* env_;
        MDB_dbi dbi_;
    };

}

#endif // DATABASE_H
