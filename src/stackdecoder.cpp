#include "stackdecoder.hpp"
#include <queue>
#include <list>
using namespace marfix_stt;

Sentence StackDecoder::Decode()
{

    auto cmp = [](Sentence left, Sentence right) {
        return left.Score() < right.Score();
    };
    std::priority_queue<Sentence, std::vector<Sentence>, decltype(cmp)> sentence_queue(cmp);
    sentence_queue.push(Sentence());

    while (!sentence_queue.empty()) {
        Sentence s = sentence_queue.top();
        sentence_queue.pop();

        if (s.Eos() == 0) {
            std::cout << s.to_string() << std::endl;
            break;
        }

        std::list<Word> candidate_next_words; //TODO = fast_matches();

        for (auto w : candidate_next_words) {
            Sentence s_plus_w = s; //TODO Implement assignment constructor
            s_plus_w.Add(w);
            // AcousticModel.AcousticLikelihood(s_plus_w);
            // LanguageModel.CalculateProbability(s_plus_w);
            // ComputeHeurisitics(s_plus_w);
            // if(EndOfSentence){
            s_plus_w.Eos(1);
            sentence_queue.push(s_plus_w);
        }
    }

    return Sentence();
}
