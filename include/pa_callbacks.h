#pragma once

#include <portaudio.h>

namespace pa_callbacks
{
    int recordCallback( 
        const void *inputBuffer, void *outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData
    );
}