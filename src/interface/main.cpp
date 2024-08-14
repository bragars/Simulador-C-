#include <SFML/Graphics.hpp>
#include <iostream>
#include "../bounce_ball/main.hpp"
#include "../launch_projectile/main.hpp"
#include "../collision_ball_and_square/main.hpp"
#include "../elastic_collision/main.hpp"
#include "../fallen_balls/main.hpp"
#include "../../include/constants/screens.hpp"
#include "../../include/components/backButton/main.hpp"

// Function to handle input and rendering of the start screen
void handleStartScreen(sf::RenderWindow &window, enum Screen &currentScreen);

// Function to handle input and rendering of the main menu
void handleMainMenu(sf::RenderWindow &window, enum Screen &currentScreen);

// Function to handle input and rendering of the settings screen
void handleSettings(sf::RenderWindow &window, enum Screen &currentScreen);

// Helper function to center text inside a rectangle
void centerTextInRectangle(sf::Text &text, const sf::RectangleShape &rectangle)
{
  sf::FloatRect textRect = text.getLocalBounds();
  text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
  text.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2.0f,
                   rectangle.getPosition().y + rectangle.getSize().y / 2.0f);
}

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
  // Title and back button
  sf::Text title("Simulations", font, 50);
  title.setPosition(300, 50);

  sf::Text backButton("Back to Menu", font, 30);
  backButton.setPosition(300, 500);

  // Simulations setup
  std::vector<sf::RectangleShape> simulations;
  std::vector<sf::Text> simulationTexts;

  std::vector<std::string> simulationLabels = {"Bounce Ball", "Projectile", "Ball & Square", "ElasticCollision", "FallenBalls"};

  sf::Vector2f rectangleSize(100.f, 40.f);
  int columns = 2;
  int spacing = 20;
  int startX = 150;
  int startY = 150;

  for (size_t i = 0; i < simulationLabels.size(); i++)
  {
    sf::RectangleShape simulation(rectangleSize);
    simulation.setFillColor(Gray);

    int x = startX + (i % columns) * (rectangleSize.x + spacing);
    int y = startY + (i / columns) * (rectangleSize.y + spacing);

    simulation.setPosition(x, y);
    simulations.push_back(simulation);

    sf::Text text(simulationLabels[i], font, 20);
    text.setFillColor(sf::Color::White);
    centerTextInRectangle(text, simulation);
    simulationTexts.push_back(text);
  }

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    // Check for mouse clicks
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      sf::Vector2i mousePos = sf::Mouse::getPosition(window);
      if (backButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
      {
        // Change to the start screen
        std::cout << "Back to menu" << std::endl;
        currentScreen = Screen::MainMenu;
        return;
      }
      for (size_t i = 0; i < simulations.size(); i++)
      {
        if (simulations[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
        {
          // Handle the respective simulation action
          std::cout << "pressed: " << i << std::endl;
          currentScreen = static_cast<Screen>(i + 3);
          return;
        }
      }
    }

    window.clear();
    window.draw(title);
    window.draw(backButton);

    for (size_t i = 0; i < simulations.size(); i++)
    {
      window.draw(simulations[i]);
      window.draw(simulationTexts[i]);
    }

    window.display();
  }
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
  sf::RenderWindow window(sf::VideoMode(900, 600), "SFML Application");
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
      case Screen::MainMenu:
        handleMainMenu(window, currentScreen);
        break;
      case Screen::Start:
        handleStartScreen(window, currentScreen);
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
      case Screen::ElasticCollision:
        handleElasticCollision(window, currentScreen);
        break;
      case Screen::FallenBalls:
        handleFallenBalls(window, currentScreen);
        break;
      }
    }

    // Clear the window and render the current screen
    window.clear();
    switch (currentScreen)
    {
    case Screen::MainMenu:
      handleMainMenu(window, currentScreen);
      break;
    case Screen::Start:
      handleStartScreen(window, currentScreen);
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
    case Screen::ElasticCollision:
      handleElasticCollision(window, currentScreen);
      break;
    case Screen::FallenBalls:
      handleFallenBalls(window, currentScreen);
      break;
    }
    window.display();
  }

  return 0;
}
