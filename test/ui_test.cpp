#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/threads/pool.hpp>
#include "sound_recorder.hpp"
#include "speech_to_text.hpp"
#include "mfcc_feature_extractor.hpp"
#include <CppUTest/TestHarness.h>
#include <nana/gui/filebox.hpp>

TEST_GROUP(ui_test_group)
{

};

TEST(ui_test_group, RandomTestCases)
{
    using namespace nana;

    form fm(API::make_center(150, 100));
    fm.caption("Recorder");
    place p(fm);
    marfix_stt::SoundRecorder soundRecorder;
    button playButton(fm);
    button pauseButton(fm);
    playButton.caption("Play");
    pauseButton.caption("Pause");
    p.div("<playAndPause>");
    p.field("playAndPause") << playButton << pauseButton;

    threads::pool pool(1);
    bool play = false;
    playButton.events().click(pool_push(pool, [&]() {

        if (!play) {
            play = true;
            soundRecorder.StartRecording();
        }
    }));

    pauseButton.events().click([&]() {

        if (play) {
            play = false;
            soundRecorder.StopRecording();
        }
    });

    p.collocate();
    fm.show();
    exec();
}
TEST(ui_test_group, CompleteUserInterfaceTest)
{

    using namespace nana;

    form fm(API::make_center(400, 200), appearance(true, true, false, false, true, false, false));
    fm.caption("Word Recognizer");

    filebox wave_file_box(fm, true);

    wave_file_box.add_filter("Wav files", "*.wav");
    wave_file_box.title("Load wave file");

    place p(fm);

    button reset_button(fm);
    button speak_button(fm);
    button recognize_button(fm);
    button load_wave_file_button(fm);

    label spoken_word_label(fm, "Recognized word: ");
    spoken_word_label.text_align(align::center, align_v::center);
    label spoken_word(fm, "ایک");
    spoken_word.text_align(align::center, align_v::center);
    spoken_word.format(true);
    reset_button.caption("Reset");
    speak_button.caption("Speak");
    recognize_button.caption("Recognize");
    load_wave_file_button.caption("Load Wave File");

    p.div("<grid=[3, 2] main_grid gap=5 margin=[25%, 5%, 25%, 5%]>");
    p.field("main_grid") << spoken_word_label << spoken_word << recognize_button;
    p.field("main_grid") << reset_button << "" << load_wave_file_button;

    marfix_stt::SpeechToText speech_to_text {marfix_stt::SpeechToText::Audio::RECORDED, std::make_unique<marfix_stt::MFCCFeatureExtractor>(13, true, false), "../../caffe_model/counting_deploy.prototxt", "counting_net_iter_150.caffemodel", "UWTP"};

    threads::pool pool(1);

    std::string file;

    load_wave_file_button.events().click(pool_push(pool, [&]() {
        if (wave_file_box()) {
            file = wave_file_box.file();
        }
    }
                                                  ));

    reset_button.events().click(pool_push(pool, [&]() {
        file = "";
        spoken_word.caption("");
    }));

    std::string word = "";

    recognize_button.events().click(pool_push(pool, [&]() {
        if (!file.empty()) {
            word = speech_to_text.Recognize(file);
            spoken_word.caption(word);

        }

        else {
            msgbox mb(fm, "File not selected");
            mb << L"Please select the wave file first.";
            mb.show();
        }
    }));

    p.collocate();
    fm.show();
    exec();
}
