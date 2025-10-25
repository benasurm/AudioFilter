#pragma once

#include <portaudio.h>
#include <vector>
#include <string>

#define NUM_IN_CHANNELS 2
#define PA_SAMPLE_TYPE  paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE  (0.0f)
#define PRINTF_S_FORMAT "%.8f"

namespace pa_utils
{
    struct AudioDeviceInfo 
    {
        int index;
        std::string name;
        std::string apiName;
        int maxInputChannels;
        int maxOutputChannels;
        double defaultsample_rate;
    };
    
    PaHostApiTypeId getPreferredApiType();
    std::vector<pa_utils::AudioDeviceInfo> getSupportedInputDevices(
        PaHostApiTypeId api_type,
        double sample_rate, 
        PaSampleFormat fmt, 
        int channels
    );
    PaStreamParameters getDefaultInputParams( 
        int device_ind,
        const PaDeviceInfo *device_info,
        PaSampleFormat sample_format
    );
    int selectInputDevice(std::vector<pa_utils::AudioDeviceInfo> &supported);
}