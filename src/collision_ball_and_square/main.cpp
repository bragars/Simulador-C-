#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <sstream>
#include <iostream>
#include <string>
#include "main.hpp"
#include "../../include/constants/screens.hpp"
#include "../../include/components/backButton/main.hpp"

void handleBallAndSquareCollision(sf::RenderWindow &window, Screen &currentScreen)
{
  // Create a circle shape (the ball)
  static sf::CircleShape ball(20.f);
  static sf::Vector2f velocity(200.f, 150.f); // 200 pixels/second horizontally, 150 pixels/second vertically
  static bool initialized = false;

  if (!initialized)
  {
    ball.setFillColor(sf::Color::Green);
    ball.setPosition(100.f, 100.f);
    initialized = true;
  }

  // Create a rectangle shape
  static sf::RectangleShape rectangle;
  rectangle.setSize(sf::Vector2f(600.f, 300.f));
  rectangle.setPosition(400.f, 300.f);

  // Info
  sf::Font font;
  if (!font.loadFromFile("include/fonts/roboto.ttf"))
  {
    std::cerr << "Error loading font!" << std::endl;
  }

  // Clock for timing
  static sf::Clock clock;
  sf::Text fst_ball_x, fst_ball_y, snd_ball_x, snd_ball_y;

  fst_ball_x.setFont(font);
  fst_ball_y.setFont(font);

  fst_ball_x.setFillColor(sf::Color::White);
  fst_ball_y.setFillColor(sf::Color::White);

  fst_ball_x.setStyle(sf::Text::Bold);
  fst_ball_y.setStyle(sf::Text::Bold);

  fst_ball_x.setPosition(10, 10);
  fst_ball_y.setPosition(10, 50);

  // Get the elapsed time
  sf::Time deltaTime = clock.restart();
  float dt = deltaTime.asSeconds();

  float rotation_speed = 90.f;
  rectangle.rotate(rotation_speed * dt);

  // Move the balls
  sf::Vector2f position = ball.getPosition();
  position += velocity * dt;

  float diameter = ball.getRadius() * 2;
  std::ostringstream oss;

  // Check for collisions with the window borders and bounce for the first ball
  if (position.x <= 0 || position.x + diameter >= window.getSize().x)
  {
    velocity.x = -velocity.x;
  }

  if (position.y <= 0 || position.y + diameter >= window.getSize().y)
  {
    velocity.y = -velocity.y;
  }

  // Check for collisions with the rectangle for the first ball
  sf::FloatRect ballBounds = ball.getGlobalBounds();
  sf::FloatRect rectBounds = rectangle.getGlobalBounds();

  BackButton backButton = BackButton();
  backButton.backButtonAction(currentScreen, window);

  if (ballBounds.intersects(rectBounds))
  {
    // Calculate edges of the rectangle
    float rectLeft = rectBounds.left;
    float rectRight = rectBounds.left + rectBounds.width;
    float rectTop = rectBounds.top;
    float rectBottom = rectBounds.top + rectBounds.height;

    // Check collision with the left or right side for the first ball
    if ((position.x < rectLeft && position.x + diameter > rectLeft) ||
        (position.x < rectRight && position.x + diameter > rectRight))
    {
      velocity.x = -500;
    }

    // Check collision with the top or bottom side for the first ball
    if (position.y < rectBottom && position.y + diameter > rectBottom)
    {
      velocity.y = 350;
    }
    if (position.y < rectTop && position.y + diameter > rectTop)
    {
      velocity.y = -350;
    }
  }

  // Update ball positions
  ball.setPosition(position);

  // Update the texts with the positions of the balls
  oss << "First Ball X: " << ball.getPosition().x;
  fst_ball_x.setString(oss.str());
  oss.str("");
  oss << "First Ball Y: " << ball.getPosition().y;
  fst_ball_y.setString(oss.str());
  oss.str("");

  // Clear screen
  window.clear();

  // Draw the info
  window.draw(fst_ball_x);
  window.draw(fst_ball_y);

  // Draw the balls
  window.draw(ball);

  // Draw the rectangle
  window.draw(rectangle);
  backButton.drawBackButton(window);

  // Update the window
  window.display();
}
