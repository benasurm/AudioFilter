#include "../include/audio_buffer.h"
#include <string.h>

pa_util_classes::AudioContext::AudioContext(
    int sample_rate, 
    int channels, 
    int total_sec):
    outfile(NULL),
    frame_index(0),
    max_frame_index(sample_rate * total_sec),
    num_channels(channels),
    play(false)
{
    recorded_samples.resize(max_frame_index * channels);
    sfinfo.channels = channels;
    sfinfo.samplerate = sample_rate;
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_FLOAT;
}

void pa_util_classes::AudioContext::WriteToBuffer(
    const SAMPLE* from, 
    size_t num_frames)
{
    sf_write_float(outfile, from, num_frames * num_channels);
    frame_index = num_frames;
}

std::vector<SAMPLE>& pa_util_classes::AudioContext::GetSamples()
{
    return recorded_samples;
}

int pa_util_classes::AudioContext::getNumChannels()
{
    return num_channels;
}
void pa_util_classes::AudioContext::setNumChannels(int channels)
{
    num_channels = channels;
}

void pa_util_classes::AudioContext::openFile(std::string fname)
{
    if(outfile != nullptr)
    {
        closeFile();
    }
    outfile = sf_open("../../../recording.wav", SFM_WRITE, &sfinfo);
}

void pa_util_classes::AudioContext::closeFile()
{
    sf_close(outfile);
    outfile = nullptr;
}

bool pa_util_classes::AudioContext::getState()
{
    return play;
}

void pa_util_classes::AudioContext::setState(bool new_state)
{
    play = new_state;
}