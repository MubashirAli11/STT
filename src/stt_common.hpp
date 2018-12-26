#ifndef STT_COMMON__HPP
#define STT_COMMON__HPP

#include <cstdint>
#include <limits>
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <algorithm>
#include <numeric>
#include <portaudio.h>
#include <portaudiocpp/PortAudioCpp.hxx>
#include <caffe/util/db_lmdb.hpp>
#include <cstddef>
#include <cmath>
#include <type_traits>
#include <random>
#include <time.h>
#include <map>
#include <sstream>
#include <unordered_map>
#include "database.hpp"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>



namespace marfix_stt {
    using SampleType = std::int16_t; // 16-bit samples

    enum class Channel {
        Mono = 1, Stereo = 2
    };

    enum class SampleRate {
        kHz_8 = 8000,
        kHz_9_6 = 9600,
        kHz_11_025 = 11025,
        kHz_12 = 12000,
        kHz_16 = 16000,
        kHz_22_05 = 22050,
        kHz_24 = 24000,
        kHz_32 = 32000,
        kHz_44_1 = 44100,
        kHz_48 = 48000,
        kHz_88_2 = 88200,
        kHz_96 = 96000
    };

    template<typename E>
    constexpr auto ToUnderlyingType(E enumerator) noexcept
    {
        return static_cast<std::underlying_type_t<E>>(enumerator);
    }
    namespace AudioFormat {

        const SampleRate SelectedSampleRate = SampleRate::kHz_16;
        const Channel SelectedChannel = Channel::Mono;
        const std::size_t BufferSize = 512;
    }

    namespace LmdbStream {

        void ReadData(Lmdb& lm1, std::string word, std::vector<std::string>phonemes, std::map<std::string, std::map<std::string, double>>& transition_counts, std::map<std::string, double>& state_i);

        void WriteData(Lmdb& lm1,  std::string word, std::vector<std::string>phonemes, std::map<std::string, std::map<std::string, double>>& transition_counts, std::map<std::string, double>& state_i);

        void WriteTransitionProbability(Lmdb& lm1, std::string word, std::vector<std::string>phonemes, std::unordered_map<std::string, std::unordered_map<std::string, double>> transition_probabilities);

        std::unordered_map<std::string, std::unordered_map<std::string, double>> ReadTransitionProbability(Lmdb& lm1, std::string word, std::vector<std::string> phonemes);
    }

    namespace CommonUtility {
        std::vector<std::string> SplitString(std::string str);
        double GetRandomNumber(double min, double max);

        inline bool PairCompare(const std::pair<double, int>& lhs,
                                const std::pair<double, int>& rhs)
        {
            return lhs.first > rhs.first;
        }

        std::vector<int> Argmax(const std::vector<double>& v, int N);
    }

    namespace HybridApproach {
        std::vector<std::vector<double>> GiveScaledEmissionProbability(std::vector<std::vector<double>> mlp_probabilities);
    }

}
#endif // STT_COMMON__HPP
