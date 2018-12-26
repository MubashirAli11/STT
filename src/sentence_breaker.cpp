#include "sentence_breaker.hpp"

using namespace marfix_stt;

SentenceBreaker::SentenceBreaker(std::string file_name)
{
    this->file_name_ = file_name;
    total_word_count = 0;
    sentence_count = 0;
}

std::vector <std::string> marfix_stt::SentenceBreaker::GetWords()
{
    std::vector <std::string> all_words;
    std::vector <std::string> words;
    std::ifstream infile;
    infile.open(file_name_);
    std::string item;

    while (std::getline(infile, item)) {
        item.erase(std::remove(item.begin(), item.end(), '\n'),
                   item.end());
        std::stringstream ss;
        ss.str(item);
        std::string sub_item;
        sentence_count++;

        while (std::getline(ss, sub_item, ' ')) {
            if (!sub_item.empty()) {
                sub_item.erase(std::remove
                               (sub_item.begin(), sub_item.end(), '\n'),
                               sub_item.end());
                all_words.push_back(sub_item);
            }
        }
    }

    total_word_count = all_words.size();
    std::sort(all_words.begin(), all_words.end());
    std::unique_copy(all_words.begin(), all_words.end(),
                     std::back_inserter(words));
    infile.close();
    return words;
}
