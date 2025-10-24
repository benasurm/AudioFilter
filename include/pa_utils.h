#pragma once

#include <portaudio.h>
#include <unordered_map>

#define NUM_IN_CHANNELS 2
#define PA_SAMPLE_TYPE  paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE  (0.0f)
#define PRINTF_S_FORMAT "%.8f"

namespace pa_utils
{
    int selectInputDevice();
    const PaStreamParameters* getDefaultInputParams(
        int device_ind,
        const PaDeviceInfo *device_info
    );
}