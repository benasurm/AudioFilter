#include "../include/record_stream.hpp"

pa_util_classes::RecordStream::RecordStream() : audio_context(nullptr)
{
    
}

void pa_util_classes::RecordStream::initialize(pa_utils::AudioFormatInfo format_info)
{    
    pa_util_classes::AudioStream::initialize(format_info);
    audio_context = new AudioContext(format_info.sample_rate, format_info.in_channels, 10);
}

void pa_util_classes::RecordStream
    ::beginStream()
{
    if(curr_state > NO_STREAM)
    {
        printf("Abruptly ending stream\n");
        endStream();
    }

    input_stream_params = getDefaultInputParams();

    printf("device: %d\n", input_stream_params.device);

    if(audio_context == nullptr)
    {
        throw std::exception("audio_context not initialized");
    }
    audio_context->openFile("../../recording.raw");
    audio_context->setState(true);

    printf("rate: %f\n", Pa_GetDeviceInfo(in_device_ind)->defaultSampleRate);

    printf("** Opened stream\n");
    PaError err = Pa_OpenStream(
        &stream,
        (const PaStreamParameters*)(&input_stream_params),
        NULL,
        Pa_GetDeviceInfo(in_device_ind)->defaultSampleRate,
        paFramesPerBufferUnspecified,
        paClipOff,
        pa_callbacks::recordCallback,
        audio_context
    );
    if(err != paNoError)
    {
        printf("** ERROR OPENING STREAM!\n");
        fprintf(stderr, "PortAudio Error code: 0x%x\n", err);
        fprintf(stderr, "PortAudio Error text: %s\n", Pa_GetErrorText(err));
        PaError err = Pa_CloseStream( stream );
        return;
    }

    printf("** Starting stream\n");
    err = Pa_StartStream(stream);
    curr_state = REC;
}

void pa_util_classes::RecordStream
    ::endStream()
{
    audio_context->setState(false);

    while (Pa_IsStreamActive(stream)) 
    {
        Pa_Sleep(10);
    }

    if(curr_state > NO_STREAM)
    {
        printf("** Closing stream\n");
        PaError err = Pa_CloseStream( stream );
        audio_context->closeFile();
    }
    curr_state = NO_STREAM;
}

std::vector<pa_utils::AudioDeviceInfo> 
    pa_util_classes::RecordStream::getInputDevices()
{
    std::vector<pa_utils::AudioDeviceInfo> result;
    for(int i = 0; i < devices.size(); i++)
    {
        if(devices[i].maxInputChannels >= format_info.in_channels)
        {
            result.push_back(devices[i]);
        }
    }
    return result;
}

void pa_util_classes::RecordStream
    ::selectInputDevice(int device_ind)
{
    in_device_ind = getInputDevices()[device_ind].index;
    printf("Selected device: %s\n", Pa_GetDeviceInfo(in_device_ind)->name);
}

PaStreamParameters 
    pa_util_classes::RecordStream::getDefaultInputParams()
{
    const PaDeviceInfo* info = Pa_GetDeviceInfo(in_device_ind);
    PaStreamParameters input_stream_params;
    input_stream_params.device = in_device_ind;
    input_stream_params.channelCount = format_info.in_channels;
    input_stream_params.sampleFormat = format_info.fmt;
    input_stream_params.suggestedLatency = info->defaultLowInputLatency;
    input_stream_params.hostApiSpecificStreamInfo = NULL;
    return input_stream_params;
}

pa_util_classes::RecordStream::~RecordStream()
{
    delete audio_context;
}
