#pragma once

#include <portaudio.h>
#include <vector>
#include <string>

#include "pa_defines.h"

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

    struct AudioFormatInfo
    {
        double sample_rate;
        PaSampleFormat fmt;
        int in_channels, out_channels;
    };
    
    PaHostApiTypeId getPreferredApiType();
}