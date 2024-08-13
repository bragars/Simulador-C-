#include <bits/stdc++.h>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "../../include/objects/Ball.hpp"
#include "../../include/objects/Cannon.hpp"
#include "../../include/constants/screens.hpp"
#include "../../include/components/backButton/main.hpp"

// std::ios_base::sync_with_stdio(false)

void handleLaunchProjectile(sf::RenderWindow &window, Screen &currentScreen)
{
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
  if (!font.loadFromFile("include/fonts/roboto.ttf"))
  {
    std::cerr << "Error loading font!" << std::endl;
  }

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

  // Get the elapsed time
  sf::Time deltaTime = clock.restart();
  float dt = deltaTime.asSeconds();

  BackButton backButton = BackButton();
  backButton.backButtonAction(currentScreen, window);

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

  // // Process events
  // sf::Event event;
  // while (window.pollEvent(event))
  // {
  //   // Close window: exit
  //   if (event.type == sf::Event::Closed)
  //     window.close();

  //   else if (event.type == sf::Event::MouseButtonPressed)
  //   {
  //     if (current_ball_nmbr > 1)
  //     {
  //       is_firing = true;
  //       current_ball_nmbr--;
  //     }

  //     current_ball = balls.at(current_ball_nmbr);
  //     fired = false;
  //   }
  // }

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
  backButton.drawBackButton(window);

  // Update the window
  window.display();
}
