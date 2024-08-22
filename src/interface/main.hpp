#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <SFML/Graphics.hpp>

// Function to handle input and rendering of the start screen
void handleStartScreen(sf::RenderWindow &window, enum Screen &currentScreen);

// Function to handle input and rendering of the main menu
void handleMainMenu(sf::RenderWindow &window, enum Screen &currentScreen);

// Function to handle input and rendering of the settings screen
void handleSettings(sf::RenderWindow &window, enum Screen &currentScreen);

// Helper function to center text inside a rectangle
void centerTextInRectangle(sf::Text &text, const sf::RectangleShape &rectangle)
{
  sf::FloatRect textRect = text.getLocalBounds();
  text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
  text.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2.0f,
                   rectangle.getPosition().y + rectangle.getSize().y / 2.0f);
}

#endif // INTERFACE_HPP
