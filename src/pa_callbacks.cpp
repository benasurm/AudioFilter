#include "../include/pa_callbacks.h"
#include "../include/pa_utils.h"
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
        const SAMPLE *read_ptr = (const SAMPLE*)inputBuffer;
        if(read_ptr == nullptr)
        {
            return paContinue;
        }

        pa_util_classes::AudioBuffer* audio_buffer 
            = (pa_util_classes::AudioBuffer*)userData;

        size_t samples_to_copy = framesPerBuffer * 2;
        audio_buffer->WriteToBuffer(read_ptr, samples_to_copy);

        return paContinue;
    }
}