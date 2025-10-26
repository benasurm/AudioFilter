cmake_minimum_required(VERSION 3.28)
project(AudioFilter LANGUAGES C CXX VERSION 1.0.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# --- Try finding SFML ---
find_package(SFML 3 QUIET COMPONENTS Graphics Audio Network Window System)
if (SFML_FOUND)
    message(STATUS "✅ Found SFML ${SFML_VERSION}")
else()
    message(WARNING "⚠️ SFML not found — fetching from GitHub...")
    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
    )
    FetchContent_MakeAvailable(SFML)
endif()

# --- Try finding PortAudio ---
find_package(PortAudio QUIET)
if (PortAudio_FOUND)
    message(STATUS "✅ Found PortAudio")
else()
    message(WARNING "⚠️ PortAudio not found — fetching from GitHub...")
    set(CMAKE_POLICY_VERSION_MINIMUM 3.5 CACHE STRING "" FORCE)
    set(CMAKE_POLICY_VERSION_COMPATIBLE 3.28 CACHE STRING "" FORCE)
    FetchContent_Declare(
        portaudio
        GIT_REPOSITORY https://github.com/PortAudio/portaudio.git
        GIT_TAG v19.7.0
    )
    FetchContent_MakeAvailable(portaudio)
endif()

# --- Find libsndfile ---
find_package(SndFile QUIET)
if (SndFile_FOUND)
    message(STATUS "✅ Found libsndfile")
else()
    message(WARNING "⚠️ libsndfile not found — fetching from GitHub...")
    set(CMAKE_POLICY_VERSION_MINIMUM 3.5 CACHE STRING "" FORCE)
    set(CMAKE_POLICY_VERSION_COMPATIBLE 3.28 CACHE STRING "" FORCE)
    FetchContent_Declare(
        libsndfile
        GIT_REPOSITORY https://github.com/libsndfile/libsndfile.git
        GIT_TAG        1.2.2   # or newer stable tag
        GIT_SHALLOW    ON
    )
    FetchContent_MakeAvailable(libsndfile)
endif()

# --- Collect source files ---
file(GLOB SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/sfml_utils/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/portaudio_utils/*.cpp"
)

add_executable(audio_filter ${SOURCES})
target_include_directories(audio_filter PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/sfml_utils
    ${CMAKE_SOURCE_DIR}/include/portaudio_utils
)

# --- Link libraries ---
target_link_libraries(audio_filter PRIVATE SFML::Graphics SFML::Audio SFML::Network SFML::Window SFML::System)

if (PortAudio_FOUND)
    target_link_libraries(audio_filter PRIVATE PortAudio::PortAudio)
else()
    target_link_libraries(audio_filter PRIVATE portaudio)
endif()

if (TARGET libsndfile::sndfile)
    target_link_libraries(audio_filter PRIVATE libsndfile::sndfile)
elseif (TARGET SndFile::sndfile)
    target_link_libraries(audio_filter PRIVATE SndFile::sndfile)
else()
    message(WARNING "⚠️ libsndfile target not exported correctly, adding include manually")
    target_include_directories(audio_filter PRIVATE
        ${libsndfile_SOURCE_DIR}/include
    )
    target_link_libraries(audio_filter PRIVATE sndfile)
endif()
