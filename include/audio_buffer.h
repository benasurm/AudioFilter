#pragma once

#include "../include/pa_utils.h"
#include <vector>

namespace pa_util_classes
{
    class AudioBuffer
    {
        private:
            int frame_index;
            int max_frame_index;
            std::vector<SAMPLE> recorded_samples;
        public:
            AudioBuffer(int sample_rate, int channels, 
                int total_sec);
            void WriteToBuffer(const SAMPLE* from, size_t from_size);
            std::vector<SAMPLE>& GetSamples();
    };
}