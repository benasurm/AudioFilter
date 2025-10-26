//  CREDITS TO:
//
//  MouseEvents.hpp
//  dropdown_menu
//
//  Created by Aaron Lin on 4/27/21.
//

#pragma once

#include <string>
#include "mouse_events.hpp"
#include "states.hpp"

namespace sfml_utils
{
    class Item: public sf::Drawable, public sf::Transformable
    {
        public:
            Item(std::string msg, sf::Vector2f vec);
            Item(std::string msg);
            Item();
            void setText(std::string msg);
            sf::FloatRect getLocalBounds() const;
            void setSize(float x, float y);
            void setPosition(float x, float y);
            void setFontSize(unsigned int size);
            void draw(sf::RenderTarget& window, sf::RenderStates states) const;
            void setFillColor(sf::Color color);
            std::string getText() const;
            bool operator==(const Item& other);
        
        private:
            sf::Text* text;
            sf::RectangleShape box;
    };
}