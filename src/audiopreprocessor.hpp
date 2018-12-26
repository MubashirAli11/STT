#ifndef AUDIOPREPROCESSOR_HPP
#define AUDIOPREPROCESSOR_HPP
#include "stt_common.hpp"
namespace marfix_stt {
    class AudioPreprocessor {
    public:
        AudioPreprocessor(size_t frame_length, size_t frame_step);
        std::vector<std::vector<double>>
                                      Preprocess(const std::vector<SampleType>& audio_buffer);
    private:
        std::vector<double> windowed_audio_buffer_;
        size_t frame_length_;
        size_t frame_step_;
    };
}

#endif // AUDIOPREPROCESSOR_HPP
