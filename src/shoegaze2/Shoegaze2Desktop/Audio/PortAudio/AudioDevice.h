//
// Created by iashi on 03.03.2022.
//

#ifndef SHOEGAZE2_AUDIODEVICE_H
#define SHOEGAZE2_AUDIODEVICE_H

#include <Shoegaze2/System/Interface/Audio/IAudioDevice.h>
#include <portaudio.h>

namespace Shoegaze2
{
    int AudioDeviceCallback(const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData);

    class AudioDevice : public IAudioDevice
    {
    private:
        PaStream* stream;
        PaStreamParameters params;
    public:
        AudioDevice(int id, const PaDeviceInfo* info, unsigned int framesPerBuffer, DeviceType type) : IAudioDevice(info->name, type, type == INPUT ? info->maxInputChannels : info->maxOutputChannels, framesPerBuffer)
        {
            params.device = id;
            params.channelCount = (int)channels;
            params.suggestedLatency = type == INPUT ? info->defaultLowInputLatency : info->defaultLowOutputLatency;
            params.sampleFormat = paFloat32;
            params.hostApiSpecificStreamInfo = nullptr;
        }

        friend int AudioDeviceCallback(const void *inputBuffer, void *outputBuffer,
                                       unsigned long framesPerBuffer,
                                       const PaStreamCallbackTimeInfo* timeInfo,
                                       PaStreamCallbackFlags statusFlags,
                                       void *userData);

        void Start() override
        {
            PaError err = Pa_OpenStream(&stream, type == INPUT ? &params : nullptr, type == OUTPUT ? &params : nullptr, 48000, framesPerBuffer, 0, AudioDeviceCallback, this);
            if (err != paNoError) {
                std::cout << "Audio device open stream error" << std::endl;
                std::cout << Pa_GetErrorText(err) << std::endl;
            }
            else {
                err = Pa_StartStream(stream);
                if (err != paNoError) {
                    std::cout << "Audio device start stream error" << std::endl;
                    std::cout << Pa_GetErrorText(err) << std::endl;
                }
            }
            //IAudioDevice::Start();
        }

        void Stop() override
        {
            Pa_StopStream(stream);
            Pa_CloseStream(&stream);
            IAudioDevice::Stop();
        }
    };
}


#endif //SHOEGAZE2_AUDIODEVICE_H
