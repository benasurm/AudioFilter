#include "../include/application.h"

Application::Application()
{
    m_window.setVerticalSyncEnabled(true);
}

bool Application::init()
{
    rec_stream = new pa_util_classes::RecordStream();
    err = Pa_Initialize();
    if(err != paNoError)
    {
        fprintf(stderr, "PortAudio ERROR: Pa_Initialize returned 0x%x\n", err);
        return false;
    }

    rec_stream->initialize({48000.0, paFloat32, 2, 0});
    std::vector<std::string> device_names = getDeviceNames();

    mic_selection = new sfml_utils::ItemList(device_names, 300.f, 90.f);
    mic_selection->setPosition(0, 0);

    rec_btn = new sfml_utils::Item("Record", sf::Vector2f({300.f, 90.f}));
    rec_btn->setFillColor(sf::Color(6, 150, 0));
    rec_btn->setPosition(360, 360);
    rec_btn->setFontSize(26);
    rec_btn_enabled = true;

    stop_btn = new sfml_utils::Item("Stop", sf::Vector2f({300.f, 90.f}));
    stop_btn->setFillColor(sf::Color(120, 18, 0));
    stop_btn->setPosition(360, 460);
    stop_btn->setFontSize(26);
    stop_btn_enabled = false;

    curr_device_select = 0;
    rec_stream->selectInputDevice(curr_device_select);

    return true;
}

void Application::run()
{    
    while (m_window.isOpen())
    {
        while (const auto event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                m_window.close();
                return;
            }

            // MICROPHONE EVENTS
            mic_selection->addEventHandler(m_window, *event);
            int item_list_select = mic_selection->getSelectedIndex();
            if(item_list_select != curr_device_select)
            {
                if(rec_stream->getCurrState() > pa_util_classes::State::NO_STREAM)
                {   
                    rec_stream->endStream();
                }
                curr_device_select = item_list_select;
                rec_stream->selectInputDevice(curr_device_select);
            }            
            
            // RECORD BUTTON EVENTS
            if(rec_btn_enabled)
            {
                if(sfml_utils::MouseEvents<sfml_utils::Item>
                    ::hovered(*rec_btn, m_window))
                {
                    rec_btn->setFillColor(sf::Color(5, 115, 1));
                }
                else
                {
                    rec_btn->setFillColor(sf::Color(6, 150, 0));
                }

                if(sfml_utils::MouseEvents<sfml_utils::Item>
                    ::mouseClicked(*rec_btn, m_window))
                {
                    stop_btn_enabled = true;
                    rec_btn_enabled = false;

                    try
                    {
                        rec_stream->beginStream();
                    }
                    catch(const std::exception& e)
                    {
                        fprintf(stderr, "%s\n", e.what());
                    }
                }
            }
            else
            {
                rec_btn->setFillColor(sf::Color(97, 97, 97));
            }

            // STOP BUTTON EVENTS
            if(stop_btn_enabled)
            {
                if(sfml_utils::MouseEvents<sfml_utils::Item>
                    ::hovered(*stop_btn, m_window))
                {
                    stop_btn->setFillColor(sf::Color(196, 29, 0));
                }
                else
                {
                    stop_btn->setFillColor(sf::Color(120, 18, 0));
                }

                if(sfml_utils::MouseEvents<sfml_utils::Item>
                    ::mouseClicked(*stop_btn, m_window))
                {
                    stop_btn_enabled = false;
                    rec_btn_enabled = true;

                    if(rec_stream->getCurrState() > pa_util_classes::State::NO_STREAM)
                    {
                        rec_stream->endStream();
                    }
                }
            }
            else
            {
                stop_btn->setFillColor(sf::Color(97, 97, 97));
            }
        }

        m_window.clear(sf::Color::Black);
        mic_selection->draw(m_window, sf::RenderStates::Default);
        rec_btn->draw(m_window, sf::RenderStates::Default);
        stop_btn->draw(m_window, sf::RenderStates::Default);
        m_window.display();

        #if defined(_WIN32)
            Sleep(SLEEP_MS);
        #else
            sleep(SLEEP_MS / 1000.0)
        #endif
    }
}

Application::~Application()
{
    delete mic_selection;
    delete rec_stream;
    if(err != paNoError)
    {
        fprintf(stderr, "PortAudio Error code: 0x%x\n", err);
        fprintf(stderr, "PortAudio Error text: %s\n", Pa_GetErrorText(err));
    }
    Pa_Terminate();
}

std::vector<std::string> Application::getDeviceNames()
{
    std::vector<pa_utils::AudioDeviceInfo> devices = rec_stream->getInputDevices();
    std::vector<std::string> result;
    for (size_t i = 0; i < devices.size(); i++)
    {        
        result.push_back(devices[i].name);
    }
    return result;
}