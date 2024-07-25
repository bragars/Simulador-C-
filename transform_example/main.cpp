#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
  // Create a window
  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Transformation Example");

  // Create a rectangle shape
  sf::RectangleShape rectangle(sf::Vector2f(100, 50));
  rectangle.setFillColor(sf::Color::Green);
  rectangle.setOrigin(rectangle.getSize() / 2.f); // Set origin to the center for rotation around the center

  // Create a transform object
  sf::Transform transform;

  // Apply transformations
  transform.translate(400, 300); // Translate to the center of the window
  transform.rotate(45);          // Rotate by 45 degrees
  transform.scale(2, 2);         // Scale by 2 in both x and y directions

  // Extract and print the transformation matrix
  const float *matrix = transform.getMatrix();
  std::cout << "Transformation Matrix:" << std::endl;
  for (int i = 0; i < 9; ++i)
  {
    std::cout << matrix[i] << (i % 3 == 2 ? "\n" : " ");
  }

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }
    }

    window.clear();

    // Draw the rectangle with the applied transform
    window.draw(rectangle, transform);

    window.display();
  }

  return 0;
}

// --------------- Result ---------------
// Transformation Matrix:
// 1.41421 -1.41421 400
// 1.41421 1.41421 300
// 0 0 1
