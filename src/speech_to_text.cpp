#include "language_model.hpp"
#include "acoustic_model.hpp"
#include <sndfile.hh>
#include "decoder.hpp"
#include "phonetics.hpp"
#include "classifier.hpp"
#include "word_decoder.hpp"
#include "mfcc_feature_extractor.hpp"
#include "speech_to_text.hpp"

using namespace marfix_stt;

/*
SpeechToText::SpeechToText(FeatureExtractor feature_extractor, LanguageModel language_model, AcousticModel acoustic_model, Decoder decoder, Phonetics phonetics):
feature_extractor_(feature_extractor),
language_model_(language_model),
acoustic_model_(acoustic_model),
decoder_(decoder),
phonetics_(phonetics)
{
}*/
SpeechToText::SpeechToText(marfix_stt::SpeechToText::Audio audio, std::unique_ptr<IFeatureExtractor> feature_extractor, std::string neural_net_path, std::string neural_net_weights_path, std::string words_db_path):
    audio_reader_type_(audio), word_decoder_(words_db_path), classifier_(neural_net_path, neural_net_weights_path)
{
    feature_extractor_.swap(feature_extractor);
}


bool SpeechToText::Start()
{

    // sound_recorder_.StartRecording();
    // std::vector<std::vector<double>> cepstral_coefficients = feature_extractor_.Extract(get_audio_data());
    // std::vector<double> probabilities = neural_net_.Forward(cepstral_coefficients);

}
bool SpeechToText::Stop()
{
    // deallocate all resources
}

std::string SpeechToText::Recognize(std::string path)
{
    using namespace caffe;
    using namespace marfix_stt;

    SndfileHandle wave_file{path};

    std::unique_ptr<SampleType[]> frames = std::make_unique<SampleType[]>(wave_file.frames());

    wave_file.readf(frames.get(), wave_file.frames());

    std::vector<SampleType> audio_buffer{frames.get(), frames.get() + wave_file.frames()};

    std::vector<std::vector<double>> cepstral_coefficients = feature_extractor_->ExtractFeatures(audio_buffer);

    std::vector<std::vector<double>> total_phonemes;

    for (size_t k = 0; k < cepstral_coefficients.size(); k++) {
        auto phoneme_probability = classifier_.Predict(cepstral_coefficients[k]);
        total_phonemes.emplace_back(phoneme_probability);
    }

    return word_decoder_.Decode(total_phonemes);
}

std::vector<SampleType> SpeechToText::get_audio_data()
{
    if (AudioReaderType() == Audio::LIVE) {

    }
    else if (AudioReaderType() == Audio::RECORDED) {

    }
}
