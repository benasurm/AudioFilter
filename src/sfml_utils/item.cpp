#include "../../include/sfml_utils/item.hpp"

sfml_utils::Item::Item(std::string msg, sf::Vector2f vec)
{    
    box.setSize(vec);
    box.setFillColor(sf::Color::Transparent);
    
    if(!sfml_utils::States::loadFont)
    {
        sfml_utils::States::font.openFromFile("../../../resources/fonts/OpenSans.ttf");
    }

    text = new sf::Text(sfml_utils::States::font, msg, (unsigned)(vec.y/7));
    text->setFillColor(sf::Color::White);
    sf::FloatRect textBounds = text->getLocalBounds();

    text->setPosition(
        sf::Vector2f
        (
            box.getPosition().x + (box.getLocalBounds().size.x - textBounds.size.x) / 2.f,
            box.getPosition().y + (box.getLocalBounds().size.y - textBounds.size.y) / 2.f
        )
    );
}

sfml_utils::Item::Item(std::string msg)
    : Item(msg, {500,100})
{
    
}

sfml_utils::Item::Item()
    : Item("Something", {500, 100})
{
    
}

void sfml_utils::Item::setText(std::string msg)
{
    text->setString(msg);
}

sf::FloatRect sfml_utils::Item::getLocalBounds() const
{
    return box.getGlobalBounds();
}

void sfml_utils::Item::setSize(float x, float y)
{
    box.setSize({x,y});
    text->setCharacterSize(y/2);
}

void sfml_utils::Item::setPosition(float x, float y)
{
    box.setPosition({x, y});

    sf::FloatRect textBounds = text->getLocalBounds();

    text->setPosition(
        sf::Vector2f
        (
            box.getPosition().x + (box.getLocalBounds().size.x - textBounds.size.x) / 2.f,
            box.getPosition().y + (box.getLocalBounds().size.y - textBounds.size.y) / 2.f
        )
    );
}

void sfml_utils::Item::setFontSize(unsigned int size)
{
    text->setCharacterSize(size);

    sf::FloatRect textBounds = text->getLocalBounds();

    text->setPosition(
        sf::Vector2f
        (
            box.getPosition().x + (box.getLocalBounds().size.x - textBounds.size.x) / 2.f,
            box.getPosition().y + (box.getLocalBounds().size.y - textBounds.size.y) / 2.f
        )
    );
}

void sfml_utils::Item::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(box);
    window.draw(*text);    
}

void sfml_utils::Item::setFillColor(sf::Color color)
{
    box.setFillColor(color);
}


std::string sfml_utils::Item::getText() const
{
    return text->getString();
}

bool sfml_utils::Item::operator==(const Item& other)
{
    return getText() == other.getText();
}