#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "link.h"
#include "level.h"

struct Point
{
  Point(float x_, float y_) : x(x_), y(y_) {}

  void move(float x_, float y_)
  {
    x += x_;
    y += y_;
  }

  float x;
  float y;
};

int main()
{
  sf::RenderWindow cWindow(sf::VideoMode(800, 600), "Window");

  Link cLink;
  Level cLevel;

  Point sViewPos(0.0f, 0.0f);
  sf::View cView;
  cView.reset(sf::FloatRect(0.0f, 0.0f, 800.0f, 600.0f));
  //cView.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
  cWindow.setView(cView);

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
    /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
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
    }*/
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
      if (sViewPos.x + cView.getSize().x < cLevel.getWidth())
      {
        cView.move(0.01f, 0.0f);
        sViewPos.move(0.01f, 0.0f);
        cWindow.setView(cView);
      }
    }

    cLink.processInput(&cWindow);
    // [INPUT]

    // [UPDATE]
    cLink.update(0.016f);
    // [UPDATE]

    // [DRAW]
    cWindow.clear(sf::Color(64, 64, 64, 255));
    //
    cWindow.draw(*cLevel.getSprite());
    cWindow.draw(*cLink.getSprite());
    //
    cWindow.display();
    // [DRAW]
  }

  return 0;
}