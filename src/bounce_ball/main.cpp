#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

int main()
{
  // Create the main window
  sf::RenderWindow window(sf::VideoMode(1800, 900), "Simple Simulator");

  // Create a circle shape (the ball)
  sf::CircleShape ball(20.f);
  ball.setFillColor(sf::Color::Green);
  ball.setPosition(100.f, 100.f);

  // Velocity of the ball
  sf::Vector2f velocity(200.f, 150.f); // 200 pixels/second horizontally, 150 pixels/second vertically

  // Create text
  sf::Font font;
  if (!font.loadFromFile("../../include/fonts/roboto.ttf"))
  {
    std::cerr << "Error loading font!" << std::endl;
  }

  sf::Text text;
  text.setFont(font);
  text.setString("Hello World");
  text.setCharacterSize(24);
  text.setFillColor(sf::Color::White);
  text.setStyle(sf::Text::Bold);

  // Clock for timing
  sf::Clock clock;

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
    window.draw(text);
    window.draw(ball);

    // Update the window using double-buffering
    window.display();
  }

  return 0;
}
