//
// Created by iashi on 03.03.2022.
//

#ifndef SHOEGAZE2_AUDIOSYSTEM_H
#define SHOEGAZE2_AUDIOSYSTEM_H

#include <Shoegaze2/System/Interface/Audio/IAudioSystem.h>
#include <portaudio.h>

#include "AudioDevice.h"

static float CubicAmplifier( float input )
{
    float output, temp;
    if( input < 0.0 )
    {
        temp = input + 1.0f;
        output = (temp * temp * temp) - 1.0f;
    }
    else
    {
        temp = input - 1.0f;
        output = (temp * temp * temp) + 1.0f;
    }

    return output;
}
#define FUZZ(x) CubicAmplifier(CubicAmplifier(CubicAmplifier(CubicAmplifier(x))))

static int clbck(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
                                   const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags,
                                   void *userData) {
    float *in = (float*)inputBuffer;
    float *out = (float*)outputBuffer;
    for (int i = 0; i < framesPerBuffer*2; i++)
    {
        out[i] = FUZZ(in[i]);
    }
    return paContinue;
}

namespace Shoegaze2 {
    class AudioSystem : public IAudioSystem
    {
    protected:
        AudioDevice* CreateDevice(int id, IAudioDevice::DeviceType type)
        {
            const PaDeviceInfo *info;
            info = Pa_GetDeviceInfo(id);
            auto apiInfo = Pa_GetHostApiInfo(info->hostApi);
            if (type == IAudioDevice::INPUT)
            {
                return new AudioDevice(id, info, 256, IAudioDevice::INPUT);
            }
            else if (type == IAudioDevice::OUTPUT)
            {
                return new AudioDevice(id, info, 256, IAudioDevice::OUTPUT);
            }
            return nullptr;
        }
    public:
        AudioDevice *input;
        AudioDevice *output;
        bool Initialize() override
        {
            // TODO: proper error check
            PaError err;
            err = Pa_Initialize();

            PaDeviceIndex in, out;
            int apis = Pa_GetHostApiCount();
            for (int i = 0; i < apis; i++)
            {
                auto api = Pa_GetHostApiInfo(i);
                if (api->type == paWASAPI)
                {
                    //in = api->defaultInputDevice;
                    in = api->defaultInputDevice;
                    out = api->defaultOutputDevice;

                    //break;
                }
                else if (api->type == paASIO)
                {
                    //in = api->defaultInputDevice;
                    //out = api->defaultOutputDevice;
                }
            }

            PaStreamParameters i, o;
            auto ii = Pa_GetDeviceInfo(in);
            auto oi = Pa_GetDeviceInfo(out);

            i.channelCount = ii->maxInputChannels;
            o.channelCount = oi->maxOutputChannels;
            i.device = in;
            o.device = out;
            i.suggestedLatency = ii->defaultLowInputLatency;
            o.suggestedLatency = oi->defaultLowOutputLatency;
            i.sampleFormat = o.sampleFormat = paFloat32;
            i.hostApiSpecificStreamInfo = o.hostApiSpecificStreamInfo = nullptr;
            PaStream *stream;
            //std::cout << Pa_GetErrorText(Pa_OpenStream(&stream, &i, &o, 48000, 128, 0, clbck, nullptr)) <<  std::endl;
            //std::cout << Pa_GetErrorText(Pa_StartStream(stream)) << std::endl;

            //while (true) {}
            // default input
            input = CreateDevice(in, IAudioDevice::INPUT);
            output = CreateDevice(out, IAudioDevice::OUTPUT);

            return true;
        }

        void Refresh() override
        {

        }

        ~AudioSystem() override
        {
            Pa_Terminate();
        }
    };
}

#endif //SHOEGAZE2_AUDIOSYSTEM_H
