#ifndef WORDTOPHONEMEDATASET_HPP
#define WORDTOPHONEMEDATASET_HPP

#include "database.hpp"
#include "lmdbcursor.hpp"
#include "stt_common.hpp"

namespace marfix_stt {

    class WordDataset {
    private:
        Lmdb lmdb_;
        LmdbCursor lmdb_cursor_;
    public:
        using index = size_t;
        WordDataset(std::string db_path);

        bool Add(std::vector<std::pair<std::string, std::string>> words_with_phonemes);

        bool IsValid();
        void SeekToFirst();
        void SeekToNext();
        std::string GetCurrentKey();
        std::string GetCurrentValue();

        std::vector<std::string> Phonemes();
        std::vector<std::string> Phonemes(std::string word);
    };
}

#endif // WORDTOPHONEMEDATASET_HPP
