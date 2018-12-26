#ifndef SEARCHNCOUNT__HPP
#define SEARCHNCOUNT__HPP

#include <string>
#include <vector>
#include <sstream>
#include<iostream>
#include<algorithm>

namespace marfix_stt {


    /**
     * @brief ...
     * This Function takes a single sentence as input and returns a vectors of all of its words.
     * @param sentence p_sentence:... A Single Sentence
     * @return std::vector< std::std::__cxx11::basic_string< char, std::char_traits< char >, std::std::allocator< char > >, std::allocator< std::std::__cxx11::basic_string< char, std::char_traits< char >, std::std::allocator< char > > > >
     */



    /**
     * @brief ...
     * This class counts given sequences uniquely and non-uniquely in the corpus.
     */
    class SearchNCount {
    public:
        /**
         * @brief ...
         * Initializations
         * @param sentences p_sentences:...List of sentences
         */
        SearchNCount(std::vector<std::string> sentences);

        /**
         * @brief ...
         * This functions returns the count of the given word.
         * @return long int
         */
        long GetNonUniqueCounts(std::string word);



        /**
         * @brief ...
         * This functions returns the count of the given two consecutive words.
         * @return long int
         */
        long GetNonUniqueCounts(std::string word, std::string word1);


        /**
         * @brief ...
         * This functions returns the count of the given three consecutive words.
         * @return long int
         */
        long GetNonUniqueCounts(std::string word, std::string word1, std::string word2);

        /**
         * @brief ...
         * This functions returns the unique count of the given two consecutive words, any of the given word can contain dot.
         * @return long int
         */
        long GetUniqueCounts(std::string word, std::string word1);


        /**
         * @brief ...
         * This functions returns the unique count of the given two consecutive words, any of the given word can contain dot.
         * @return long int
         */
        long GetUniqueCounts(std::string word, std::string word1, std::string word2);

    private:
        std::vector<std::vector<std::string>> words;

    };

}
#endif // SEARCHNCOUNT__HPP
