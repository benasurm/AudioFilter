#include "../../include/sfml_utils/states.hpp"

std::map<sfml_utils::States::ObjectState, bool> sfml_utils::States::states;
sf::Font sfml_utils::States::font;

bool sfml_utils::States::loadFont = false;

sfml_utils::States::States()
{
    for(int i = static_cast<int>(APPEAR); i < static_cast<int>(LASTSTATE); i++)
    {
        states[static_cast<ObjectState>(i)] = false;
    }
        
}

bool sfml_utils::States::isStateEnabled(ObjectState state)
{
    return states[state];
}


void sfml_utils::States::setStateEnable(ObjectState state, bool set)
{
    states[state] = set;
}