#include "sound_recorder.hpp"

using namespace marfix_stt;

int SoundRecorder::streamRecordCallback(
    const void* inputBuffer, void*, unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlag)
{
    auto in = static_cast<SampleType**>(const_cast<void*>(inputBuffer));

    for (unsigned long i = 0; i < framesPerBuffer; i++) {
        audioFile.write((char*) &in[0][i], sizeof(SampleType));
    }

    return paContinue;
}

int SoundRecorder::streamPlaybackCallback(
    const void*, void* outputBuffer, unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlag)
{

    auto out = static_cast<SampleType**>(outputBuffer);

    for (unsigned long i = 0; i < framesPerBuffer; i++) {
        if (d.frameIndex < d.buffer.size()) {
            out[0][i] = d.buffer.at(d.frameIndex++);
        }
    }

    if (d.frameIndex >= d.buffer.size() - 1) {
        return paComplete;
    }

    else {
        return paContinue;
    }
}

SoundRecorder::SoundRecorder()
    : system(portaudio::System::instance()),
      audioFile("data.bin", std::ios::app | std::ios::out | std::ios::binary) {}

void SoundRecorder::StartRecording()
{
    portaudio::Device& inDevice = system.defaultInputDevice();

    portaudio::DirectionSpecificStreamParameters inParam(
        inDevice, ToUnderlyingType(AudioFormat::SelectedChannel), portaudio::INT16,
        false, inDevice.defaultLowInputLatency(), nullptr);
    portaudio::StreamParameters streamParam(
        inParam, portaudio::DirectionSpecificStreamParameters::null(),
        static_cast<double>(AudioFormat::SelectedSampleRate), 64,
        paClipOff);

    stream.open(streamParam, *this, &SoundRecorder::streamRecordCallback);
    stream.start();

    while (stream.isActive()) {
        system.sleep(100);
    }

    audioFile.close();
}

void SoundRecorder::StopRecording()
{
    stream.stop();
    stream.close();
}

void SoundRecorder::PlaybackRecorded()
{
    portaudio::Device& outDevice = system.defaultOutputDevice();

    portaudio::DirectionSpecificStreamParameters outParam(
        outDevice, ToUnderlyingType(AudioFormat::SelectedChannel), portaudio::INT16,
        false, outDevice.defaultLowOutputLatency(), nullptr);
    portaudio::StreamParameters streamParam(
        portaudio::DirectionSpecificStreamParameters::null(), outParam,
        static_cast<double>(AudioFormat::SelectedSampleRate), 64,
        paClipOff);

    audioFile.close();
    std::ifstream playAudioFile("./data.bin", std::ios::binary);

    auto tempBuffer =
        std::vector<char> ((std::istreambuf_iterator<char> (playAudioFile)),
                           std::istreambuf_iterator<char>());

    const SampleType* data =
        reinterpret_cast<const SampleType*>(tempBuffer.data());

    d.buffer.assign(data, data + tempBuffer.size() / sizeof(SampleType));
    d.frameIndex = 0;
    // std::cout << d.buffer.size();
    /* for ( int i = 0; i < tempBuffer.size(); i++){
     *     std::cout << tempBuffer[i] << std::endl;
    }
    */

    stream.open(streamParam, *this, &SoundRecorder::streamPlaybackCallback);
    stream.start();

    //while (stream.isActive())
    // system.sleep(100);

    playAudioFile.close();
}

std::vector<portaudio::Device*> SoundRecorder::GetInputDevices()
{
    std::vector<portaudio::Device*> devices;

    for (portaudio::System::DeviceIterator device = system.devicesBegin();
            device != system.devicesEnd(); device++) {
        if (device->isFullDuplexDevice() || device->isInputOnlyDevice()) {
            devices.emplace_back(& (*device));
        }
    }

    return devices;
}
