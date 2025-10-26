//  CREDITS TO:
//
//  ItemList.hpp
//  dropdown_menu
//
//  Created by Aaron Lin on 4/28/21.
//  Edited my me
//

#pragma once

#include "item.hpp"
#include <stdio.h>

namespace sfml_utils
{    
    class ItemList: public sf::Drawable, public sf::Transformable
    {
        public:
            ItemList();
            ItemList(std::vector<std::string> vec, float x, float y);  // given a vector of std::string
            void setPosition(float x, float y);
            void setSize(float x, float y);     // x = width of a single Item inside list,
                                                // y = height of a single item
            void add(std::string item, float x, float y);         // add an item to the list
            void remove(std::string item);      // delete an item with msg == item
            void addEventHandler(sf::RenderWindow& window, const sf::Event& event);
            void draw(sf::RenderTarget& window, sf::RenderStates states) const;
            sf::FloatRect getLocalBounds();
            int getSelectedIndex();
            
        private:
            std::vector<Item> itemlist;
            sf::Font font;
            std::string word;
            int selected_index = 0;
    };
}
