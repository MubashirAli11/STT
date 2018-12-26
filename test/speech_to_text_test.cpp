#include <iostream>
#include "speech_to_text.hpp"
#include "mfcc_feature_extractor.hpp"
#include <memory>
#include <CppUTest/TestHarness.h>

enum class UserControl {
    START,
    STOP
};
TEST_GROUP(speech_to_text_test)
{
};

TEST(speech_to_text_test, dummyStructure)
{

    marfix_stt::SpeechToText speech_to_text {marfix_stt::SpeechToText::Audio::RECORDED, std::make_unique<marfix_stt::MFCCFeatureExtractor>(13, true, false), "../../caffe_model/counting_deploy.prototxt", "counting_net_iter_150.caffemodel", "UWTP"};

    UserControl user_control;

    switch (user_control) {
        case UserControl::START:
            speech_to_text.Start();
            break;

        case UserControl::STOP:
            speech_to_text.Stop();
            break;

        default:
            std::cerr << "Invalid Input" << std::endl;
    }

}
