#ifndef WORD_DECODER_H
#define WORD_DECODER_H

#include<vector>
#include<iostream>
#include<string>
#include<unordered_map>
#include<algorithm>
#include<map>
#include<algorithm>
#include "hidden_markov_model.hpp"
#include "viterbi_decoder.hpp"
#include "word_dataset.hpp"

namespace marfix_stt {

    class WordDecoder {
    private:
        std::unordered_map<std::string, double> word_probability_;
        Lmdb lm1_;
    public:
        WordDecoder(std::string db_path);
        std::string Decode(std::vector<std::vector<double>> mlp_probability);
    };
}

#endif // WORD_DECODER_H
