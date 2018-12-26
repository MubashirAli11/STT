#ifndef SENTENCEBREAKER__HPP
#define SENTENCEBREAKER__HPP

#include<string>
#include<fstream>
#include<vector>
#include <sstream>
#include<iostream>
#include<algorithm>

namespace marfix_stt {
    /**
     * @brief ...
     * This Class takes the sentences file as input in constructor, each sentence must be on a new line. It has methods that gives
     * the unique words as ouput.
     */
    class SentenceBreaker {
    public:
        /**
         * @brief ...
         * Initializations
         * @param fileName p_fileName:...
         * Name of the file that contains sentences
         */
        SentenceBreaker(std::string fileName);
        /**
         * @brief ...
         * This Function breaks the given sentences into words
         * @return std::vector< std::std::__cxx11::basic_string< char, std::char_traits< char >, std::std::allocator< char > >, std::allocator< std::std::__cxx11::basic_string< char, std::char_traits< char >, std::std::allocator< char > > > >
         * This vector contains the list of unique words
         */
        std::vector <std::string> GetWords();

        long total_word_count;
        long sentence_count;
    private:
        std::string file_name_;

    };
}
#endif              //   */ SENTENCEBREAKER__HPP
