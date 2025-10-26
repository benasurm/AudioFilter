#include "../include/portaudio_utils/pa_utils.h"
#include <cstdio>
#include <algorithm>

#ifdef WIN32
#define NOMINMAX
#include <windows.h>
#endif

namespace pa_utils
{
    PaHostApiTypeId getPreferredApiType()
    {
        #if defined(_WIN32)
            return paWASAPI;
        #elif defined(__linux__)
            return paALSA;
        #elif defined(__APPLE__)
            return paCoreAudio;
        #else
            return Pa_GetHostApiInfo(Pa_GetDefaultHostApi())->type;
        #endif
    }
}