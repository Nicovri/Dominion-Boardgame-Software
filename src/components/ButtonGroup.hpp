#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include <iostream>
#include <vector>

class ButtonGroup {
    std::vector<Button> buttons;
    std::vector<int> buttonValues;

public:
    void addButton(float relativeX, float relativeY, float width, float height, const std::string& label, sf::Font& font, sf::RenderWindow& window, int value);
    void draw(sf::RenderWindow& window);
    int getSelectedValue() const;
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
};