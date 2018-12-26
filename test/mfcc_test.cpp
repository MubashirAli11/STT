#include "stt_common.hpp"
#include "mfcc_feature_extractor.hpp"
#include "dsp_math.hpp"
#include <iomanip>
#include <sndfile.hh>
#include <CppUTest/TestHarness.h>

TEST_GROUP(mfcc_test_group)
{

};

TEST(mfcc_test_group, FeatureExtractionTestOriginalData)
{
    /*  using namespace std;
      using namespace marfix_stt;

     vector<double> windowed_audio_buffer;
     ifstream file("data.txt");
     CHECK_EQUAL(file.is_open(), !0);
     vector<double> real, img, fftresult;

     for (std::string line; std::getline(file, line);) {
       windowed_audio_buffer.emplace_back(stod(line));
     }

     CHECK_EQUAL(512, windowed_audio_buffer.size());
     file.close();

      MelFrequencyCepstralCoefficients mfcc(13, true, false);
      std::vector<double> cepstral_coefficients = mfcc.ExtractFeatures(windowed_audio_buffer);


       ofstream mfcc_file("mfcc_file_windowed_data.txt", std::ios::trunc);

       copy(cepstral_coefficients.begin(), cepstral_coefficients.end(), ostream_iterator<double>(mfcc_file, "\n"));*/

}
TEST(mfcc_test_group, FeatureExtractionTestWindowedData)
{

}
TEST(mfcc_test_group, FeatureExtractionTestOverlapping)
{
    /*
     using namespace std;
     using namespace marfix_stt;

    vector<double> windowed_audio_buffer;
    vector<SampleType> audio_buffer;
    ifstream file("english16000.txt");
    CHECK_EQUAL(file.is_open(), !0);
    vector<double> real, img, fftresult;

    for (std::string line; std::getline(file, line);) {
      audio_buffer.emplace_back(stod(line));
    }

    audio_buffer.resize(400);
    audio_buffer.insert(audio_buffer.end(), 112, 0);
    CHECK_EQUAL(512, audio_buffer.size());
    file.close();
      windowed_audio_buffer = DSPMath::ConvertMicBufferToWindowedBuffer(audio_buffer);
     MelFrequencyCepstralCoefficients mfcc(13, true, false);
     std::vector<std::vector<double>> cepstral_coefficients = mfcc.ExtractFeatures(audio_buffer);


      ofstream mfcc_file("mfcc_file_overlapping.txt", std::ios::trunc);

       for ( auto i : cepstral_coefficients){
          copy(i.begin(), i.end(), ostream_iterator<double>(mfcc_file, " "));
          mfcc_file << "\n";
      }*/
}
TEST(mfcc_test_group, FeatureExtractionTestStepByStep)
{
    /*
      using namespace std;
      using namespace marfix_stt;

     vector<double> windowed_audio_buffer;
     vector<SampleType> audio_buffer;
     ifstream file("english16000full.txt");
     CHECK_EQUAL(file.is_open(), !0);
     vector<double> real, img, fftresult;

     for (std::string line; std::getline(file, line);) {
       audio_buffer.emplace_back(stod(line));
     }
     file.close();*/
    using namespace marfix_stt;
    using namespace std;
    SndfileHandle test("/home/abdulrehman/Workspace/cpp/kdevelop-workspace/stt-project-data/speaker-recognition/seed/faraz.wav");

    SampleType* samples = new SampleType[test.frames()];
    std::vector<SampleType> audio_buffer;
    test.readf(samples, test.frames());
    audio_buffer.assign(samples, samples + test.frames());
    delete[] samples;
    std::cout << test.frames();

    MFCCFeatureExtractor
    mfcc(13, true, true);

    std::vector<std::vector<double>> cepstral_coefficients = mfcc.ExtractFeatures(audio_buffer);


    ofstream mfcc_file("mfcc_file_overlapping.txt", std::ios::trunc);

    for (auto i : cepstral_coefficients) {
        copy(i.begin(), i.end(), ostream_iterator<double>(mfcc_file, "\n"));
    }

}
