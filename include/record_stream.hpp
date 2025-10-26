#pragma once

#include "audio_stream.h"
#include "audio_buffer.h"

namespace pa_util_classes
{
    class RecordStream 
        : public pa_util_classes::AudioStream
    {
        public:
            RecordStream();
            void beginStream() override;
            void endStream() override;
            void initialize(pa_utils::AudioFormatInfo format_info) override;

            std::vector<pa_utils::AudioDeviceInfo> getInputDevices();
            void selectInputDevice(int device_ind);

            ~RecordStream();

        private:
            AudioContext* audio_context;
            PaStreamParameters input_stream_params;
            int in_device_ind = 0;

            PaStreamParameters getDefaultInputParams();
    };
}