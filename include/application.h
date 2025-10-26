#include <SFML/Graphics.hpp>
#include <thread>
#include <portaudio.h>
#include <format>
#include <string>
#include "../include/sfml_utils/item_list.hpp"
#include "record_stream.hpp"

#if defined(_WIN32)
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#define SLEEP_MS 50

class Application
{
    public:
        Application();
        ~Application();
        bool init();
        void run();

    private:
        sf::RenderWindow m_window{ sf::VideoMode({1280u, 720u}), 
            "Audio Filter", sf::Style::Titlebar | sf::Style::Close };
        sfml_utils::ItemList* mic_selection;
        sfml_utils::Item* rec_btn;
        sfml_utils::Item* stop_btn;
        PaError err;

        pa_util_classes::RecordStream* rec_stream;

        // TEMPORARY VARIABLES
        int curr_device_select;
        bool rec_btn_enabled;
        bool stop_btn_enabled;

        std::vector<std::string> getDeviceNames();

};