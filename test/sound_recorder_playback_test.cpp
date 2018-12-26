
#include "sound_recorder.hpp"
#include <CppUTest/TestHarness.h>
TEST_GROUP(sound_recorder_playback_test_group)
{

};

TEST(sound_recorder_playback_test_group, PlaybackTest)
{
    marfix_stt::SoundRecorder sr;
    sr.PlaybackRecorded();
}


