#ifndef HIDDENMARKOVMODEL_H
#define HIDDENMARKOVMODEL_H


#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>
#include <random>
#include <sstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include "phoneme_dataset.hpp"
#include "acoustic_model.hpp"
#include "word_dataset.hpp"
namespace marfix_stt {

    class HiddenMarkovModel: public AcousticModel {
    private:
        /**
         * @brief  vector containing based on hmm states each state representing sub phonemes
         *
         */
        std::vector<std::string> states_;

        std::vector<std::string> observations_;

        /**
         * @brief hold initial probabilities taken according to the probabilities of starting phoneme.
         *
         */
        std::unordered_map<std::string, double> initial_probabilities_;
        /**
         * @brief hold final probabilities taken according to the probabilities of ending phoneme ...
         *
         */
        std::unordered_map<std::string, double> final_probabilities_;
        /**
         * @brief emission_probabilities_ which will be trained from forced viterbi...
         *
         */
        std::unordered_map<std::string, std::unordered_map<std::string, double>> transition_probabilities_;
        /**
         * @brief emision probabilities which will take from neural network...
         *
         */
        std::unordered_map<std::string, std::unordered_map<std::string, double>>
                emission_probabilities_;
    public:

        void LoadData();

        /**
         * @brief  representing sub phones in hmm state row wise and frames of each sub phones column wise
         *   each frame represents an observation ...
         *
         * @param phonemes p_phonemes_:...
         * @return std::vector< std::std::__cxx11::basic_string< char, std::char_traits< char >, std::allocator< char > >, std::allocator< std::std::__cxx11::basic_string< char, std::char_traits< char >, std::allocator< char > > > >
         */
        std::vector<std::string> AssignPhonemeStates(std::vector<std::string> phonemes);

        /**
         * @brief Assign initial probabilities for the start states's transition which has been chosen randomly ...

         */
        std::unordered_map<std::string, double> AssignInitialProbabilities();
        /**
         * @brief Assign final probabilities for the transition to the end state  which has been chosen randomly...

         */
        std::unordered_map<std::string, double> AssignFinalProbabilities();
        /**
         * @brief initially assign transition probabilities to 0.5 for loop back and next transition else is 0  ...

         */
        std::unordered_map<std::string, std::unordered_map<std::string, double>> AssignTransitionProbabilities();
        /**
         * @brief initially chosen emission probabilities randomly  ...

         */
        std::unordered_map<std::string, std::unordered_map<std::string, double>> AssignEmissionProbabilities(std::vector<std::vector<double>> mlp_probabilities);


        //// Getters Setters

        void States(std::vector<std::string> states)
        {
            this-> states_ = states;
        }
        std::vector<std::string> GetStates()
        {
            return this->states_;
        }

        void Observations(std::vector<std::string> observations)
        {
            this->observations_ = observations;
        }

        std::vector<std::string> GetObservations()
        {
            return this->observations_;
        }

        void InitialProbabilities(std::unordered_map<std::string, double> initial_probabilities)
        {
            this->initial_probabilities_ = initial_probabilities;
        }
        std::unordered_map<std::string, double> GetInitialProbabilities()
        {
            return this->initial_probabilities_;
        }


        void FinalProbabilities(std::unordered_map<std::string, double> final_probabilities)
        {
            this->final_probabilities_ = final_probabilities;
        }
        std::unordered_map<std::string, double> GetFinalProbabilities()
        {
            return this->final_probabilities_;
        }


        void TransitionProbabilities(std::unordered_map<std::string, std::unordered_map<std::string, double>> transition_probabilities)
        {
            this->transition_probabilities_ = transition_probabilities;
        }
        std::unordered_map<std::string, std::unordered_map<std::string, double>> GetTransitionProbabilities()
        {
            return this->transition_probabilities_;
        }

        void EmissionProbabilities(std::unordered_map<std::string, std::unordered_map<std::string, double>> emission_probabilities)
        {
            this->emission_probabilities_ = emission_probabilities;
        }
        std::unordered_map<std::string, std::unordered_map<std::string, double>> GetEmissionProbabilities()
        {
            return this->emission_probabilities_;
        }
    };
}

#endif // HIDDENMARKOVMODEL_H
