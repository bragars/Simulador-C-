#include <bits/stdc++.h>
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
    return ball_position.y < size.y && +ball_position.y + diameter >= size.y;
  }

  void gravity(sf::Vector2u size, float dt, int count)
  {
    if (!ball_is_in_bottom_edge(size))
    {
      this->setVelocity(
          sf::Vector2f(
              this->getVelocity().x,
              this->getVelocity().y + (abs(GRAVITY * dt * count) + (20 * count))));
    }

    if (ball_is_in_bottom_edge(size) && this->getMass() > 500)
    {
      this->setVelocity(sf::Vector2f(0, 0));
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

  void setMass(float mass)
  {
    this->mass = mass;
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

class Cannon : sf::Transformable
{
public:
  sf::RectangleShape cannonBase;
  sf::RectangleShape cannonBarrel;
  sf::CircleShape cannonWheel;

  float rotationAngle;

  Cannon(sf::Vector2f base, sf::Vector2f barrel, float wheel, float rotationAngle)
  {
    cannonBase.setSize(base);
    cannonBase.setOrigin(25.f, 10.f);
    cannonBase.setPosition(100.f, 550.f);
    cannonBase.setFillColor(sf::Color(100, 50, 0));

    cannonBarrel.setSize(barrel);
    cannonBarrel.setOrigin(0.f, 10.f);
    cannonBarrel.setPosition(100.f, 550.f);
    cannonBarrel.setFillColor(sf::Color::Green);

    cannonWheel.setRadius(wheel);
    cannonWheel.setOrigin(20.f, 20.f);
    cannonWheel.setPosition(100.f, 570.f);
    cannonWheel.setFillColor(sf::Color::Black);

    this->setAngle(rotationAngle);
    // rectangle.setOrigin(rectangle.getSize() / 2.f);
  }

  float getAngle()
  {
    return rotationAngle;
  }

  void setAngle(float rotationAngle)
  {
    cannonBase.rotate(rotationAngle);
    cannonBarrel.rotate(rotationAngle);
    cannonWheel.rotate(rotationAngle);
  }
};

int main()
{
  sf::RenderWindow window(sf::VideoMode(1800, 900), "Simple Simulator");
  Ball ball = Ball(20.f, sf::Vector2(100.f, 550.f), sf::Vector2(500.f, 100.f), 50, sf::Color::Red);
  ball.setMass(600);

  Cannon cannon = Cannon(
      sf::Vector2f(50.f, 20.f),
      sf::Vector2f(100.f, 20.f),
      20.f, -10.f);

  bool is_firing = false;
  bool fired = false;

  // Clock for timing
  sf::Clock clock;

  // Start the game loop
  while (window.isOpen())
  {
    // Get the elapsed time
    sf::Time deltaTime = clock.restart();
    float dt = deltaTime.asSeconds();

    if (is_firing) {
      ball.gravity(window.getSize(), dt, 1);
    }

    if (is_firing)
    {
      sf::Vector2f ball_pos = ball.getPosition();
      sf::FloatRect cannonAngle = cannon.cannonBarrel.getGlobalBounds();

      if (!fired) {
        ball_pos.y = cannonAngle.top;
        fired = true;
      }

      ball_pos.x += ball.getVelocity().x * dt;
      ball_pos.y += ball.getVelocity().y * dt;

      ball.setPosition(ball_pos);
    }

    // Process events
    sf::Event event;
    while (window.pollEvent(event))
    {
      // Close window: exit
      if (event.type == sf::Event::Closed)
        window.close();

      else if (event.type == sf::Event::MouseButtonPressed)
      {
        // attack
        std::cout << "mouse button pressed" << std::endl;
        is_firing = true;
      }

      else if (event.type == sf::Event::KeyPressed)
      {
        // attack
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
          std::cout << "key pressed" << std::endl;
      }
    }

    // Clear screen
    window.clear();

    // Draw the cannon
    window.draw(cannon.cannonBase);
    window.draw(cannon.cannonWheel);
    window.draw(cannon.cannonBarrel);

    if (is_firing)
    {
      window.draw(ball.shape);
    }

    // Update the window
    window.display();
  }

  return 0;
}
