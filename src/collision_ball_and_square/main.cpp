#include <sstream>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

int main()
{
  // Create the main window
  sf::RenderWindow window(sf::VideoMode(1800, 900), "Simple Simulator");

  // Enable vertical sync
  window.setVerticalSyncEnabled(true);

  // Create a circle shape (the ball)
  sf::CircleShape first_ball(20.f);
  first_ball.setFillColor(sf::Color::Green);
  first_ball.setPosition(200.f, 200.f);

  // Create a rectangle shape
  sf::RectangleShape rectangle;
  rectangle.setSize(sf::Vector2f(600.f, 300.f));
  rectangle.setPosition(400.f, 300.f);

  // Velocity of the ball
  sf::Vector2f fst_velocity(500.f, 350.f); // 200 pixels/second horizontally, 150 pixels/second vertically

  // Clock for timing
  sf::Clock clock;

  // Info
  sf::Font font;
  if (!font.loadFromFile("../../include/fonts/roboto.ttf")) 
  {
    std::cerr << "Error loading font!" << std::endl;
  }

  sf::Text fst_ball_x, fst_ball_y, snd_ball_x, snd_ball_y;

  fst_ball_x.setFont(font);
  fst_ball_y.setFont(font);

  fst_ball_x.setFillColor(sf::Color::White);
  fst_ball_y.setFillColor(sf::Color::White);

  fst_ball_x.setStyle(sf::Text::Bold);
  fst_ball_y.setStyle(sf::Text::Bold);

  fst_ball_x.setPosition(10, 10);
  fst_ball_y.setPosition(10, 50);

  // Start the game loop
  while (window.isOpen())
  {
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

    float rotation_speed = 90.f;
    rectangle.rotate(rotation_speed * dt);

    // Move the balls
    sf::Vector2f first_ball_position = first_ball.getPosition();
    first_ball_position += fst_velocity * dt;

    float diameter = first_ball.getRadius() * 2;
    std::ostringstream oss;

    // Check for collisions with the window borders and bounce for the first ball
    if (first_ball_position.x <= 0 || first_ball_position.x + diameter >= window.getSize().x)
    {
      fst_velocity.x = -fst_velocity.x;
    }

    if (first_ball_position.y <= 0 || first_ball_position.y + diameter >= window.getSize().y)
    {
      fst_velocity.y = -fst_velocity.y;
    }

    // Check for collisions with the rectangle for the first ball
    sf::FloatRect ballBounds = first_ball.getGlobalBounds();
    sf::FloatRect rectBounds = rectangle.getGlobalBounds();

    if (ballBounds.intersects(rectBounds))
    {
      // Calculate edges of the rectangle
      float rectLeft = rectBounds.left;
      float rectRight = rectBounds.left + rectBounds.width;
      float rectTop = rectBounds.top;
      float rectBottom = rectBounds.top + rectBounds.height;

      // Check collision with the left or right side for the first ball
      if ((first_ball_position.x < rectLeft && first_ball_position.x + diameter > rectLeft) ||
          (first_ball_position.x < rectRight && first_ball_position.x + diameter > rectRight))
      {
        fst_velocity.x = -500;
      }

      // Check collision with the top or bottom side for the first ball
      if (first_ball_position.y < rectBottom && first_ball_position.y + diameter > rectBottom)
      {
        fst_velocity.y = 350;
      }
      if (first_ball_position.y < rectTop && first_ball_position.y + diameter > rectTop)
      {
        fst_velocity.y = -350;
      }
    }

    // Update ball positions
    first_ball.setPosition(first_ball_position);

    // Update the texts with the positions of the balls
    oss << "First Ball X: " << first_ball.getPosition().x;
    fst_ball_x.setString(oss.str());
    oss.str("");
    oss << "First Ball Y: " << first_ball.getPosition().y;
    fst_ball_y.setString(oss.str());
    oss.str("");

    // Clear screen
    window.clear();

    // Draw the info
    window.draw(fst_ball_x);
    window.draw(fst_ball_y);

    // Draw the balls
    window.draw(first_ball);

    // Draw the rectangle
    window.draw(rectangle);

    // Update the window
    window.display();
  }

  return 0;
}
