#include "sound_recorder.hpp"
#include <CppUTest/TestHarness.h>


TEST_GROUP(sound_recorder_test_group)
{

};

TEST(sound_recorder_test_group, constructor_test)
{
    marfix_stt::SoundRecorder sr;
    std::vector<portaudio::Device*> devices = sr.GetInputDevices();
    CHECK(devices.size() > 0);

    for (portaudio::Device* device : devices) {
        CHECK(device != nullptr);
    }
}

TEST(sound_recorder_test_group, methods_test)
{
    marfix_stt::SoundRecorder sr;
    sr.StartRecording();
    sr.StopRecording();
}
