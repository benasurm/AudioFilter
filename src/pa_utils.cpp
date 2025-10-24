#include "../include/pa_utils.h"
#include <cstdio>
#include <algorithm>

namespace pa_utils
{
    int selectInputDevice()
    {
        int devices_cnt = Pa_GetDeviceCount();
        if(devices_cnt < 0)
        {
            fprintf(stderr, "PortAudio ERROR: Pa_GetDeviceCount returned 0x%x\n", devices_cnt);
            return paNoDevice;
        }

        printf("Input audio devices:\n");
        int in_device_cnt = 0;
        std::unordered_map<int, int> input_ind_to_device_ind;
        for(int i = 0; i < devices_cnt; i++)
        {
            const PaDeviceInfo *device_info = Pa_GetDeviceInfo(i);
            if(device_info->maxInputChannels > 0)
            {
                in_device_cnt++;
                input_ind_to_device_ind[in_device_cnt] = i;
                printf("%d: %s\n", in_device_cnt, device_info->name);            
            }
        }
        printf("Enter device index to use (%d-%d): ", 1, in_device_cnt);
        int device_ind;
        scanf("%d", &device_ind);
        device_ind = std::max(1, device_ind);
        device_ind = std::min(in_device_cnt, device_ind);

        return input_ind_to_device_ind[device_ind];
    }

    const PaStreamParameters* getDefaultInputParams( 
        int device_ind,
        const PaDeviceInfo *device_info
        )
    {
        PaStreamParameters input_stream_params;
        input_stream_params.device = device_ind;
        input_stream_params.channelCount = device_info->maxInputChannels;
        input_stream_params.sampleFormat = PA_SAMPLE_TYPE;
        input_stream_params.suggestedLatency = device_info->defaultLowInputLatency;
        input_stream_params.hostApiSpecificStreamInfo = NULL;
        return (const PaStreamParameters*)&input_stream_params;
    }
}