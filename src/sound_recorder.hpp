#ifndef SOUND_RECORDER__HPP
#define SOUND_RECORDER__HPP

#include "stt_common.hpp"

/**
 * @brief This is speech to text global namespace
 * @author Abdul Rehman, Faraz Ahmed, Monis Ahmed Khan, Mubashir Ali
 */
namespace marfix_stt {

    /**
     * @brief Gets data from mic and output it on a file "data.bin" we are writing to this file temporarily, after testing we will give direct mic input to feature extraction.
     *
     */
    class SoundRecorder {
        portaudio::AutoSystem autoSys;
        portaudio::System& system;

        std::ofstream audioFile;
        struct data {
            unsigned long frameIndex;
            std::vector<SampleType> buffer;
        } d;

        portaudio::MemFunCallbackStream<SoundRecorder> stream;
        int streamRecordCallback(const void* inputBuffer, void* outputBuffer,
                                 unsigned long framesPerBuffer,
                                 const PaStreamCallbackTimeInfo* timeInfo,
                                 PaStreamCallbackFlags statusFlag);

        int streamPlaybackCallback(const void*, void* outputBuffer,
                                   unsigned long framesPerBuffer,
                                   const PaStreamCallbackTimeInfo* timeInfo,
                                   PaStreamCallbackFlags statusFlag);

    public:
        SoundRecorder();
        void StartRecording();
        void StopRecording();
        void PlaybackRecorded();
        std::vector<portaudio::Device*> GetInputDevices();
    };
}
#endif // SOUND_RECORDER__HPP
