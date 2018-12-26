#include "word_dataset.hpp"
#include "stt_common.hpp"
#include "database.hpp"
using namespace marfix_stt;

WordDataset::WordDataset(std::string db_path): lmdb_(db_path), lmdb_cursor_(lmdb_)
{
}
bool WordDataset::Add(std::vector<std::pair<std::string, std::string>> words_with_phonemes)
{
    for (size_t i = 0; i < words_with_phonemes.size(); i++) {
        lmdb_.Put(words_with_phonemes[i].first, words_with_phonemes[i].second);
    }

    return true;
}
std::vector<std::string> WordDataset::Phonemes()
{
    return CommonUtility::SplitString(GetCurrentValue());
}
std::vector<std::string> WordDataset::Phonemes(std::string word)
{
    return CommonUtility::SplitString(word);
}
std::string WordDataset::GetCurrentKey()
{
    return lmdb_cursor_.GetCurrentKey();
}
std::string WordDataset::GetCurrentValue()
{
    return lmdb_cursor_.GetCurrentValue();
}
bool WordDataset::IsValid()
{
    return lmdb_cursor_.IsValid();
}
void WordDataset::SeekToFirst()
{
    lmdb_cursor_.SeekToFirst();
}
void WordDataset::SeekToNext()
{
    lmdb_cursor_.SeekToNext();
}
