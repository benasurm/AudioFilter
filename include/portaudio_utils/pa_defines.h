#pragma once

#ifdef WIN32
#define NOMINMAX
#include <windows.h>
 
#if PA_USE_ASIO
#include "pa_asio.h"
#endif
#endif

#define SAMPLE_RATE 44100

#define NUM_IN_CHANNELS 2
#define PA_SAMPLE_TYPE  paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE  (0.0f)
#define PRINTF_S_FORMAT "%.8f"