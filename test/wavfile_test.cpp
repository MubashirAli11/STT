#include <sndfile.hh>
#include <iostream>
#include <memory>
#include "stt_common.hpp"
#include "phoneme_dataset.hpp"
#include <CppUTest/TestHarness.h>

TEST_GROUP(Wavfile)
{

};

TEST(Wavfile, WavFileReading)
{
    using namespace marfix_stt;
    SndfileHandle sfh("/home/abdulrehman/Workspace/cpp/kdevelop-workspace/stt-project-data/english16k.wav");
    std::cout << sfh.channels() << std::endl;
    std::cout << sfh.frames() << std::endl;
    std::cout << sfh.samplerate() << std::endl;
    //  SampleType* frames = new SampleType[sfh.frames()];
    std::unique_ptr<SampleType[]> frames = std::make_unique<SampleType[]>(sfh.frames());
    sfh.readf(frames.get(), sfh.frames());

    for (int i = 0; i < sfh.frames(); i++) {
        std::cout << frames.get()[i] << std::endl;
    }

    //  delete[] frames;

}
