#include "stt_common.hpp"
#include <sndfile.hh>
#include "audiopreprocessor.hpp"
#include <CppUTest/TestHarness.h>

TEST_GROUP(AudioPreprocessor)
{

};
TEST(AudioPreprocessor, TestFrames)
{

    using namespace marfix_stt;
    using namespace std;
    SndfileHandle test("/home/abdulrehman/Workspace/cpp/kdevelop-workspace/stt-project-data/speaker-recognition/seed/faraz.wav");

    SampleType* samples = new SampleType[test.frames()];
    std::vector<SampleType> audio_buffer;
    test.read(samples, test.frames());
    audio_buffer.assign(samples, samples + test.frames());
    delete[] samples;
    AudioPreprocessor audio_preprocessor(400, 160);
    auto frames = audio_preprocessor.Preprocess(audio_buffer);
    ofstream frames_file("frames.txt", std::ios::trunc);

    for (auto i : frames) {
        copy(i.begin(), i.end(), ostream_iterator<double>(frames_file, "\n"));
    }
}
