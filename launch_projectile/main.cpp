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

  Ball() {}

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
    return ball_position.y < size.y && ball_position.y + diameter >= size.y;
  }

  void gravity(sf::Vector2u size, float dt, int count, bool &is_firing)
  {
    if (!ball_is_in_bottom_edge(size))
    {
      this->setVelocity(
          sf::Vector2f(
              this->getVelocity().x,
              this->getVelocity().y + (abs(GRAVITY * dt * count) + (20 * count))));
    }
    else
    {
      this->setPosition(sf::Vector2f(0, this->getPosition().y));

      // fade away after 3 SECONDS
      sleep(1);
      is_firing = false;
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

  int cylinderQnt = 0;
  float rotationAngle;
  float force;

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
  
  float getForce()
  {
    return force;
  }

  void setAngle(float rotationAngle)
  {
    cannonBase.rotate(rotationAngle);
    cannonBarrel.rotate(rotationAngle);
    cannonWheel.rotate(rotationAngle);
  }

  void setCylinderQnt(int cylinderQnt)
  {
    this->cylinderQnt = cylinderQnt;
  }

  void setForce(float force)
  {
    this->force = force;
  }
};

int main()
{
  sf::RenderWindow window(sf::VideoMode(1200, 650), "Simple Simulator");
  // sf::RenderWindow window(sf::VideoMode(1800, 900), "Simple Simulator");

  Cannon cannon = Cannon(
      sf::Vector2f(50.f, 20.f),
      sf::Vector2f(100.f, 20.f),
      20.f, -10.f);

  cannon.setCylinderQnt(6);
  cannon.setForce(2);

  std::vector<Ball> balls = std::vector(cannon.cylinderQnt + 1, Ball());

  for (int i = 1; i <= cannon.cylinderQnt; i++)
  {
    Ball ball = Ball(20.f, sf::Vector2(100.f + 2 * i, 550.f + 2 * i), sf::Vector2(500.f + 2 * i, 100.f + 2 * i), 50, sf::Color::Red);
    ball.setMass(600);
    balls[i] = ball;
  }

  bool is_firing = false;
  bool fired = false;

  int current_ball_nmbr = cannon.cylinderQnt;

  std::cout << "balls.size(): " << balls.size() << std::endl;
  std::cout << "current_ball_nmbr: " << current_ball_nmbr << std::endl;

  // Clock for timing
  sf::Clock clock;

  sf::Font font;
  font.loadFromFile("./fonts/roboto.ttf");
  // if (!font.loadFromFile("./fonts/roboto.ttf")) {
  //   std::cerr << "Error loading font!" << std::endl;
  //   // Handle the error appropriately
  // }

  sf::Text ball_count;
  ball_count.setFont(font);

  std::ostringstream oss;
  oss << "Remaining: " << current_ball_nmbr - 1;
  ball_count.setString(oss.str());
  oss.str("");

  ball_count.setCharacterSize(24);
  ball_count.setFillColor(sf::Color::White);
  ball_count.setStyle(sf::Text::Bold);

  ball_count.setPosition(100.f, 100.f);
  Ball current_ball = balls.at(0);

  // Start the game loop
  while (window.isOpen())
  {
    // Get the elapsed time
    sf::Time deltaTime = clock.restart();
    float dt = deltaTime.asSeconds();

    if (is_firing)
    {
      sf::Vector2f ball_pos = current_ball.getPosition();
      sf::FloatRect cannonAngle = cannon.cannonBarrel.getGlobalBounds();

      if (!fired)
      {
        ball_pos.y = cannonAngle.top;
        fired = true;
      }

      ball_pos.x += current_ball.getVelocity().x * (cannon.getForce() * dt);
      ball_pos.y += current_ball.getVelocity().y * (cannon.getForce() * dt);

      current_ball.gravity(window.getSize(), dt, 1, is_firing);
      current_ball.setPosition(ball_pos);
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
        if (current_ball_nmbr > 1)
        {
          is_firing = true;
          current_ball_nmbr--;
        }

        current_ball = balls.at(current_ball_nmbr);
        fired = false;
      }
    }

    // Clear screen
    window.clear();

    // Draw the cannon
    window.draw(cannon.cannonBase);
    window.draw(cannon.cannonWheel);
    window.draw(cannon.cannonBarrel);

    if (is_firing && current_ball_nmbr > 0)
    {
      oss << "Remaining: " << current_ball_nmbr - 1;
      ball_count.setString(oss.str());
      oss.str("");

      window.draw(current_ball.shape);
    }

    window.draw(ball_count);

    // Update the window
    window.display();
  }

  return 0;
}
