#include "../../include/sfml_utils/item_list.hpp"

sfml_utils::ItemList::ItemList(){}

sfml_utils::ItemList::ItemList(std::vector<std::string> vec, float x, float y)
{
    for(int i = 0; i < vec.size(); ++i)
    {
        add(vec[i], x, y);
    }
    word = "";
}


void sfml_utils::ItemList::setPosition(float x, float y)
{
    int index = 0;
    for(std::vector<Item>::iterator i = itemlist.begin(); i != itemlist.end(); ++i)
    {
        i->setPosition(x, y + index * i->getLocalBounds().size.y);
        index++;
    }
}

void sfml_utils::ItemList::setSize(float x, float y)
{
    for(std::vector<Item>::iterator i = itemlist.begin(); i != itemlist.end(); ++i)
    {
        i->setSize(x, y);
    }
    setPosition(getPosition().x, getPosition().y);
}

void sfml_utils::ItemList::add(std::string item, float x, float y)
{    
    if(itemlist.empty())
    {
        Item temp(item, sf::Vector2f({x, y}));
        itemlist.push_back(temp);
        setPosition(getPosition().x, getPosition().y);
        return;
    }

    sf::FloatRect dimension = itemlist[0].getLocalBounds();
    Item temp(item, sf::Vector2f({x, y}));
    itemlist.push_back(temp);
    setPosition(getPosition().x, getPosition().y);
}

void sfml_utils::ItemList::remove(std::string item)
{
    for(int i = 0; i < itemlist.size(); i++)
    {
        if(itemlist[i].getText() == item)
        {
            itemlist.erase(itemlist.begin() + i);
            break;
        }
    }
    setPosition(getPosition().x, getPosition().y);
}

sf::FloatRect sfml_utils::ItemList::getLocalBounds()
{
    sf::FloatRect rec = itemlist.begin()->getLocalBounds();
    int count = 0;
    for(std::vector<Item>::iterator i = itemlist.begin(); i != itemlist.end(); ++i)
    {
        count++;
    }
    rec.size.y *= count;
    return rec;
}

void sfml_utils::ItemList::addEventHandler(sf::RenderWindow& window, const sf::Event& event)
{
    for(int i = 0; i < itemlist.size(); ++i)
    {
        if(MouseEvents<Item>::hovered(itemlist[i], window))
        {
            itemlist[i].setFillColor(sf::Color::Blue);
        }
        else
        {
            if(i != selected_index)
            {
                itemlist[i].setFillColor(sf::Color::Transparent);
            }
            else
            {
                itemlist[i].setFillColor(sf::Color(128, 128, 128));
            }
        }

        if(MouseEvents<Item>::mouseClicked(itemlist[i], window))
        {
            // if mouse clicked on an option, closed the bar
            // set clicked state to be true
            selected_index = i;
            States::setStateEnable(States::APPEAR, false);
            States::setStateEnable(States::CLICKED, true);
            word = itemlist[i].getText();
            itemlist[i].setFillColor(sf::Color(128, 128, 128));
        }
    }
}

void sfml_utils::ItemList::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    if(itemlist.empty()) return;
    for(int i = 0; i < itemlist.size(); ++i)
    {
        window.draw(itemlist[i]);
    }
}

int sfml_utils::ItemList::getSelectedIndex()
{
    return selected_index;
}