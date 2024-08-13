#include <SFML/Graphics.hpp>
#include <iostream>
#include "../bounce_ball/main.hpp"
#include "../launch_projectile/main.hpp"
#include "../collision_ball_and_square/main.hpp"
#include "../../include/constants/screens.hpp"
#include "../../include/components/backButton/main.hpp"

// Function to handle input and rendering of the start screen
void handleStartScreen(sf::RenderWindow &window, enum Screen &currentScreen);

// Function to handle input and rendering of the main menu
void handleMainMenu(sf::RenderWindow &window, enum Screen &currentScreen);

// Function to handle input and rendering of the settings screen
void handleSettings(sf::RenderWindow &window, enum Screen &currentScreen);

void handleMainMenu(sf::RenderWindow &window, enum Screen &currentScreen)
{
  // Load fonts and create text objects
  static sf::Font font;
  static bool fontLoaded = false;
  if (!fontLoaded)
  {
    if (!font.loadFromFile("include/fonts/roboto.ttf"))
    {
      std::cerr << "Error loading font in interface!" << std::endl;
    }
    fontLoaded = true;
  }

  static sf::Text title("Welcome to the Game", font, 50);
  title.setPosition(200, 100);

  static sf::Text startButton("Start", font, 30);
  startButton.setPosition(350, 300);

  static sf::Text settingsButton("Settings", font, 30);
  settingsButton.setPosition(350, 400);

  // Check for mouse clicks
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
  {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (settingsButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
    {
      // Change to the settings screen
      currentScreen = Screen::Settings;
    }
    if (startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
    {
      // Change to the main menu screen
      currentScreen = Screen::Start;
    }
  }

  // Draw elements
  window.draw(title);
  window.draw(settingsButton);
  window.draw(startButton);
}

void handleStartScreen(sf::RenderWindow &window, enum Screen &currentScreen)
{
  static sf::Font font;
  static bool fontLoaded = false;
  if (!fontLoaded)
  {
    if (!font.loadFromFile("include/fonts/roboto.ttf"))
    {
      std::cerr << "Error loading font!" << std::endl;
    }
    fontLoaded = true;
  }

  sf::Color Gray(128, 128, 128);

  static sf::Text title("Simulations", font, 50);
  title.setPosition(300, 100);

  static sf::Text backButton("Back to Menu", font, 30);
  backButton.setPosition(300, 400);

  sf::Vector2f rectangleSize = sf::Vector2f(100.f, 40.f);

  static sf::RectangleShape simulation(rectangleSize);
  simulation.setFillColor(Gray);
  simulation.setPosition(300, 200);

  sf::Text text;
  text.setFont(font);
  text.setString("Bounce Ball");
  text.setCharacterSize(20);
  text.setFillColor(sf::Color::White);

  sf::FloatRect textRect = text.getLocalBounds();
  text.setOrigin(textRect.left + textRect.width / 2.0f,
                 textRect.top + textRect.height / 2.0f);
  text.setPosition(simulation.getPosition().x + rectangleSize.x / 2.0f,
                   simulation.getPosition().y + rectangleSize.y / 2.0f);

  static sf::RectangleShape simulation2(rectangleSize);
  simulation2.setFillColor(Gray);
  simulation2.setPosition(300, 250);

  sf::Text text2;
  text2.setFont(font);
  text2.setString("Launch Projectile");
  text2.setCharacterSize(20);
  text2.setFillColor(sf::Color::White);

  sf::FloatRect text2Rect = text2.getLocalBounds();
  text2.setOrigin(text2Rect.left + text2Rect.width / 2.0f,
                  text2Rect.top + text2Rect.height / 2.0f);
  text2.setPosition(simulation2.getPosition().x + rectangleSize.x / 2.0f,
                    simulation2.getPosition().y + rectangleSize.y / 2.0f);

  static sf::RectangleShape simulation3(rectangleSize);
  simulation3.setFillColor(Gray);
  simulation3.setPosition(300, 320);

  sf::Text text3;
  text3.setFont(font);
  text3.setString("Ball and square collision");
  text3.setCharacterSize(20);
  text3.setFillColor(sf::Color::White);

  sf::FloatRect text3Rect = text3.getLocalBounds();
  text3.setOrigin(text3Rect.left + text3Rect.width / 2.0f,
                  text3Rect.top + text3Rect.height / 2.0f);
  text2.setPosition(simulation3.getPosition().x + rectangleSize.x / 2.0f,
                    simulation3.getPosition().y + rectangleSize.y / 2.0f);

  // static std::vector<sf::RectangleShape> simulations(4);
  // static bool rectanglesInitialized = false;

  // if (!rectanglesInitialized)
  // {
  //     for (size_t i = 0; i < simulations.size(); i++)
  //     {
  //         sf::RectangleShape &simulation = simulations[i];
  //         simulation.setSize(rectangleSize);
  //         simulation.setFillColor(sf::Color::Green);

  //         int x = 200 + (i % 3) * 120;
  //         int y = 200 + (i / 3) * 120;

  //         simulation.setPosition(x, y);
  //     }
  //     rectanglesInitialized = true;
  // }

  // Check for mouse clicks
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
  {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (backButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
    {
      // Change to the start screen
      currentScreen = Screen::MainMenu;
    }
    if (simulation.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
    {
      // Change to the start screen
      currentScreen = Screen::BounceBall;
    }
    if (simulation2.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
    {
      // Change to the start screen
      currentScreen = Screen::LaunchProjectile;
    }
    if (simulation3.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
    {
      // Change to the start screen
      currentScreen = Screen::BallAndSquareCollision;
    }
    // for (size_t i = 3; i < 7; i++)
    // {
    //   sf::RectangleShape &simulation = simulations[i];
    //   if (simulation.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
    //   {
    //     currentScreen = static_cast<Screen>(i);
    //   }
    // }
  }

  // Draw elements
  window.draw(title);
  window.draw(backButton);
  window.draw(simulation);
  window.draw(text);
  window.draw(simulation2);
  window.draw(text2);
  window.draw(simulation3);
  window.draw(text3);
  // for (const auto &simulation : simulations)
  // {
  //     window.draw(simulation);
  // }
}

void handleSettings(sf::RenderWindow &window, enum Screen &currentScreen)
{
  static sf::Font font;
  static bool fontLoaded = false;
  if (!fontLoaded)
  {
    if (!font.loadFromFile("include/fonts/roboto.ttf"))
    {
      std::cerr << "Error loading font!" << std::endl;
    }
    fontLoaded = true;
  }

  static sf::Text title("Settings", font, 50);
  title.setPosition(300, 100);

  static sf::Text backButton("Back to Main Menu", font, 30);
  backButton.setPosition(250, 300);

  // Check for mouse clicks
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
  {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (backButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
    {
      // Change to the main menu screen
      currentScreen = Screen::MainMenu;
    }
  }

  // Draw elements
  window.draw(title);
  window.draw(backButton);
}

int main()
{
  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Application");
  window.setVerticalSyncEnabled(true);

  Screen currentScreen = Screen::MainMenu;

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }

      // Handle input and update state based on the current screen
      switch (currentScreen)
      {
      case Screen::Start:
        handleStartScreen(window, currentScreen);
        break;
      case Screen::MainMenu:
        handleMainMenu(window, currentScreen);
        break;
      case Screen::Settings:
        handleSettings(window, currentScreen);
        break;
      case Screen::BounceBall:
        handleBounceBall(window, currentScreen);
        break;
      case Screen::LaunchProjectile:
        handleLaunchProjectile(window, currentScreen);
        break;
      case Screen::BallAndSquareCollision:
        handleBallAndSquareCollision(window, currentScreen);
        break;
        // case Screen::ElasticCollision:
        //   handleElasticCollision(window, currentScreen);
        //   break;
        // case Screen::FallenBalls:
        //   handleFallenBalls(window, currentScreen);
        //   break;
        // }
      }
    }

    // Clear the window and render the current screen
    window.clear();
    switch (currentScreen)
    {
    case Screen::Start:
      handleStartScreen(window, currentScreen);
      break;
    case Screen::MainMenu:
      handleMainMenu(window, currentScreen);
      break;
    case Screen::Settings:
      handleSettings(window, currentScreen);
      break;
    case Screen::BounceBall:
      handleBounceBall(window, currentScreen);
      break;
    case Screen::LaunchProjectile:
      handleLaunchProjectile(window, currentScreen);
      break;
    case Screen::BallAndSquareCollision:
      handleBallAndSquareCollision(window, currentScreen);
      break;
    }
    window.display();
  }

  return 0;
}
