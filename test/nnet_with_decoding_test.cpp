#include <iostream>
#include "stt_common.hpp"
#include "mfcc_feature_extractor.hpp"
#include <sndfile.hh>
#include <caffe/caffe.hpp>
#include <caffe/net.hpp>
#include <sstream>
#include <vector>
#include "word_decoder.hpp"
#include "phoneme_dataset.hpp"
#include "word_dataset.hpp"
#include "classifier.hpp"

#include <CppUTest/TestHarness.h>

TEST_GROUP(nnet_with_decoding)
{
    void setup() {
        MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();
    }
    void teardown() {
        MemoryLeakWarningPlugin::turnOnNewDeleteOverloads();
    }
};
TEST(nnet_with_decoding, words)
{
    using namespace marfix_stt;
    WordDataset words("words");

    for (words.SeekToFirst(); words.IsValid(); words.SeekToNext()) {
        //      std::cout << words.GetCurrentKey() << std::endl;
    }
}
TEST(nnet_with_decoding, decoding)
{
    using namespace caffe;
    using namespace marfix_stt;

    Caffe::set_mode(Caffe::CPU);

    MFCCFeatureExtractor mfcc_feature_extractor{13, true, false};

    std::ostringstream file_path;

    PhonemeDataset phonemes("phonemes");
    WordDataset words("words");
    WordDecoder word_decoder("UWTP");

    Classifier classifier("../../caffe_model/counting_deploy.prototxt", "counting_net_iter_150.caffemodel");
    //آٹھ 5
    //ایک 0
    //تین 0

    //دس not tested
    //دو 3
    //سات 0
    //نو 1
    //پانچ 1
    //چار 1
    //چھ 0


    //  words.SeekToFirst();
    /*  words.SeekToNext();
      words.SeekToNext();
      words.SeekToNext();
      words.SeekToNext();
      words.SeekToNext();
      words.SeekToNext();
      words.SeekToNext();
      words.SeekToNext();
      words.SeekToNext();*/
    std::ofstream file("decoding.txt", std::ios::trunc);

    for (words.SeekToFirst(); words.IsValid(); words.SeekToNext()) {
        int counter = 0;
        file << words.GetCurrentKey() << std::endl;

        for (size_t i = 1; i <= 399; i++) {
            std::string word = words.GetCurrentKey();

            file_path << "training_data" << "/" << word << "/" << word << "_" << i << ".wav";
            // file_path << "TestSet" << "/" << word << "/" << 3 << ".wav";
            std::string path = file_path.str();
            SndfileHandle wave_file{file_path.str()};
            std::cout << wave_file.frames() << std::endl;
            file_path.str(std::string());

            std::unique_ptr<SampleType[]> frames = std::make_unique<SampleType[]>(wave_file.frames());

            wave_file.readf(frames.get(), wave_file.frames());

            std::vector<SampleType> audio_buffer{frames.get(), frames.get() + wave_file.frames()};

            std::vector<std::vector<double>> cepstral_coefficients = mfcc_feature_extractor.ExtractFeatures(audio_buffer);

            std::vector<std::vector<double>> total_phonemes;

            for (size_t k = 0; k < cepstral_coefficients.size(); k++) {

                //            std::cout << "frame number: " << k << std::endl;
                auto phoneme_probability = classifier.Predict(cepstral_coefficients[k]);
                /*
                for (size_t i = 0; i < phoneme_probability.size(); i++){
                    std::cout << i << " " << phoneme_probability[i] << std::endl;
                }*/

                total_phonemes.emplace_back(phoneme_probability);

            }

            std::string recognized_word = word_decoder.Decode(total_phonemes);
            std::cout << word << std::endl;
            std::cout << recognized_word << std::endl;

            if (word.compare(recognized_word) != 0) {
                file << "Suspicious File: " << path << std::endl;

                counter++;
            }
        }

        file << "Incorrectly Recognized: " << counter << " times for " << words.GetCurrentKey() << std::endl;
    }
}
