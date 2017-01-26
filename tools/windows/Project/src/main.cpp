#include <iostream>
#include <SFML/Graphics.hpp>

#include "vector.h"

sf::RenderWindow cWindow;

struct Point
{
  Point() : x(0.0f), y(0.0f) {}
  Point(float x_, float y_) : x(x_), y(y_) {}

  void move(float x_, float y_)
  {
    x += x_;
    y += y_;
  }

  void move(const Point &sPoint)
  {
    x += sPoint.x;
    y += sPoint.y;
  }

  void setPos(float x_, float y_)
  {
    x = x_;
    y = y_;
  }

  void setPos(const sf::Vector2i &sPosition)
  {
    x = (int)sPosition.x;
    y = (int)sPosition.y;
  }

  void setPos(const Point &sPoint)
  {
    x = sPoint.x;
    y = sPoint.y;
  }

  bool operator==(const Point &sOther)
  {
    return (x == sOther.x && y == sOther.y);
  }

  bool operator!= (const Point &sOther)
  {
    return (x != sOther.x && y != sOther.y);
  }

  Point operator-(const Point &sOther)
  {
    Point sAux(x - sOther.x, y - sOther.y);

    return sAux;
  }

  float x;
  float y;
};

class Button
{
public:
  Button(const Point &sPosition, const Point &sSize, const std::string &cLabel)
  {
    m_sPosition = sPosition;
    m_sSize = sSize;
    m_bPressed = false;
    m_bCanBePressedAgain = true;

    if (m_cFont.loadFromFile("../../../Project/resources/arial.ttf") == false)
    {
      printf("Failed to load font\n");
    }
    m_cLabel.setFont(m_cFont);
    m_cLabel.setString(cLabel);
    m_cLabel.setCharacterSize(10);
    m_cLabel.setPosition(sPosition.x + sSize.x * 0.1f, sPosition.y + sSize.y / 4.0f);
    m_cLabel.setColor(sf::Color::Black);

    m_cBox.setSize(sf::Vector2f(sSize.x, sSize.y));
    m_cBox.setPosition(sPosition.x, sPosition.y);
  }

  bool isClicked()
  {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == true)
    {
      m_bPressed = true;

      if (m_bCanBePressedAgain == true) 
      {
        m_bCanBePressedAgain = false;

        Point sMousePos;
        sMousePos.setPos(sf::Mouse::getPosition(cWindow));
        if (sMousePos.x > m_sPosition.x && sMousePos.x < m_sPosition.x + m_sSize.x
          && sMousePos.y > m_sPosition.y && sMousePos.y < m_sPosition.y + m_sSize.y)
        {
          printf("Yay\n");
          return true;
        } else
        {
          return false;
        }
      } else
      {
        //printf("Wuao\n");
      }
    } else
    {
      m_bPressed = false;
      m_bCanBePressedAgain = true;
      //printf("Nay\n");
    }

    /*if (m_bPressed == true)
    {
      Point sMousePos;
      sMousePos.setPos(sf::Mouse::getPosition(cWindow));
      if (sMousePos.x > m_sPosition.x && sMousePos.x < m_sPosition.x + m_sSize.x
        && sMousePos.y > m_sPosition.y && sMousePos.y < m_sPosition.y + m_sSize.y)
      {
        return true;
      } else
      {
        return false;
      }
    }*/

    return false;
  }

  void draw(sf::RenderWindow *cTarget)
  {
    cTarget->draw(m_cBox);
    cTarget->draw(m_cLabel);
  }

  Point m_sPosition;
  Point m_sSize;
  sf::RectangleShape m_cBox;
  sf::Text m_cLabel;
  sf::Font m_cFont;
  bool m_bPressed;
  bool m_bCanBePressedAgain;
};

