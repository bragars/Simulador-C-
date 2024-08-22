#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "main.hpp"
#include "../../include/constants/screens.hpp"
#include "../../include/components/backButton/main.hpp"

void handleBounceBall(sf::RenderWindow &window, Screen &currentScreen)
{
  static sf::CircleShape ball(20.f);
  static sf::Vector2f velocity(200.f, 150.f); // 200 pixels/second horizontally, 150 pixels/second vertically
  static bool initialized = false;

  if (!initialized)
  {
    ball.setFillColor(sf::Color::Green);
    ball.setPosition(100.f, 100.f);
    initialized = true;
  }

  static sf::Font font;
  static sf::Text text;

  if (!font.loadFromFile("include/fonts/roboto.ttf"))
  {
    std::cerr << "Error loading font!" << std::endl;
  }

  BackButton backButton = BackButton();
  backButton.backButtonAction(currentScreen, window);

  // Clock for timing
  static sf::Clock clock;

  // Get the elapsed time
  sf::Time deltaTime = clock.restart();
  float dt = deltaTime.asSeconds();

  // Move the ball
  sf::Vector2f position = ball.getPosition();
  position += velocity * dt;

  // Check for collisions with the window borders and bounce
  if (position.x <= 0 || position.x + ball.getRadius() * 2 >= window.getSize().x)
  {
    velocity.x = -velocity.x;
  }
  if (position.y <= 0 || position.y + ball.getRadius() * 2 >= window.getSize().y)
  {
    velocity.y = -velocity.y;
  }

  ball.setPosition(position);

  // Clear screen
  window.clear();

  // Draw the ball to hidden buffer
  window.draw(ball);
  backButton.drawBackButton(window);

  // Update the window using double-buffering
  window.display();
}
