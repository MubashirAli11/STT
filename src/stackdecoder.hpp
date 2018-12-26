#ifndef STACKDECODER_H
#define STACKDECODER_H
#include "stt_common.hpp"
#include "decoder.hpp"

namespace marfix_stt {

    class Word {
        std::string word;
        double probability;
    public:
        std::string GetWord()
        {
            return word;
        }
    };
    class Sentence {
        int eos;
        std::vector<Word> sentence;
        double score;
    public:
        int Eos()
        {
            return eos;
        }
        void Eos(int eos)
        {
            this->eos = eos;
        }
        void Add(Word word)
        {
            sentence.emplace_back(word);
        }
        void Score(double score)
        {
            this->score = score;
        }
        double Score()
        {
            return score;
        }

        std::string to_string()
        {
            std::string sentence("");

            for (auto i : this->sentence) {
                sentence += i.GetWord();
            }

            return sentence;
        }
    };
    class StackDecoder {
        Sentence Decode();
    };
}

#endif // STACKDECODER_H
