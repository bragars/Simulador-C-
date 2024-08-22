#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "../../include/objects/Ball.hpp"
#include "../../include/constants/screens.hpp"
#include "../../include/constants/physics_constants.hpp"

void handleElasticCollision(sf::RenderWindow &window, Screen &currentScreen)
{
  // Create a circle shape (the ball)
  static Ball first_ball(20.f, sf::Vector2(100.f, 100.f), sf::Vector2(500.f, 0.f), 50, sf::Color::Green);
  static Ball second_ball(50.f, sf::Vector2(300.f, 100.f), sf::Vector2(100.f, 0.f), 200, sf::Color::Red);

  static BackButton backButton = BackButton();
  backButton.backButtonAction(currentScreen, window);

  // Clock for timing
  static sf::Clock clock;

  // Get the elapsed time
  sf::Time deltaTime = clock.restart();
  float dt = deltaTime.asSeconds();

  // Move the balls
  sf::Vector2f first_ball_position = first_ball.getPosition();
  sf::Vector2f second_ball_position = second_ball.getPosition();
  first_ball_position += first_ball.getVelocity() * dt;
  second_ball_position += second_ball.getVelocity() * dt;

  float diameter = first_ball.getRadius() * 2;

  first_ball.windowBounce(window.getSize(), first_ball_position);
  second_ball.windowBounce(window.getSize(), second_ball_position);

  if (first_ball_position.x < second_ball_position.x && first_ball_position.x + diameter > second_ball_position.x)
  {
    first_ball.velocity.x = -first_ball.velocity.x;
    second_ball.setVelocity(sf::Vector2(-first_ball.getVelocity().x, first_ball.getVelocity().y));
  }

  first_ball.setPosition(first_ball_position);
  second_ball.setPosition(second_ball_position);

  // elastic

  // Clear screen
  window.clear();

  // Draw the balls
  window.draw(first_ball.shape);
  window.draw(second_ball.shape);
  backButton.drawBackButton(window);

  // Update the window
  window.display();
}
