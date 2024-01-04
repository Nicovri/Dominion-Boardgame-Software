#include "ButtonGroup.hpp"

// Ajoute un bouton textuel à ce groupe de boutons.
void ButtonGroup::addButton(int value, float relativeX, float relativeY, float width, float height, const std::string& label, sf::Font& font, int characterSize, sf::RenderWindow& window) {
    Button *button = new TextButton(value, relativeX, relativeY, width, height, label, font, characterSize, window);
    buttons.push_back(button);

    if(buttons.size() > 1) {
        buttons.back()->setSelected(false);
    }
}

// Ajoute un bouton image à ce groupe de boutons.
void ButtonGroup::addButton(int value, float relativeX, float relativeY, float scale, sf::Texture& texture, sf::RenderWindow& window) {
    Button *button = new ImageButton(value, relativeX, relativeY, scale, texture, window);
    buttons.push_back(button);

    if(buttons.size() > 1) {
        buttons.back()->setSelected(false);
    }
}

// Enlève un bouton du groupe à l'index souhaité.
void ButtonGroup::removeButton(int index) {
    if(index >= 0 && index <= int(buttons.size()-1)) {
        buttons.erase(buttons.begin() + index);
    }
}

// Enlève un/des boutons du groupe contenant la valeur souhaitée.
void ButtonGroup::removeButtonByValue(int value) {
    buttons.erase(std::remove_if(buttons.begin(), buttons.end(),
        [value](Button* button) { return button->getValue() == value; }), buttons.end());
}

// Enlève tous les boutons du groupe.
void ButtonGroup::clear() {
    buttons.clear();
}

// Dessine les boutons sur la fenêtre.
void ButtonGroup::draw(sf::RenderWindow& window) {
    for (Button *button : buttons) {
        button->draw(window);
    }
}

// Retourne la valeur du bouton selectionné.
int ButtonGroup::getSelectedValue() const {
    for (std::size_t i = 0; i < buttons.size(); ++i) {
        if (buttons[i]->getSelected()) {
            return buttons[i]->getValue();
        }
    }
    return -1;
}

int ButtonGroup::getValueAtPosition(const sf::Vector2f& position) const {
    for (Button* button : buttons) {
        if (button->contains(position)) {
            return button->getValue();
        }
    }
    return -1;
}

// Modifie le bouton selectionné.
void ButtonGroup::setSelectedValue(int value) {
    for(std::size_t i = 0; i < buttons.size(); i++) {
        buttons[i]->setSelected(false);
        if(int(i) == value) {
            buttons[i]->setSelected(true);
        }
    }
}

// Permet au bouton cliqué d'être selectionné.
void ButtonGroup::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        for (Button *button : buttons) {
            if (button->contains(mousePos)) {
                button->setSelected(true);
                for (Button *otherButton : buttons) {
                    if (otherButton != button) {
                        otherButton->setSelected(false);
                    }
                }
                break;
            }
        }
    }
}