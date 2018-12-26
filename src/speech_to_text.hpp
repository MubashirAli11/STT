#ifndef SPEECH_TO_TEXT__HPP
#define SPEECH_TO_TEXT__HPP

#include "stt_common.hpp"
#include <memory>
#include <vector>
#include <string>
#include "sound_recorder.hpp"
#include "word_decoder.hpp"
#include "classifier.hpp"

namespace marfix_stt {

    class IFeatureExtractor;
    class LanguageModel;
    class AcousticModel;
    class Phonetics;

    class SpeechToText {
    public:
        enum class Audio {
            LIVE,
            RECORDED
        };

        /*
         *  FeatureExtractor feature_extractor_;
         *  LanguageModel language_model_;
         *  AcousticModel acoustic_model_;
         *  Decoder decoder_;
         *  Phonetics phonetics_;
         *  SoundRecorder sound_recorder_;
         *
         *  public:
         *  SpeechToText(FeatureExtractor feature_extractor,
         *              LanguageModel language_model,
         *              AcousticModel acoustic_model,
         *              Decoder decoder,
         *              Phonetics phonetics
         *   );
         */
        SpeechToText(Audio audio, std::unique_ptr<marfix_stt::IFeatureExtractor> feature_extractor, std::string neural_net_path, std::string neural_net_weights_path, std::string words_db_path);

        bool Start();
        bool Stop();

        std::vector<SampleType> get_audio_data();

        Audio AudioReaderType()
        {
            return audio_reader_type_;
        }
        void AudioReaderType(Audio audio_reader_type)
        {
            this->audio_reader_type_ = audio_reader_type;
        }
        std::string Recognize(std::string path);

    private:
        SoundRecorder sound_recorder_;
        std::unique_ptr<IFeatureExtractor> feature_extractor_;
        Audio audio_reader_type_;
        WordDecoder word_decoder_;
        Classifier classifier_;
    };
}

#endif // SPEECH_TO_TEXT__HPP
