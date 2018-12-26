#ifndef PHONEMEDATASET_H
#define PHONEMEDATASET_H

#include <string>
#include <vector>
#include "lmdbcursor.hpp"
#include "database.hpp"

namespace marfix_stt {
    class PhonemeDataset {
    private:
        Lmdb lmdb_;
        LmdbCursor lmdb_cursor_;
    public:
        using index = size_t;
        PhonemeDataset(std::string db_path);

        bool Add(std::vector<std::pair<std::string, index>> phonemes);

        index Phoneme();
        index Phoneme(std::string phoneme);

        bool IsValid();
        void SeekToFirst();
        void SeekToNext();

        std::string GetCurrentKey();
        std::string GetCurrentValue();


    };
}

#endif // PHONEMEDATASET_H