sf::Image cBackgroundImage;
sf::Texture cBackgroundTexture;
sf::Sprite cBackgroundSprite;
Point sImagePos(0.0f, 0.0f);
Point sImagePosDrag(0.0f, 0.0f);
sf::RectangleShape cToolPanel;
bool bIsMousePressed = false;
bool bIsMouseFirstPosSet = false;
Point sMouseFirstPos(0.0f, 0.0f);
Point sMouseSecondPos(0.0f, 0.0f);
sf::View cView;
float fCurrentZoom = 1.0f;
elm::vector<Button> vButtons;

int main()
{
  cWindow.create(sf::VideoMode(1366, 768), "WINDOW");
  cView.reset(sf::FloatRect(0.0f, 0.0f, 1366.0f, 768.0f));

  cBackgroundImage.loadFromFile("../../../Project/resources/south-hyrule-field_background.png"); 
  cBackgroundTexture.loadFromImage(cBackgroundImage);
  cBackgroundSprite.setTexture(cBackgroundTexture);

  cToolPanel.setSize(sf::Vector2f(366.0f, 768.0f));
  cToolPanel.setFillColor(sf::Color(96, 96, 96, 255));
  cToolPanel.setPosition(1000.0f, 0.0f);

  Button cZoomButton(Point(1050.0f, 675.0f), Point(50.0f, 25.0f), "Zoom");
  vButtons.pushBack(cZoomButton);

  while (cWindow.isOpen())
  {
    // [INPUT]
    sf::Event cEvent;
    while (cWindow.pollEvent(cEvent))
    {
      if (cEvent.type == sf::Event::MouseWheelMoved)
      {
        if (cEvent.mouseWheel.delta > 0)
        {
          fCurrentZoom = 1.0f;
          fCurrentZoom -= 0.01f;
        } else if (cEvent.mouseWheel.delta < 0)
        {
          fCurrentZoom = 1.0f;
          fCurrentZoom += 0.01f;
        }
        cView.zoom(fCurrentZoom);
      }
    }

    sf::Keyboard::Key eKey;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
      eKey = sf::Keyboard::Key::Escape;
      cWindow.close();
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
      if (sf::Mouse::getPosition(cWindow).x < 1000)
      {
        if (bIsMouseFirstPosSet == false)
        {
          sMouseFirstPos.setPos(sf::Mouse::getPosition(cWindow));
          sMouseSecondPos.setPos(sMouseFirstPos);
          bIsMouseFirstPosSet = true;
        }
        if (bIsMousePressed == true)
        {
          sMouseSecondPos.setPos(sf::Mouse::getPosition(cWindow));
          if (sMouseFirstPos != sMouseSecondPos)
          {
            sImagePos.setPos(sImagePosDrag.x + (sMouseSecondPos.x - sMouseFirstPos.x),
              sImagePosDrag.y + (sMouseSecondPos.y - sMouseFirstPos.y));
          }
        }
      }

      bIsMousePressed = true;
    } else
    {
      bIsMousePressed = false;
      bIsMouseFirstPosSet = false;
      sImagePosDrag.setPos(sImagePos);
    }

    for (uint32 i = 0; i < vButtons.size(); i++)
    {
      if (vButtons[i].isClicked() == true)
      {
        /*int j;
        j++;*/
      }
    }
    /*if (cZoomButton.isClicked() == true)
    {
      int i;
      i++;
    }*/
    // [INPUT]


    // [UPDATE]
    cBackgroundSprite.setPosition(sImagePos.x, sImagePos.y);
    //cView.zoom(fCurrentZoom);
    // [UPDATE]


    // [DRAW]
    cWindow.setView(cView);
    cWindow.clear();
    
    cWindow.draw(cBackgroundSprite);

    cWindow.setView(cWindow.getDefaultView());
    //cWindow.clear();
    cWindow.draw(cToolPanel);

    for (uint32 i = 0; i < vButtons.size(); i++)
    {
      vButtons[i].draw(&cWindow);
    }
    cWindow.display();
    // [DRAW]
  }

  return 0;
}