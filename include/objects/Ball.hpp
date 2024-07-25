#ifndef BALL_HPP
#define BALL_HPP

#include <bits/stdc++.h>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <iostream>
#include "../constants/physics_constants.hpp"

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

#endif
