#include <SFML/Graphics.hpp>

// Classe représentant un champ de saisie sur l'interface SFML.
class TextInputField {
private:
    sf::RectangleShape inputField;
    sf::Text text;
    std::string content;

public:
    TextInputField(float relativeX, float relativeY, sf::Font& font, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void setPositionRelativeToWindow(float relativeX, float relativeY, sf::RenderWindow& window);
    void clear();
    void updateText();
    const std::string& getContent() const;
    void handleEvent(const sf::Event& event);
};