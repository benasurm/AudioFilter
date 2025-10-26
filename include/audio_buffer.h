#pragma once

#include "portaudio_utils/pa_utils.h"
#include <vector>
#include <sndfile.h>

namespace pa_util_classes
{
    class AudioContext
    {
        private:
            SNDFILE* outfile;
            SF_INFO sfinfo{};
            int num_channels;
            int frame_index;
            int max_frame_index;
            std::vector<SAMPLE> recorded_samples;
            bool play;
        public:
            AudioContext(int sample_rate, int channels, 
                int total_sec);
            void WriteToBuffer(const SAMPLE* from, size_t from_size);
            std::vector<SAMPLE>& GetSamples();
            int getNumChannels();
            void setNumChannels(int channels);
            void openFile(std::string fname);
            void closeFile();
            bool getState();
            void setState(bool new_state);
    };
}