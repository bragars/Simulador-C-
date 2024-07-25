#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

float GRAVITY = 9.8;

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

    this->sides_bounce(size, ball_position, diameter);
    this->bottom_bounce(size, ball_position, diameter);
  }

  void bottom_bounce(sf::Vector2u size, sf::Vector2f ball_position, float diameter)
  {
    if (ball_position.y <= 0 || ball_position.y + diameter >= size.y)
    {
      this->velocity.y = -this->velocity.y;
    }
  }

  bool ball_is_in_bottom_edge(sf::Vector2u size)
  {
    float diameter = this->shape.getRadius() * 2;

    sf::Vector2f ball_position = this->getPosition();
    return ball_position.y < size.y && + ball_position.y + diameter >= size.y;
  }

  void gravity(sf::Vector2u size, float dt, int count)
  {
    if (!ball_is_in_bottom_edge(size)) {
      this->setVelocity(
        sf::Vector2f(
          this->getVelocity().x,
          this->getVelocity().y + (abs(GRAVITY * dt * count) + (20 * count))
        )
      );
    }

    if (this->getMass() > 500) {
      this->setVelocity(sf::Vector2f(0,0));
    }
  }

  void sides_bounce(sf::Vector2u size, sf::Vector2f ball_position, float diameter)
  {
    if (ball_position.x <= 0 || ball_position.x + diameter >= size.x)
    {
      this->velocity.x = -this->velocity.x;
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

  float getWeight()
  {
    return this->mass * GRAVITY;
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
  std::vector<Ball> balls;

  for (size_t i = 0; i < 10; i++)
  {
    balls.push_back(Ball(20.f, sf::Vector2(100.f * (i + 1), 50.f * (i + 1)), sf::Vector2(500.f, 100.f), 50, sf::Color::Green));
  }

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

    int count = 1;
    for (Ball &ball : balls)
    {
      ball.gravity(window.getSize(), dt, count);
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

    // Update the window
    window.display();
  }

  return 0;
}
