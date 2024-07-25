#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

int main()
{
  // Create the main window
  sf::RenderWindow window(sf::VideoMode(1800, 900), "Simple Simulator");

  // Create texture
  sf::Texture texture;
  if (!texture.loadFromFile(".textures/image.png"))
  {
    return -1;
  }

  texture.setSmooth(true);

  int width = 200;
  int height = 200;

  sf::RenderTexture renderTexture;
  renderTexture.create(width, height);

  // Create a circle shape
  sf::CircleShape circleShape(width / 2.0f);
  circleShape.setTexture(&texture);
  circleShape.setPosition(0, 0);

  // Draw the circle shape with the texture onto the render texture
  renderTexture.clear(sf::Color::Transparent);
  renderTexture.draw(circleShape);
  renderTexture.display();

  // Create a sprite from the render texture
  sf::Sprite roundedSprite(renderTexture.getTexture());

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

    window.clear();

    // Draw the ball to hidden buffer
    window.draw(roundedSprite);

    // Update the window using double-buffering
    window.display();
  }

  return 0;
}
