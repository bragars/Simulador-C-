#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Ball
{
public:
  sf::CircleShape shape;
  sf::Vector2f velocity;
  float mass;
  float aceleration;

  Ball(float radius, sf::Vector2f position, sf::Vector2f velocity, float mass, const sf::Color color)
  {
    this->shape = sf::CircleShape(radius);
    this->shape.setFillColor(color);
    this->shape.setPosition(position);
    this->velocity = velocity;
    this->mass = mass;
  }

  void windowBounce(sf::Vector2u size, sf::Vector2f ball_position)
  {
    float diameter = this->shape.getRadius() * 2;

    if (ball_position.x <= 0 || ball_position.x + diameter >= size.x)
    {
      this->velocity.x = -this->velocity.x;
    }

    if (ball_position.y <= 0 || ball_position.y + diameter >= size.y)
    {
      this->velocity.y = -this->velocity.y;
    }
  }

  sf::Vector2<float> getPosition()
  {
    return this->shape.getPosition();
  }

  float getMass()
  {
    return this->mass;
  }

  float getRadius()
  {
    return this->shape.getRadius();
  }

  sf::Vector2f getVelocity()
  {
    return this->velocity;
  }

  void setVelocity(sf::Vector2<float> velocity)
  {
    this->velocity = velocity;
  }

  void setPosition(sf::Vector2<float> position)
  {
    return this->shape.setPosition(position);
  }

  void reverseVelocityX()
  {
    this->velocity.x = -this->velocity.x;
  }

  void reverseVelocityY()
  {
    this->velocity.y = -this->velocity.y;
  }
};

int main()
{
  // Create the main window
  sf::RenderWindow window(sf::VideoMode(1800, 900), "Simple Simulator");

  // Create a circle shape (the ball)
  Ball first_ball(20.f, sf::Vector2(100.f, 100.f), sf::Vector2(500.f, 0.f), 50, sf::Color::Green);
  Ball second_ball(50.f, sf::Vector2(300.f, 100.f), sf::Vector2(100.f, 0.f), 200, sf::Color::Red);

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

    // Update the window
    window.display();
  }

  return 0;
}
