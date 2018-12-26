#include "database.hpp"


marfix_stt::Lmdb::Lmdb(std::string source)
{
    int rc = 0;
    rc = mkdir(source.c_str(), 0744);

    if (rc == 0) {
        std::cout << "Database Created.\n";
    }

    else {
        std::cout << "Database already exits.\n";
    }


    rc = mdb_env_create(&env_);

    if (rc == 0) {
        std::cout << "Enviroment Handler Created.\n";
    }

    else {
        std::cout << "Enviroment Handler Cant't Created: " << mdb_strerror(rc) << " .\n";
    }

    rc = mdb_env_open(env_, source.c_str(), 0, 0664);

    if (rc) {
        std::cout << "Enviroment can't be opened " << mdb_strerror(rc) << " .\n";
    }

    else if (rc == 0) {
        std::cout << "Enviroment opened.\n";
    }
}

std::string marfix_stt::Lmdb::Get(std::string key)
{
    int rc = 0;
    char* c_key = (char*)key.c_str();
    MDB_val d_key, data;
    data.mv_data = nullptr;
    data.mv_size = 0;
    MDB_txn* txn = nullptr;
    rc = mdb_txn_begin(env_, NULL, 0, &txn);
    rc = mdb_dbi_open(txn, NULL, 0, &dbi_);
    d_key.mv_size =  key.size();
    d_key.mv_data = c_key;
    rc = mdb_get(txn, dbi_, &d_key, &data);

    if (rc) {
        std::cout << "Data Can't be Found, Error: " << mdb_strerror(rc);
        mdb_dbi_close(env_, dbi_);
        mdb_env_close(env_);
        return "";
    }

    //  else if(r////==0)
    //  std::cout<<"Data Found.\n";
    rc = mdb_txn_commit(txn);

    mdb_dbi_close(env_, dbi_);
    std::string str((char*)data.mv_data, data.mv_size);
    return str;
}


void marfix_stt::Lmdb::Put(std::string key, std::string value)
{
    MDB_txn* txn = nullptr;
    MDB_val d_key, d_data;
    int rc = 0;
    char* c_key = (char*)key.c_str();
    char* c_data = (char*)value.c_str();
    rc = mdb_txn_begin(env_, NULL, 0, &txn);
    rc = mdb_dbi_open(txn, NULL, 0, &dbi_);
    d_key.mv_size =  key.size();
    d_key.mv_data = c_key;
    d_data.mv_size = value.size();
    d_data.mv_data = c_data;
    rc = mdb_put(txn, dbi_, &d_key, &d_data, 0);
    // if (rc==0) {
    // std::cout<<"Data inserted.\n";
    // }
    rc = mdb_txn_commit(txn);

    if (rc) {
        std::cout << "Cannot Commit : " << mdb_strerror(rc);
        mdb_txn_abort(txn);
        mdb_dbi_close(env_, dbi_);
        mdb_env_close(env_);
        return;
    }

    else if (rc == 0) {
        std::cout << "Transaction Completed.\n";
    }
}
