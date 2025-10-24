#include "../include/audio_buffer.h"
#include <string.h>

pa_util_classes::AudioBuffer::AudioBuffer(
    int sample_rate, 
    int channels, 
    int total_sec)
{
    this->frame_index = 0;
    this->max_frame_index = sample_rate * total_sec;
    recorded_samples.resize(max_frame_index * channels);
}

void pa_util_classes::AudioBuffer::WriteToBuffer(
    const SAMPLE* from, 
    size_t size)
{
    memcpy(recorded_samples.data(), from, size);
    frame_index = size / 2;
}

std::vector<SAMPLE>& pa_util_classes::AudioBuffer::GetSamples()
{
    return recorded_samples;
}