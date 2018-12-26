#include <iostream>
#include "forced_viterbi.hpp"
#include "stt_common.hpp"
#include <caffe/layers/memory_data_layer.hpp>
#include "mfcc_feature_extractor.hpp"
#include <sndfile.hh>
#include <caffe/caffe.hpp>
#include <caffe/net.hpp>
#include <sstream>
#include <vector>
#include "phoneme_dataset.hpp"
#include "word_dataset.hpp"

#include <CppUTest/TestHarness.h>


auto get_output(boost::shared_ptr<caffe::Net<double>> network)
{

    network->ForwardTo(6);
    auto output_blob = network->blob_by_name("prob");
    auto begin = output_blob->cpu_data();
    auto end = begin + output_blob->channels();

    return std::vector<double>(begin, end);
}

TEST_GROUP(neural_net_training)
{
    void setup() {
        MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();
    }
    void teardown() {
        MemoryLeakWarningPlugin::turnOnNewDeleteOverloads();
    }
};
TEST(neural_net_training, add_phoneme_data)
{
    using namespace marfix_stt;

    std::vector<std::pair<std::string, size_t>> phoneme_to_index;

    phoneme_to_index.emplace_back(std::make_pair("p", 0));
    phoneme_to_index.emplace_back(std::make_pair("t_", 1));
    phoneme_to_index.emplace_back(std::make_pair("tsh", 2));
    phoneme_to_index.emplace_back(std::make_pair("d_", 3));
    phoneme_to_index.emplace_back(std::make_pair("r", 4));
    phoneme_to_index.emplace_back(std::make_pair("s", 5));
    phoneme_to_index.emplace_back(std::make_pair("k", 6));
    phoneme_to_index.emplace_back(std::make_pair("n", 7));
    phoneme_to_index.emplace_back(std::make_pair("th", 8));
    phoneme_to_index.emplace_back(std::make_pair("tshh", 9));
    phoneme_to_index.emplace_back(std::make_pair("a_", 10));
    phoneme_to_index.emplace_back(std::make_pair("i_", 11));
    phoneme_to_index.emplace_back(std::make_pair("e_", 12));
    phoneme_to_index.emplace_back(std::make_pair("o_", 13));
    phoneme_to_index.emplace_back(std::make_pair("A", 14));
    phoneme_to_index.emplace_back(std::make_pair("c", 15));

    PhonemeDataset phoneme_dataset("phonemes");
    phoneme_dataset.Add(phoneme_to_index);

    std::vector<std::pair<std::string, std::string>> word_to_phonemes;

    word_to_phonemes.emplace_back(std::make_pair("ایک", "e_ k"));
    word_to_phonemes.emplace_back(std::make_pair("دو", "d_ o_"));
    word_to_phonemes.emplace_back(std::make_pair("تین", "t_ i_ n"));
    word_to_phonemes.emplace_back(std::make_pair("چار", "tsh a_ r"));
    word_to_phonemes.emplace_back(std::make_pair("پانچ", "p A tsh"));
    word_to_phonemes.emplace_back(std::make_pair("چھ", "tshh e_"));
    word_to_phonemes.emplace_back(std::make_pair("سات", "s a_ t_"));
    word_to_phonemes.emplace_back(std::make_pair("آٹھ", "a_ th"));
    word_to_phonemes.emplace_back(std::make_pair("نو", "n c o_"));
    word_to_phonemes.emplace_back(std::make_pair("دس", "d_ c s"));

    WordDataset word_dataset("words");
    word_dataset.Add(word_to_phonemes);

}
TEST(neural_net_training, match_layers_of_file_with_net)
{
    using namespace caffe;
    using namespace marfix_stt;

    Caffe::set_mode(Caffe::CPU);

    SolverParameter solver_param;
    ReadSolverParamsFromTextFileOrDie("../../caffe_model/counting_solver.prototxt", &solver_param);


    shared_ptr<Solver<double>> solver(SolverRegistry<double>::CreateSolver(solver_param));
    shared_ptr<Net<double>> network = solver->net();

    shared_ptr<caffe::Net<double>> test_net = solver->test_nets()[0];

    boost::shared_ptr<MemoryDataLayer<double>> train_input_data_layer = boost::dynamic_pointer_cast<MemoryDataLayer<double>>(network->layer_by_name("Count"));

    boost::shared_ptr<MemoryDataLayer<double>> test_input_data_layer = boost::dynamic_pointer_cast<MemoryDataLayer<double>>(test_net->layer_by_name("Count"));

    MFCCFeatureExtractor mfcc_feature_extractor{13, true, false};

    std::ostringstream file_path;
    const size_t data_set_size = 15;

    PhonemeDataset phonemes("phonemes");
    WordDataset words("words");

    ForcedViterbi forced_viterbi("UWTP");
    forced_viterbi.LoadData();

    size_t index = 400;

    for (size_t j = index; j < index + data_set_size; j++) {
        for (words.SeekToFirst(); words.IsValid(); words.SeekToNext()) {
            std::cout << words.GetCurrentKey() << std::endl;
            std::string word = words.GetCurrentKey();
            file_path << "training_data" << "/" << word << "/" << word << "_" << j << ".wav";

            SndfileHandle wave_file{file_path.str()};
            std::cout << wave_file.frames() << std::endl;
            file_path.str(std::string());

            std::unique_ptr<SampleType[]> frames = std::make_unique<SampleType[]>(wave_file.frames());

            wave_file.readf(frames.get(), wave_file.frames());

            std::vector<SampleType> audio_buffer{frames.get(), frames.get() + wave_file.frames()};

            std::vector<std::vector<double>> cepstral_coefficients = mfcc_feature_extractor.ExtractFeatures(audio_buffer);

            size_t index_of_data_train = 0;
            const size_t data_size = cepstral_coefficients.size() * mfcc_feature_extractor.NumberOfCepstralCoefficients();

            std::unique_ptr<double[]> data_train = std::make_unique<double[]>(data_size);
            std::unique_ptr<double[]> label_train = std::make_unique<double[]>(cepstral_coefficients.size());

            std::vector<std::vector<double>> total_phonemes;

            for (size_t k = 0; k < cepstral_coefficients.size(); k++) {

                size_t index_of_data_test = 0;

                std::unique_ptr<double[]> data_test = std::make_unique<double[]>(data_size);
                std::unique_ptr<double[]> label_test = std::make_unique<double[]>(cepstral_coefficients.size());

                for (size_t l = 0; l < cepstral_coefficients[k].size(); l++) {
                    data_train[index_of_data_train++] = cepstral_coefficients[k][l];
                    data_test[index_of_data_test++] = cepstral_coefficients[k][l];
                }

                label_test[k] = 0;

                test_input_data_layer->Reset(data_test.get(), label_test.get(), 1);
                auto phoneme_probability = get_output(test_net);



                total_phonemes.emplace_back(phoneme_probability);

            }

            std::vector<std::string> adjusted_labels =
                forced_viterbi.GetPath(std::make_pair(words.GetCurrentKey(), words.Phonemes()), total_phonemes);

            for (size_t x = 0; x < adjusted_labels.size(); x++) {
                label_train[x] = phonemes.Phoneme(adjusted_labels[x]);
            }

            train_input_data_layer->set_batch_size(cepstral_coefficients.size());
            train_input_data_layer->Reset(data_train.get(), label_train.get(), adjusted_labels.size());


            solver->Step(1);
            forced_viterbi.UpdateTransitionsCount(total_phonemes);
        }
    }

    forced_viterbi.UpdateTransitionsProbabilities();
}
TEST(neural_net_training, test_layers_test)
{
    using namespace caffe;
    using namespace marfix_stt;

    PhonemeDataset phonemes("phonemes");
    WordDataset words("words");

    Caffe::set_mode(Caffe::CPU);

    MFCCFeatureExtractor mfcc_feature_extractor{13, true, false};

    boost::shared_ptr<caffe::Net<double>> test_net;
    test_net.reset(new caffe::Net<double>("../../caffe_model/counting_model.prototxt", caffe::TEST));


    boost::shared_ptr<MemoryDataLayer<double>> input_data_layer = boost::dynamic_pointer_cast<MemoryDataLayer<double>>(test_net->layer_by_name("Count"));


    auto x  = test_net->layers();

    for (size_t i = 0; i < x.size(); i++) {
        std::cout << i << " " << x[i]->layer_param().name() << std::endl;
    }

    std::ostringstream file_path;


    words.SeekToFirst();
    std::cout << words.GetCurrentKey() << std::endl;

    std::string word = words.GetCurrentKey();
    file_path << "training_data" << "/" << word << "/" << word << "_" << 0 << ".wav";

    SndfileHandle wave_file{file_path.str()};
    std::cout << wave_file.frames() << std::endl;
    file_path.str(std::string());

    std::unique_ptr<SampleType[]> frames = std::make_unique<SampleType[]>(wave_file.frames());

    wave_file.readf(frames.get(), wave_file.frames());

    std::vector<SampleType> audio_buffer{frames.get(), frames.get() + wave_file.frames()};

    std::vector<std::vector<double>> cepstral_coefficients = mfcc_feature_extractor.ExtractFeatures(audio_buffer);

    const size_t data_size = mfcc_feature_extractor.NumberOfCepstralCoefficients();



    std::vector<std::vector<double>> total_phonemes;

    for (size_t k = 0; k < cepstral_coefficients.size(); k++) {
        size_t index_of_data_test = 0;

        std::unique_ptr<double[]> data_test = std::make_unique<double[]>(data_size);
        std::unique_ptr<double[]> label_test = std::make_unique<double[]>(cepstral_coefficients.size());

        for (size_t l = 0; l < cepstral_coefficients[k].size(); l++) {
            data_test[index_of_data_test++] = cepstral_coefficients[k][l];
        }

        label_test[k] = 0;

        input_data_layer->Reset(data_test.get(), label_test.get(), 1);
        auto phoneme_probability = get_output(test_net);

        for (auto x : phoneme_probability) {
            std::cout << x << std::endl;
        }
    }

}
