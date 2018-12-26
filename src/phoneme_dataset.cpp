#include "phoneme_dataset.hpp"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <sstream>

using namespace marfix_stt;

PhonemeDataset::PhonemeDataset(std::string db_path):
    lmdb_(db_path), lmdb_cursor_(lmdb_)
{
}

bool PhonemeDataset::Add(std::vector<std::pair<std::string, index>> phonemes)
{
    for (index i = 0; i < phonemes.size(); i++) {
        std::ostringstream serialized;
        boost::archive::text_oarchive oa(serialized);
        oa << phonemes[i].second;
        lmdb_.Put(phonemes[i].first, serialized.str());
    }

    return true;
}

PhonemeDataset::index PhonemeDataset::Phoneme()
{
    std::istringstream deserialized;
    deserialized.str(GetCurrentValue());

    boost::archive::text_iarchive ia(deserialized);
    PhonemeDataset::index idx;
    ia >> idx;

    return idx;
}
PhonemeDataset::index PhonemeDataset::Phoneme(std::string phoneme)
{
    std::istringstream deserialized;
    deserialized.str(lmdb_.Get(phoneme));

    boost::archive::text_iarchive ia(deserialized);
    PhonemeDataset::index idx;
    ia >> idx;

    return idx;
}

std::string PhonemeDataset::GetCurrentKey()
{
    return lmdb_cursor_.GetCurrentKey();
}

std::string PhonemeDataset::GetCurrentValue()
{
    return lmdb_cursor_.GetCurrentValue();
}

bool PhonemeDataset::IsValid()
{
    return lmdb_cursor_.IsValid();
}

void PhonemeDataset::SeekToFirst()
{
    lmdb_cursor_.SeekToFirst();
}

void PhonemeDataset::SeekToNext()
{
    lmdb_cursor_.SeekToNext();
}
