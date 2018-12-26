#include <sndfile.hh>
#include <iostream>
#include "stt_common.hpp"
#include "mfcc_feature_extractor.hpp"
#include "kmeans.hpp"
#include <sstream>
#include <CppUTest/TestHarness.h>

std::string GetInfo(SndfileHandle& file)
{

    std::cout << file.format() << std::endl;
    std::cout << file.channels() << std::endl;
    std::cout << file.frames() << std::endl;
    return file.strError();
}
std::vector<double> GetFeatures(SndfileHandle& file)
{
    using namespace marfix_stt;
    std::vector<double> features_of_speaker(13, 0.0);
    SampleType* samples = new SampleType[file.frames()];
    std::vector<SampleType> audio_buffer;
    file.read(samples, file.frames());
    audio_buffer.assign(samples, samples + file.frames());
    delete[] samples;
    std::cout << file.format() << std::endl;
    MFCCFeatureExtractor mfcc(13, true, false);

    std::vector<std::vector<double>> cepstral_coefficients = mfcc.ExtractFeatures(audio_buffer);

    for (size_t x = 0; x < cepstral_coefficients.size(); x++) {
        for (size_t z = 0; z < cepstral_coefficients[x].size(); z++) {
            features_of_speaker[z] += cepstral_coefficients[x][z];
        }
    }

    for (size_t i = 0; i < features_of_speaker.size(); i++) {
        features_of_speaker[i] /= cepstral_coefficients.size();
    }

    return features_of_speaker;
}
TEST_GROUP(SpeakerRecognition)
{
    void setup() override {
        MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();

    }
    void teardown() override {
        MemoryLeakWarningPlugin::turnOnNewDeleteOverloads();
    }
};

TEST(SpeakerRecognition, MFCCTestWithWavfile)
{
    using namespace marfix_stt;
    using namespace std;

    SndfileHandle abdul_rehman("/home/abdulrehman/Workspace/cpp/kdevelop-workspace/stt-project-data/speaker-recognition/seed/abdul_rehman.wav");
    SndfileHandle monis("/home/abdulrehman/Workspace/cpp/kdevelop-workspace/stt-project-data/speaker-recognition/seed/monis.wav");
    SndfileHandle mubashir("/home/abdulrehman/Workspace/cpp/kdevelop-workspace/stt-project-data/speaker-recognition/seed/mubashir.wav");
    SndfileHandle faraz("/home/abdulrehman/Workspace/cpp/kdevelop-workspace/stt-project-data/speaker-recognition/seed/faraz.wav");
    //SndfileHandle sfh("/home/abdulrehman/Workspace/cpp/kdevelop-workspace/stt-project-data/english16k.wav");

    vector<SndfileHandle*> wav_files;
    wav_files.push_back(&abdul_rehman);
    wav_files.push_back(&monis);
    wav_files.push_back(&mubashir);
    wav_files.push_back(&faraz);

    vector<vector<double>> features_of_speakers(4, vector<double>(13, 0.0));
    /*  size_t speaker_index = 0;
      for ( auto i : wav_files){
      SampleType *samples = new SampleType[i->frames()];
      std::vector<SampleType> audio_buffer;
      i->read(samples, i->frames());
      audio_buffer.assign(samples, samples+ i->frames());
      delete[] samples;

      MelFrequencyCepstralCoefficients mfcc(13, true, false);

      std::vector<std::vector<double>> cepstral_coefficients = mfcc.ExtractFeatures(audio_buffer);

      for ( size_t x = 0; x < cepstral_coefficients.size(); x++){
          for ( size_t z = 0; z < cepstral_coefficients[x].size(); z++){
              features_of_speakers[speaker_index][z] += cepstral_coefficients[x][z];
          }
      }
      for ( size_t j = 0; j < features_of_speakers[speaker_index].size(); j++){
              features_of_speakers[speaker_index][j] /= cepstral_coefficients.size();
      }
      speaker_index++;
      }
      wav_files.clear();*/
    long k = 4;

    std::vector<std::string> names = {"abdul_rehman", "monis", "mubashir", "faraz"};


    kmeans k1(k, features_of_speakers, names, false);

    /*
      for (int count = 1; count <= 15; count++)
      {
          ostringstream Astr;
          Astr << "/home/abdulrehman/Workspace/cpp/kdevelop-workspace/stt-project-data/";
          Astr << "speaker-recognition/train/silence.removed.A" << count << ".wav";

          ostringstream Mstr;
          Mstr << "/home/abdulrehman/Workspace/cpp/kdevelop-workspace/stt-project-data/";
          Mstr << "speaker-recognition/train/silence.removed.Monis" << count << ".wav";

          ostringstream Mubstr;
          Mubstr << "/home/abdulrehman/Workspace/cpp/kdevelop-workspace/stt-project-data/";
          Mubstr << "speaker-recognition/train/silence.removed.Mub" << count << ".wav";

          ostringstream Fstr;
          Fstr << "/home/abdulrehman/Workspace/cpp/kdevelop-workspace/stt-project-data/";
          Fstr << "speaker-recognition/train/silence.removed.F" << count << ".wav";

          string Apath = Astr.str();
          string Mpath = Mstr.str();
          string Mubpath = Mubstr.str();
          string Fpath = Fstr.str();
          SndfileHandle abdul_rehman_training_set(Apath.c_str());
          SndfileHandle monis_training_set(Mpath.c_str());
          SndfileHandle mubashir_training_set(Mubpath.c_str());
          SndfileHandle faraz _training_set(Fpath.c_str());


          std::cout << k1.Update_Clusters(0, GetFeatures(abdul_rehman_training_set)); // 0 // 0
          std::cout << k1.Update_Clusters(1, GetFeatures(monis_training_set)); // 1 // 2
          std::cout << k1.Update_Clusters(2, GetFeatures(mubashir_training_set)); // 2 // 3
          std::cout << k1.Update_Clusters(3, GetFeatures(faraz_training_set)); // 3 // 1
      }*/
    std::vector<std::string> names_from_lmdb = {"abdul_rehman", "faraz", "monis", "mubashir"};
    ostringstream Teststr;
    Teststr << "/home/abdulrehman/Workspace/cpp/kdevelop-workspace/stt-project-data/";
    Teststr << "speaker-recognition/test/silence.removed.F17.wav";
    SndfileHandle test_file(Teststr.str());
    std::cout << names_from_lmdb[k1.GetIndex(GetFeatures(test_file))] << std::endl;

}

TEST(SpeakerRecognition, SpeakerRecognitionCombined)
{

}
