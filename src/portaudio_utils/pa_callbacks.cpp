#include "../include/portaudio_utils/pa_callbacks.h"
#include "../include/portaudio_utils/pa_utils.h"
#include "../include/audio_buffer.h"

namespace pa_callbacks
{
    int recordCallback( 
        const void *inputBuffer, void *outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData
    )
    {
        if(inputBuffer == nullptr)
        {
            return paContinue;
        }

        pa_util_classes::AudioContext* context 
            = reinterpret_cast<pa_util_classes::AudioContext*>(userData);

        if(!context->getState())
        {
            return paComplete;
        }

        context->WriteToBuffer((const SAMPLE*)inputBuffer, framesPerBuffer);

        return paContinue;
    }
}