#pragma once

#include "portaudio_utils/pa_utils.h"
#include "portaudio_utils/pa_callbacks.h"
#include "audio_buffer.h"

namespace pa_util_classes 
{
    enum State
    {
        NOT_INIT,
        NO_STREAM,
        REC,
        PLAY,
        REC_AND_PLAY
    };

    class AudioStream
    {
        public:
            AudioStream();
            virtual void initialize(pa_utils::AudioFormatInfo format_info);
            std::vector<pa_utils::AudioDeviceInfo> getSupportedDeviceInfo();
            State getCurrState();

            virtual void beginStream() = 0;
            //virtual void stopStream() = 0;
            virtual void endStream() = 0;

        protected:
            PaHostApiTypeId api_type;
            pa_utils::AudioFormatInfo format_info;
            PaStream* stream;
            std::vector<pa_utils::AudioDeviceInfo> devices = {};
            int out_device_ind;
            State curr_state = NOT_INIT;

            void findSupportedDevices();
    };
}