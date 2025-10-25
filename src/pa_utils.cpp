#include "../include/pa_utils.h"
#include <cstdio>
#include <algorithm>

#ifdef WIN32
#define NOMINMAX
#include <windows.h>
#endif

namespace pa_utils
{
    PaHostApiTypeId getPreferredApiType()
    {
        #if defined(_WIN32)
            return paWASAPI;
        #elif defined(__linux__)
            return paALSA;
        #elif defined(__APPLE__)
            return paCoreAudio;
        #else
            return Pa_GetHostApiInfo(Pa_GetDefaultHostApi())->type;
        #endif
    }

    std::vector<AudioDeviceInfo> getSupportedInputDevices(
        PaHostApiTypeId api_type,
        double sample_rate, 
        PaSampleFormat fmt, 
        int channels) 
    {
        std::vector<AudioDeviceInfo> result = {};
        int num_devices = Pa_GetDeviceCount();
        for (int i = 0; i < num_devices; ++i) 
        {
            const PaDeviceInfo* dev_info = Pa_GetDeviceInfo(i);
            if (!dev_info || dev_info->maxInputChannels <= 0) continue;

            const PaHostApiInfo* api_info = Pa_GetHostApiInfo(dev_info->hostApi);
            if(api_info->type != api_type) continue;

            PaStreamParameters test{};
            test.device = i;
            test.channelCount = std::min(channels, (dev_info->maxInputChannels));
            test.sampleFormat = fmt;
            test.suggestedLatency = dev_info->defaultLowInputLatency;
            test.hostApiSpecificStreamInfo = nullptr;

            PaError err = Pa_IsFormatSupported(&test, nullptr, sample_rate);
            if (err == paFormatIsSupported) 
            {
                const PaHostApiInfo* api = Pa_GetHostApiInfo(dev_info->hostApi);
                result.push_back
                ({ 
                    i, 
                    dev_info->name, 
                    api->name, 
                    dev_info->maxInputChannels, 
                    dev_info->maxOutputChannels, 
                    dev_info->defaultSampleRate 
                });
            }
        }
        return result;
    }

    PaStreamParameters getDefaultInputParams( 
        int device_ind,
        const PaDeviceInfo *device_info,
        PaSampleFormat sample_format
    )
    {
        PaStreamParameters input_stream_params;
        input_stream_params.device = device_ind;
        input_stream_params.channelCount = std::min(2, device_info->maxInputChannels);
        input_stream_params.sampleFormat = sample_format;
        input_stream_params.suggestedLatency = device_info->defaultLowInputLatency;
        input_stream_params.hostApiSpecificStreamInfo = NULL;
        return input_stream_params;
    }

    int selectInputDevice(std::vector<pa_utils::AudioDeviceInfo> &supported)
    {
        printf("Available input devices:\n");
        for (size_t i = 0; i < supported.size(); i++)
        {
            printf("%d: %s\n(API: %s, ch=%d)\n",
                i+1,
                supported[i].name.c_str(),
                supported[i].apiName.c_str(),
                supported[i].maxInputChannels
            );
        }

        printf("Select device index to open (%d-%d): ", 
            1, supported.size());
        int choice;
        scanf("%d", &choice);
        choice = std::max(0, choice);
        choice = std::min(choice, int(supported.size() - 1));
        return choice;
    }

}