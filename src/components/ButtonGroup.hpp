#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "TextButton.hpp"
#include "ImageButton.hpp"
#include <iostream>
#include <vector>

// Classe représentant un groupe de boutons sur l'interface SFML.
class ButtonGroup {
    std::vector<Button*> buttons;

public:
    void addButton(int value, float relativeX, float relativeY, float width, float height, const std::string& label, sf::Font& font, int characterSize, sf::RenderWindow& window);
    void addButton(int value, float relativeX, float relativeY, float scale, sf::Texture& texture, sf::RenderWindow& window);
    void removeButton(int index);
    void clear();
    void draw(sf::RenderWindow& window);
    int getSelectedValue() const;
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
};