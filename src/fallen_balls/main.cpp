#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "../../include/constants/screens.hpp"
#include "../../include/objects/Ball.hpp"
#include "../../include/constants/physics_constants.hpp"

void handleFallenBalls(sf::RenderWindow &window, Screen &currentScreen)
{
  BackButton backButton = BackButton();
  backButton.backButtonAction(currentScreen, window);

  std::vector<Ball> balls;

  for (size_t i = 0; i < 10; i++)
  {
    balls.push_back(Ball(20.f, sf::Vector2(100.f * (i + 1), 50.f * (i + 1)), sf::Vector2(500.f, 100.f), 50, sf::Color::Green));
  }

  // Clock for timing
  sf::Clock clock;

  // Process events
  sf::Event event;
  while (window.pollEvent(event))
  {
    // Close window: exit
    if (event.type == sf::Event::Closed)
      window.close();
  }

  // Get the elapsed time
  sf::Time deltaTime = clock.restart();
  float dt = deltaTime.asSeconds();

  bool is_firing = false;
  int count = 1;
  for (Ball &ball : balls)
  {
    ball.gravity(window.getSize(), dt, count, is_firing);
    count++;
  }

  for (Ball &ball : balls)
  {
    sf::Vector2f ball_pos = ball.getPosition();
    ball_pos.y += ball.getVelocity().y * dt;
    ball.setPosition(ball_pos);
    ball.windowBounce(window.getSize(), ball_pos);
  }

  // Clear screen
  window.clear();

  // Draw the balls
  for (Ball const &ball : balls)
  {
    window.draw(ball.shape);
  }

  backButton.drawBackButton(window);
  // Update the window
  window.display();
}
