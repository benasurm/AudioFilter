#include <portaudio.h>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include "../include/pa_utils.h"
#include "../include/pa_callbacks.h"
#include "../include/audio_buffer.h"

#include <iostream>

#ifdef WIN32
#define NOMINMAX
#include <windows.h>
 
#if PA_USE_ASIO
#include "pa_asio.h"
#endif
#endif

#define SAMPLE_RATE 44100

int main()
{
    int supported_index, in_device_ind;
    const PaDeviceInfo *device_info;

    PaStreamParameters input_stream_params;
    PaStream* stream;

    pa_util_classes::AudioBuffer audio_buffer(SAMPLE_RATE, 
        2, 10);

    std::vector<pa_utils::AudioDeviceInfo> supported = {};
    
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

    PaHostApiTypeId pref_api = pa_utils::getPreferredApiType();
    supported = pa_utils::getSupportedInputDevices(
        pref_api,
        48000.0,
        paFloat32,
        2
    );

    if (supported.empty()) 
    {
        fprintf(stderr, "PortAudio Warning: no supported input devices!");
        goto error;
    }

    supported_index = pa_utils::selectInputDevice(supported);
    in_device_ind = supported[supported_index].index;
    device_info = Pa_GetDeviceInfo(in_device_ind);
    printf("Selected device: %s\n", device_info->name);

    input_stream_params = pa_utils::getDefaultInputParams(
        in_device_ind,
        device_info,
        paFloat32
    );

    err = Pa_OpenStream(
        &stream,
        (const PaStreamParameters*)&input_stream_params,
        NULL,
        device_info->defaultSampleRate,
        paFramesPerBufferUnspecified,
        paClipOff,
        pa_callbacks::recordCallback,
        &audio_buffer
    );
    if(err != paNoError) goto error;

    Pa_Terminate();
    return 0;

    error:
        Pa_Terminate();
        fprintf(stderr, "PortAudio Error code: 0x%x\n", err);
        fprintf(stderr, "PortAudio Error text: %s\n", Pa_GetErrorText(err));
        return err;
}