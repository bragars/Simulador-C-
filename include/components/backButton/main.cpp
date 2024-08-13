#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "main.hpp"
#include "../../constants/screens.hpp"
#include "./main.hpp"

sf::Text BackButton::backButtonText;
sf::RectangleShape BackButton::backButtonShape;

BackButton::BackButton()
{
  static sf::Font font;
  static bool fontLoaded = false;

  if (!fontLoaded)
  {
    if (!font.loadFromFile("include/fonts/roboto.ttf"))
    {
      std::cerr << "Error loading font!" << std::endl;
    }
    fontLoaded = true;
  }

  backButtonText.setFont(font);
  backButtonText.setString("Back");
  backButtonText.setCharacterSize(20);
  backButtonText.setFillColor(sf::Color::White);

  sf::FloatRect backRect = backButtonText.getLocalBounds();
  backButtonText.setOrigin(backRect.left + backRect.width / 2.0f,
                           backRect.top + backRect.height / 2.0f);
  backButtonText.setPosition(100.f, 500.f);

  // Initialize back button shape
  backButtonShape.setSize(sf::Vector2f(100.f, 40.f));
  backButtonShape.setFillColor(sf::Color::Red);
  backButtonShape.setPosition(backButtonText.getPosition().x - backButtonText.getLocalBounds().width / 2.f,
                              backButtonText.getPosition().y - backButtonText.getLocalBounds().height / 2.f);
};

void BackButton::backButtonAction(Screen &currentScreen, sf::RenderWindow &window)
{
  // Check for mouse clicks
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
  {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    if (backButtonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
    {
      currentScreen = Screen::Start;
    }
  }
}

void BackButton::drawBackButton(sf::RenderWindow &window)
{
  window.draw(backButtonShape);
  window.draw(backButtonText);
}
