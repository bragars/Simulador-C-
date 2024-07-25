#ifndef CANNON_HPP
#define CANNON_HPP

#include <bits/stdc++.h>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "../constants/physics_constants.hpp"

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

#endif
