#include <iostream>

#include <SFML/Graphics.hpp>

#include "link.h"

int main()
{
  sf::RenderWindow cWindow(sf::VideoMode(800, 600), "Window");

  Link cLink;

  while (cWindow.isOpen())
  {
    sf::Event e;
    if (cWindow.pollEvent(e))
    {
      if (e.type == sf::Event::Closed)
      {
        cWindow.close();
      }
    }
    // [INPUT]
    sf::Keyboard::Key eKey = sf::Keyboard::Key::Unknown;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
      cWindow.close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
      eKey = sf::Keyboard::Key::Up;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
      eKey = sf::Keyboard::Key::Left;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
      eKey = sf::Keyboard::Key::Down;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
      eKey = sf::Keyboard::Key::Right;
    }

    cLink.processInput(eKey);
    // [INPUT]

    // [UPDATE]
    cLink.update(0.16f);
    // [UPDATE]

    // [DRAW]
    cWindow.clear(sf::Color(64, 64, 64, 255));
    //
    cWindow.draw(*cLink.getSprite());
    //
    cWindow.display();
    // [DRAW]
  }

  return 0;
}