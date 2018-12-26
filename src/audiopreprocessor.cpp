#include "audiopreprocessor.hpp"
#include "dsp_math.hpp"

using namespace marfix_stt;
AudioPreprocessor::AudioPreprocessor(size_t frame_length, size_t frame_step)
{
    this->frame_length_ = frame_length;
    this->frame_step_ = frame_step;
}

std::vector<std::vector<double>> AudioPreprocessor::Preprocess(const std::vector<SampleType>& audio_buffer)
{

    windowed_audio_buffer_ = DSPMath::ConvertMicBufferToWindowedBuffer(audio_buffer);

    size_t n_frames = 0;
    size_t size_audio_buffer = windowed_audio_buffer_.size();

    if (size_audio_buffer <= frame_length_) {
        n_frames = 1;
    }

    else {
        n_frames = 1 + ceil((size_audio_buffer - frame_length_) / (1.0 * frame_step_));
    }

    size_t pad_len = (n_frames - 1) * frame_step_ + frame_length_;

    if (pad_len > 0) {
        windowed_audio_buffer_.insert(windowed_audio_buffer_.end(), (pad_len - size_audio_buffer), 0.0);
        size_audio_buffer = windowed_audio_buffer_.size();
    }

    std::vector<std::vector<double>> frames(n_frames, std::vector<double> (frame_length_, 0.0));

    for (size_t i = 0, f_step = 0; i < n_frames; i++, f_step += frame_step_) {
        copy_n(windowed_audio_buffer_.begin() + f_step, frame_length_, frames[i].begin());
    }

    return frames;
}
