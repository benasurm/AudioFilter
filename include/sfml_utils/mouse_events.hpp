//  CREDITS TO:
//
//  MouseEvents.hpp
//  dropdown_menu
//
//  Created by Aaron Lin on 4/27/21.
//

#pragma once

#include <SFML/Graphics.hpp>

namespace sfml_utils
{
    template <class T>
    class MouseEvents 
    {
        public:
            // returns true if the mouse clicks on the object
            static bool mouseClicked(T& object, sf::RenderWindow& window);

            // returns true if the mouse clicks anywhere in the window
            static bool mouseClicked( sf::RenderWindow& window, sf::Event event);

            // returns true if the mouse has been double clicked
            static bool mouseDoubleClicked();

            //returns true if the mouse has been triple clicked
            static bool mouseTripleClicked();

            // returns if the object has been clicked and the mouse has dragged over the object
            static bool draggedOver(T& object, sf::RenderWindow& window, sf::Event event);
            
            // returns tru if the mouse is hovered over the object
            static bool hovered(T& object, sf::RenderWindow& window);

        private:
            // this is what I used to determine if a double click or triple click occurred
            // you don't have to use this if you don't want to
            static sf::Clock clock;
            static int clicks;
            static void countClicks(sf::Event event);
    };


    // -----------------implementation------


    template <class T>
    int MouseEvents<T>::clicks;


    template <class T>
    bool MouseEvents<T>::mouseClicked(T& object, sf::RenderWindow& window)
    {
        if( hovered(object, window) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    template <class T>
    bool MouseEvents<T>::mouseClicked( sf::RenderWindow& window, sf::Event event)
    {
        if( (event.is<sf::Event::MouseButtonPressed> ) && 
            ( event.getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left) )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    template <class T>
    bool MouseEvents<T>::mouseDoubleClicked()
    {
        if(clicks == 2)
        {
            return true;
        }
    }

    template <class T>
    bool MouseEvents<T>::mouseTripleClicked()
    {
        return (clicks == 3);
    }

    template <class T>
    bool MouseEvents<T>::draggedOver(T& object, sf::RenderWindow& window, sf::Event event)
    {
        if(mouseClicked(object, window))
        {
            while( !event.is<sf::Event::MouseButtonReleased> )
            {
                if(event.is<sf::Event::MouseMoved> )
                {
                    return true;
                }
            }
        }
        return false;
    }

    template <class T>
    bool MouseEvents<T>::hovered(T& object, sf::RenderWindow& window)
    {
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        if( object.getLocalBounds().contains(sf::Vector2f(pos.x, pos.y)) )
        {
            return true;
        }
        else
        {
            return false;
        }
    }


    template <class T>
    void MouseEvents<T>::countClicks(sf::Event event)
    {
        while(clock.getElapsedTime().asSeconds() <= 1)
        {
            if( (event.is<sf::Event::MouseButtonPressed> ) && 
                ( event.getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left) )
            {
                clock.restart();
                ++clicks;
            }
        }
                
    }
}