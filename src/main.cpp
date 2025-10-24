#include <portaudio.h>
#include <cstdlib>
#include <cstdio>
#include "../include/pa_utils.h"
#include "../include/pa_callbacks.h"
#include "../include/audio_buffer.h"

#ifdef WIN32
#include <windows.h>
 
#if PA_USE_ASIO
#include "pa_asio.h"
#endif
#endif

#define SAMPLE_RATE 44100

int main()
{
    int in_device_ind;
    const PaDeviceInfo *device_info;

    const PaStreamParameters* input_stream_params;
    PaStream* stream;

    pa_util_classes::AudioBuffer audio_buffer(SAMPLE_RATE, 
        2, 10);
    
    PaError err = Pa_Initialize();
    if(err != paNoError)
    {
        fprintf(stderr, "PortAudio ERROR: Pa_Initialize returned 0x%x\n", err);
        goto error;
    }

    // A hack, should not be present in the "production" versions
    #ifdef WIN32
        system("CLS");
    #else
        system("clear");
    #endif

    // Selection of input audio device
    in_device_ind = pa_utils::selectInputDevice();
    if(in_device_ind == paNoDevice)
    {
        printf("No input audio devices found, exiting program");
        Pa_Terminate();
        return 0;
    }
    device_info = Pa_GetDeviceInfo(in_device_ind);
    printf("Selected device: %s\n", device_info->name);

    // Initializing input stream parameters
    input_stream_params = pa_utils::getDefaultInputParams(
        in_device_ind,
        device_info);
    
    /*err = Pa_OpenStream(
        &stream,
        input_stream_params,
        NULL,
        SAMPLE_RATE,
        paFramesPerBufferUnspecified,
        paClipOff,
        pa_callbacks::recordCallback,
        &audio_buffer
    );
    if(err != paNoError) goto error;*/


    Pa_Terminate();
    return 0;

    error:
        Pa_Terminate();
        fprintf(stderr, "PortAudio Error code: 0x%x\n", err);
        fprintf(stderr, "PortAudio Error text: %s\n", Pa_GetErrorText(err));
        return err;
}
