#include "searchncount.hpp"


namespace {
    std::vector <std::string> GetAllWords(std::string sentence)
    {
        std::vector <std::string> words_row;
        sentence.erase(std::remove(sentence.begin(), sentence.end(), '\n'),
                       sentence.end());
        std::stringstream ss;
        ss.str(sentence);
        std::string sub_item;

        while (std::getline(ss, sub_item, ' ')) {
            if (!sub_item.empty()) {
                sub_item.erase(std::remove
                               (sub_item.begin(), sub_item.end(), '\n'),
                               sub_item.end());
                words_row.push_back(sub_item);
            }
        }

        return words_row;
    }
}

using namespace marfix_stt;

SearchNCount::SearchNCount(std::vector <std::string> sentences)
{
    for (size_t i = 0; i < sentences.size(); i++) {
        std::vector<std::string> splited_words = GetAllWords(sentences[i]);
        words.push_back(splited_words);

    }
}

long
SearchNCount::GetNonUniqueCounts(std::string word)
{
    long   count = 0;

    for (unsigned long i = 0; i < words.size(); i++) {
        for (unsigned int w = 0; w < words[i].size(); w++) {
            if (word.compare(words[i][w]) == 0) {
                count++;
            }

        }
    }

    return count;
}



long
SearchNCount::GetNonUniqueCounts(std::string word, std::string word1)
{
    long   count = 0;

    for (unsigned long i = 0; i < words.size(); i++) {
        for (unsigned int w = 0; w < words[i].size(); w++) {
            if (w + 1 < words[i].size()) {
                if ((word.compare(words[i][w]) == 0 && word1.compare(words[i][w + 1]) == 0)) {
                    count++;
                }
            }
        }
    }

    return count;
}


long
SearchNCount::GetNonUniqueCounts(std::string word, std::string word1, std::string word2)
{
    long   count = 0;

    for (unsigned long i = 0; i < words.size(); i++) {
        for (unsigned int w = 0; w < words[i].size(); w++) {
            if (w + 2 < words[i].size()) {
                if ((word.compare(words[i][w]) == 0 && word1.compare(words[i][w + 1]) == 0 && word2.compare(words[i][w + 2]) == 0)) {
                    count++;

                }
            }
        }
    }

    return count;
}

long
SearchNCount::GetUniqueCounts(std::string word, std::string word1)
{
    std::string combo = "";
    unsigned        count = 0;

    for (unsigned long i = 0; i < words.size(); i++) {
        for (unsigned int w = 0; w < words[i].size(); w++) {
            if (w + 1 < words[i].size()) {
                if ((word.compare("dot") == 0 && word1.compare(words[i][w + 1]) == 0)
                        || (word.compare(words[i][w]) == 0 && word1.compare("dot") == 0)) {
                    if (combo.find(words[i][w] + words[i][w + 1]) == std::string::npos) {
                        count++;
                        combo += (words[i][w] + words[i][w + 1]);
                    }
                }
            }
        }

        combo += " ";
    }

    return count;
}


long
SearchNCount::GetUniqueCounts(std::string word, std::string word1, std::string word2)
{
    unsigned count = 0;
    std::string combo = "";

    for (unsigned long i = 0; i < words.size(); i++) {
        for (unsigned int w = 0; w < words[i].size(); w++) {
            if (w + 2 < words[i].size()) {
                if ((word.compare(words[i][w]) == 0 && word1.compare(words[i][w + 1]) == 0 && word2.compare("dot") == 0)
                        || (word.compare("dot") == 0 && word1.compare(words[i][w + 1]) == 0 && word2.compare(words[i][w + 2]) == 0)) {
                    if (combo.find(words[i][w] + words[i][w + 1] + words[i][w + 2]) == std::string::npos) {
                        count++;
                        combo += (words[i][w] + words[i][w + 1] + words[i][w + 2]);
                    }
                }
            }
        }

        combo += " ";
    }

    return count;
}
