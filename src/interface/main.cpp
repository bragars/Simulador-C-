#include <SFML/Graphics.hpp>
#include <iostream>

// Variable to track the current screen
enum class Screen
{
  Start,
  MainMenu,
  Settings
};

// Function to handle input and rendering of the start screen
void handleStartScreen(sf::RenderWindow &window, enum Screen &currentScreen);

// Function to handle input and rendering of the main menu
void handleMainMenu(sf::RenderWindow &window, enum Screen &currentScreen);

// Function to handle input and rendering of the settings screen
void handleSettings(sf::RenderWindow &window, enum Screen &currentScreen);

void handleStartScreen(sf::RenderWindow &window, enum Screen &currentScreen)
{
  // Load fonts and create text objects
  static sf::Font font;
  static bool fontLoaded = false;
  if (!fontLoaded)
  {
    if (!font.loadFromFile("../../include/fonts/roboto.ttf"))
    {
      std::cerr << "Error loading font!" << std::endl;
    }
    fontLoaded = true;
  }

  static sf::Text title("Welcome to the Game", font, 50);
  title.setPosition(200, 100);

  static sf::Text startButton("Start", font, 30);
  startButton.setPosition(350, 300);

  // Check for mouse clicks
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
  {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
    {
      // Change to the main menu screen
      currentScreen = Screen::MainMenu;
    }
  }

  // Draw elements
  window.draw(title);
  window.draw(startButton);
}

void handleMainMenu(sf::RenderWindow &window, enum Screen &currentScreen)
{
  static sf::Font font;
  static bool fontLoaded = false;
  if (!fontLoaded)
  {
    if (!font.loadFromFile("../../include/fonts/roboto.ttf"))
    {
      std::cerr << "Error loading font!" << std::endl;
    }
    fontLoaded = true;
  }

  static sf::Text title("Main Menu", font, 50);
  title.setPosition(300, 100);

  static sf::Text settingsButton("Settings", font, 30);
  settingsButton.setPosition(350, 300);

  static sf::Text backButton("Back to Start", font, 30);
  backButton.setPosition(300, 400);

  // Check for mouse clicks
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
  {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (settingsButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
    {
      // Change to the settings screen
      currentScreen = Screen::Settings;
    }
    else if (backButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
    {
      // Change to the start screen
      currentScreen = Screen::Start;
    }
  }

  // Draw elements
  window.draw(title);
  window.draw(settingsButton);
  window.draw(backButton);
}

void handleSettings(sf::RenderWindow &window, enum Screen &currentScreen)
{
  static sf::Font font;
  static bool fontLoaded = false;
  if (!fontLoaded)
  {
    if (!font.loadFromFile("../../include/fonts/roboto.ttf"))
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

  Screen currentScreen = Screen::Start;

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
    }
    window.display();
  }

  return 0;
}
