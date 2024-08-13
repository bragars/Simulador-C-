#ifndef BACK_BUTTON_HPP
#define BACK_BUTTON_HPP

#include <SFML/Graphics.hpp>
#include "../../constants/screens.hpp"

class BackButton
{
public:
  BackButton();
  static sf::Text backButtonText;
  static sf::RectangleShape backButtonShape;
  void backButtonAction(Screen &currentScreen, sf::RenderWindow &window);
  void drawBackButton(sf::RenderWindow &window);
};

#endif // BACK_BUTTON_HPP
