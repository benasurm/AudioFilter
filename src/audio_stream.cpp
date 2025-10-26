#include "../include/audio_stream.h"

pa_util_classes::AudioStream::AudioStream()
{

}

void pa_util_classes::AudioStream::initialize(pa_utils::AudioFormatInfo format_info)
{
    if(curr_state > NO_STREAM)
    {
        Pa_CloseStream(stream);
        devices.clear();
    }

    this->format_info = format_info;

    out_device_ind = -1;
    api_type = pa_utils::getPreferredApiType();
    curr_state = NO_STREAM;
    findSupportedDevices();
}

std::vector<pa_utils::AudioDeviceInfo> 
    pa_util_classes::AudioStream::getSupportedDeviceInfo()
{
    return devices;
}

pa_util_classes::State 
    pa_util_classes::AudioStream::getCurrState()
{
    return curr_state;
}

void pa_util_classes::AudioStream::findSupportedDevices()
{
    int device_cnt = Pa_GetDeviceCount();
    if(device_cnt < 0)
    {
        fprintf(stderr, "** No audio devices found!");
        return;
    }
    for (int i = 0; i < device_cnt; i++) 
    {
        const PaDeviceInfo* dev_info = Pa_GetDeviceInfo(i);
        if (!dev_info 
            || (dev_info->maxInputChannels < format_info.in_channels
            && dev_info->maxOutputChannels < format_info.out_channels)) continue;

        const PaHostApiInfo* api_info = Pa_GetHostApiInfo(dev_info->hostApi);
        if(api_info->type != api_type) continue;

        PaStreamParameters test{};
        test.device = i;
        test.channelCount = std::max(format_info.in_channels, format_info.out_channels);
        test.sampleFormat = format_info.fmt;
        test.suggestedLatency = dev_info->defaultLowInputLatency;
        test.hostApiSpecificStreamInfo = nullptr;

        PaError err = Pa_IsFormatSupported(&test, nullptr, format_info.sample_rate);
        if (err == paFormatIsSupported) 
        {
            const PaHostApiInfo* api = Pa_GetHostApiInfo(dev_info->hostApi);
            devices.push_back
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
}