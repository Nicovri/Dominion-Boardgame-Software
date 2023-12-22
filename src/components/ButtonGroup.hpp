#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "TextButton.hpp"
#include "ImageButton.hpp"
#include <iostream>
#include <vector>

class ButtonGroup {
    std::vector<Button*> buttons;

public:
    void addButton(int value, float relativeX, float relativeY, float width, float height, const std::string& label, sf::Font& font, sf::RenderWindow& window);
    void addButton(int value, float relativeX, float relativeY, float scale, const std::string& imagePath, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    int getSelectedValue() const;
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
};