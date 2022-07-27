//
// Created by iashi on 03.03.2022.
//

#include "AudioDevice.h"
#include <iostream>

int Shoegaze2::AudioDeviceCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
                                   const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags,
                                   void *userData) {
    auto dev = (Shoegaze2::AudioDevice *) userData;
    if (dev == nullptr)
        return paContinue;
    dev->status = IAudioDevice::RUNNING;
    if (dev->type == IAudioDevice::INPUT) {
        ///std::cout << "I" << framesPerBuffer << " S" << dev->queue->size << " R" << dev->queue->readIndex << " W" << dev->queue->writeIndex << " A" << dev->queue->available << std::endl;
        auto *buffer = (float *) inputBuffer;
        dev->queue->Write(buffer, framesPerBuffer * dev->channels);
        ///std::cout << "I_" << framesPerBuffer << " S" << dev->queue->size << " R" << dev->queue->readIndex << " W" << dev->queue->writeIndex << " A" << dev->queue->available << std::endl;
    } else if (dev->type == IAudioDevice::OUTPUT) {
        ///std::cout << "O" << framesPerBuffer << " S" << dev->queue->size << " R" << dev->queue->readIndex << " W" << dev->queue->writeIndex << " A" << dev->queue->available << std::endl;
        auto *buffer = (float *) outputBuffer;
        ///if (dev->queue->Available() == 0)
            ///std::cout << "UNDERRUN" << std::endl;
        dev->queue->Read(buffer, framesPerBuffer * dev->channels);
        ///std::cout << "O_" << framesPerBuffer << " S" << dev->queue->size << " R" << dev->queue->readIndex << " W" << dev->queue->writeIndex << " A" << dev->queue->available << std::endl;
    }
    return paContinue;
}
