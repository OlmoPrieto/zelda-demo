#ifndef __MISC_H__
#define __MISC_H__

#include <iostream>

#include <SFML/Graphics.hpp>

#include "chrono.h"

typedef unsigned int uint32;
typedef unsigned char byte;

static inline uint32 lerp(uint32 uA, uint32 uB, float fAlpha)
{
  return (uA + fAlpha * (uB - uA));
}

template <class T> 
static inline T lerp(const T& cA, const T& cB, float fAlpha)
{
  return (cA + fAlpha * (cB - cA));
}

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

  void operator*=(float fValue)
  {
    x *= fValue;
    y *= fValue;
  }

  Point operator*(float fValue)
  {
    return Point(x * fValue, y * fValue);
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

  bool isClicked(sf::RenderWindow *pTarget)
  {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == true)
    {
      m_bPressed = true;

      if (m_bCanBePressedAgain == true)
      {
        m_bCanBePressedAgain = false;

        Point sMousePos;
        sMousePos.setPos(sf::Mouse::getPosition(*pTarget));
        if (sMousePos.x > m_sPosition.x && sMousePos.x < m_sPosition.x + m_sSize.x
          && sMousePos.y > m_sPosition.y && sMousePos.y < m_sPosition.y + m_sSize.y)
        {
          return true;
        } else
        {
          return false;
        }
      }
    } else
    {
      m_bPressed = false;
      m_bCanBePressedAgain = true;
    }

    return false;
  }

  void draw(sf::RenderWindow *pTarget)
  {
    pTarget->draw(m_cBox);
    pTarget->draw(m_cLabel);
  }

  Point m_sPosition;
  Point m_sSize;
  sf::RectangleShape m_cBox;
  sf::Text m_cLabel;
  sf::Font m_cFont;
  bool m_bPressed;
  bool m_bCanBePressedAgain;
};


class TextInput
{
public:
  TextInput(const sf::FloatRect &sDimensions, uint32 uStringMaxLenght)
  {
    m_cString = "";
    m_fBlinkTime = 0.5f;
    //m_fBlinkTime = 1000.0f;
    m_fInputTime = 0.15f;
    m_fNoInputAccTime = 0.0f;
    m_fBlinkAccTime = 0.0f;
    m_fCursorYOffset = sDimensions.top + sDimensions.height * 0.05f;
    m_uCursorIndex = 0;
    m_uStringMaxLenght = uStringMaxLenght;
    m_byAlphaLerp = 255;
    m_bHasFocus = false;
    m_bBlinkDown = true;

    if (m_cFont.loadFromFile("../../../Project/resources/arial.ttf") == false)
    {
      printf("Failed to load font\n");
    }
    m_cText.setFont(m_cFont);
    m_cText.setCharacterSize(uint32(sDimensions.height) /*25*/);
    m_cText.setColor(sf::Color::Black);
    m_cText.setPosition(sDimensions.left + sDimensions.width * 0.05f,
      sDimensions.top - sDimensions.height * 0.15f);

    m_cDimensions = sDimensions;

    m_cTextBox.setSize(sf::Vector2f(sDimensions.width, sDimensions.height));
    m_cTextBox.setPosition(sDimensions.left, sDimensions.top);
    m_cTextBox.setFillColor(sf::Color::White);

    m_cCursor.setSize(sf::Vector2f(1.0f, sDimensions.height - sDimensions.height * 0.1f));
    m_cCursor.setFillColor(sf::Color::Black);
    //m_cCursor.setPosition(sDimensions.left + sDimensions.width * 0.025f, 
    //  sDimensions.top + sDimensions.height * 0.075f);
    sf::Vector2f cCharacterPosition(m_cText.findCharacterPos(0).x, m_fCursorYOffset);
    m_cCursor.setPosition(cCharacterPosition);

    m_cBlinkChrono.start();
    m_cInputChrono.start();
  }

  std::string& getString()
  {
    return m_cString;
  }

  void setString(const std::string &cString)
  {
    m_cString = cString;
    
    m_cText.setString(cString);
    m_uCursorIndex = cString.size();
    m_cCursor.setPosition(m_cText.findCharacterPos(m_uCursorIndex).x, m_fCursorYOffset);
  }

  bool isClicked(sf::RenderWindow *pTarget)
  {
    bool bIsClicked = false;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == true)
    {
      Point sMousePos;
      sMousePos.setPos(sf::Mouse::getPosition(*pTarget));

      if (sMousePos.x > m_cDimensions.left && sMousePos.x < m_cDimensions.left + m_cDimensions.width
        && sMousePos.y > m_cDimensions.top && sMousePos.y < m_cDimensions.top + m_cDimensions.height)
      {
        m_bHasFocus = true;

        bIsClicked = true;
      } else
      {
        m_bHasFocus = false;
      }
    }

    return bIsClicked;
  }

  /*  This method sometimes fails because the accumulated time keep increasing 
   *  and when you really want to check if you have been m_fInputTime without input 
   *  the counter has been reset.
  */
  //void processInput(sf::RenderWindow *pTarget)
  //{
  //  sf::Keyboard::Key eKeyPressed = sf::Keyboard::Key::Unknown;

  //  if (m_bHasFocus == true)
  //  {
  //    m_cInputChrono.stop();
  //    m_fNoInputAccTime += m_cInputChrono.timeAsSeconds();
  //    printf("%.2f\n", m_fNoInputAccTime);
  //    m_cInputChrono.start();

  //    /*m_cInputChrono.stop();
  //    static float sfCurrentTime = m_fNoInputAccTime;
  //    m_fNoInputAccTime += m_cInputChrono.timeAsSeconds() - sfCurrentTime;
  //    m_cInputChrono.start();*/

  //    if (m_fNoInputAccTime >= m_fInputTime)
  //    {
  //      m_fNoInputAccTime = 0.0f;
  //      
  //      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
  //      {
  //        if (m_uCursorIndex > 0)
  //        {
  //          m_uCursorIndex--;
  //        }
  //      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
  //      {
  //        //if (m_uCursorIndex < m_cString.size())
  //        //{
  //          m_uCursorIndex++;
  //        //}
  //      }

  //      // Update cursor
  //      m_cCursor.setPosition(m_cText.findCharacterPos(m_uCursorIndex));
  //    }
  //  }
  //}

  void processInput(sf::RenderWindow *pTarget)
  {
    sf::Keyboard::Key eKeyPressed = sf::Keyboard::Key::Unknown;
    bool bShiftPressed = false;

    if (m_bHasFocus == true)
    {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
      {
        eKeyPressed = sf::Keyboard::Key::Left;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
      {
        eKeyPressed = sf::Keyboard::Key::Right;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
      {
        eKeyPressed = sf::Keyboard::Key::BackSpace;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
      {
        eKeyPressed = sf::Keyboard::Key::A;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B))
      {
        eKeyPressed = sf::Keyboard::Key::B;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
      {
        eKeyPressed = sf::Keyboard::Key::C;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
      {
        eKeyPressed = sf::Keyboard::Key::D;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
      {
        eKeyPressed = sf::Keyboard::Key::E;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))
      {
        eKeyPressed = sf::Keyboard::Key::F;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G))
      {
        eKeyPressed = sf::Keyboard::Key::G;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H))
      {
        eKeyPressed = sf::Keyboard::Key::H;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I))
      {
        eKeyPressed = sf::Keyboard::Key::I;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J))
      {
        eKeyPressed = sf::Keyboard::Key::J;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
      {
        eKeyPressed = sf::Keyboard::Key::K;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
      {
        eKeyPressed = sf::Keyboard::Key::L;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M))
      {
        eKeyPressed = sf::Keyboard::Key::M;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N))
      {
        eKeyPressed = sf::Keyboard::Key::N;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O))
      {
        eKeyPressed = sf::Keyboard::Key::O;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
      {
        eKeyPressed = sf::Keyboard::Key::P;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
      {
        eKeyPressed = sf::Keyboard::Key::Q;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
      {
        eKeyPressed = sf::Keyboard::Key::R;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
      {
        eKeyPressed = sf::Keyboard::Key::S;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T))
      {
        eKeyPressed = sf::Keyboard::Key::T;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U))
      {
        eKeyPressed = sf::Keyboard::Key::U;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V))
      {
        eKeyPressed = sf::Keyboard::Key::V;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
      {
        eKeyPressed = sf::Keyboard::Key::W;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
      {
        eKeyPressed = sf::Keyboard::Key::X;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y))
      {
        eKeyPressed = sf::Keyboard::Key::Y;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
      {
        eKeyPressed = sf::Keyboard::Key::Z;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num0))
      {
        eKeyPressed = sf::Keyboard::Key::Num0;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
      {
        eKeyPressed = sf::Keyboard::Key::Num1;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
      {
        eKeyPressed = sf::Keyboard::Key::Num2;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
      {
        eKeyPressed = sf::Keyboard::Key::Num3;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))
      {
        eKeyPressed = sf::Keyboard::Key::Num4;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5))
      {
        eKeyPressed = sf::Keyboard::Key::Num5;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6))
      {
        eKeyPressed = sf::Keyboard::Key::Num6;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num7))
      {
        eKeyPressed = sf::Keyboard::Key::Num7;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num8))
      {
        eKeyPressed = sf::Keyboard::Key::Num8;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num9))
      {
        eKeyPressed = sf::Keyboard::Key::Num9;
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
      {
        bShiftPressed = true;
      }

      // --
      if (eKeyPressed != sf::Keyboard::Key::Unknown)
      {
        m_cInputChrono.stop();
        m_fNoInputAccTime += m_cInputChrono.timeAsSeconds();
        m_cInputChrono.start();

        /*m_cInputChrono.stop();
        static float sfCurrentTime = m_fNoInputAccTime;
        m_fNoInputAccTime += m_cInputChrono.timeAsSeconds() - sfCurrentTime;
        m_cInputChrono.start();*/

        if (m_fNoInputAccTime >= m_fInputTime)
        {
          m_fNoInputAccTime = 0.0f;

          if (eKeyPressed == sf::Keyboard::Key::Left)
          {
            if (m_uCursorIndex > 0)
            {
              m_uCursorIndex--;
            }
          } else if (eKeyPressed == sf::Keyboard::Key::Right)
          {
            if (m_uCursorIndex < m_cString.size())
            {
              m_uCursorIndex++;
            }
          } else if (eKeyPressed == sf::Keyboard::BackSpace)
          {
            if (m_uCursorIndex > 0)
            {
              m_cString.erase(m_cString.begin() + m_uCursorIndex - 1);
              m_cText.setString(m_cString);
              m_uCursorIndex--;
            }
          } else if (eKeyPressed >= sf::Keyboard::Key::A && eKeyPressed <= sf::Keyboard::Key::Num9)
          {
            char cWord = 'a';
            switch (eKeyPressed)
            {
            case sf::Keyboard::Key::A: cWord = 'a'; break;
            case sf::Keyboard::Key::B: cWord = 'b'; break;
            case sf::Keyboard::Key::C: cWord = 'c'; break;
            case sf::Keyboard::Key::D: cWord = 'd'; break;
            case sf::Keyboard::Key::E: cWord = 'e'; break;
            case sf::Keyboard::Key::F: cWord = 'f'; break;
            case sf::Keyboard::Key::G: cWord = 'g'; break;
            case sf::Keyboard::Key::H: cWord = 'h'; break;
            case sf::Keyboard::Key::I: cWord = 'i'; break;
            case sf::Keyboard::Key::J: cWord = 'j'; break;
            case sf::Keyboard::Key::K: cWord = 'k'; break;
            case sf::Keyboard::Key::L: cWord = 'l'; break;
            case sf::Keyboard::Key::M: cWord = 'm'; break;
            case sf::Keyboard::Key::N: cWord = 'n'; break;
            case sf::Keyboard::Key::O: cWord = 'o'; break;
            case sf::Keyboard::Key::P: cWord = 'p'; break;
            case sf::Keyboard::Key::Q: cWord = 'q'; break;
            case sf::Keyboard::Key::R: cWord = 'r'; break;
            case sf::Keyboard::Key::S: cWord = 's'; break;
            case sf::Keyboard::Key::T: cWord = 't'; break;
            case sf::Keyboard::Key::U: cWord = 'u'; break;
            case sf::Keyboard::Key::V: cWord = 'v'; break;
            case sf::Keyboard::Key::W: cWord = 'w'; break;
            case sf::Keyboard::Key::X: cWord = 'x'; break;
            case sf::Keyboard::Key::Y: cWord = 'y'; break;
            case sf::Keyboard::Key::Z: cWord = 'z'; break;
            case sf::Keyboard::Key::Num0: cWord = '0'; break;
            case sf::Keyboard::Key::Num1: cWord = '1'; break;
            case sf::Keyboard::Key::Num2: cWord = '2'; break;
            case sf::Keyboard::Key::Num3: cWord = '3'; break;
            case sf::Keyboard::Key::Num4: cWord = '4'; break;
            case sf::Keyboard::Key::Num5: cWord = '5'; break;
            case sf::Keyboard::Key::Num6: cWord = '6'; break;
            case sf::Keyboard::Key::Num7: cWord = '7'; break;
            case sf::Keyboard::Key::Num8: cWord = '8'; break;
            case sf::Keyboard::Key::Num9: cWord = '9'; break;
            }

            if (bShiftPressed == true)
            {
              cWord -= 32;
            }

            if (m_cString.size() < m_uStringMaxLenght)
            {
              m_cString.insert(m_uCursorIndex, 1, cWord);
              m_cText.setString(m_cString);
              m_uCursorIndex++;
            }
          }

          // Update cursor
          m_cCursor.setPosition(m_cText.findCharacterPos(m_uCursorIndex).x, m_fCursorYOffset);
        }
      }
    }
  }

  void draw(sf::RenderWindow *pTarget)
  {
    if (m_bHasFocus == true)
    {
      m_cBlinkChrono.stop();
      m_fBlinkAccTime += m_cBlinkChrono.timeAsSeconds();
      m_cBlinkChrono.start();
    
      if (m_fBlinkAccTime >= m_fBlinkTime)
      {
        m_fBlinkAccTime = 0.0f;
        if (m_bBlinkDown == true)
        {
          m_bBlinkDown = false;
        } else
        {
          m_bBlinkDown = true;
        }
      }

      if (m_bBlinkDown == false)
      {
        m_byAlphaLerp = lerp<byte>(0, 255, m_fBlinkAccTime / m_fBlinkTime);
      } else
      {
        m_byAlphaLerp = lerp<byte>(255, 0, m_fBlinkAccTime / m_fBlinkTime);
      }
    
      sf::Color cColor = m_cCursor.getFillColor();
      cColor.a = m_byAlphaLerp;
      m_cCursor.setFillColor(cColor);
    } else
    {
      m_cCursor.setFillColor(sf::Color::Black);
    }

    pTarget->draw(m_cTextBox);
    pTarget->draw(m_cText);
    pTarget->draw(m_cCursor);
  }

  sf::RectangleShape m_cTextBox;
  sf::Font m_cFont;
  sf::Text m_cText;
  sf::RectangleShape m_cCursor;
  sf::FloatRect m_cDimensions;
  std::string m_cString;
  Chrono m_cBlinkChrono;
  Chrono m_cInputChrono;
  float m_fBlinkTime;
  float m_fInputTime;
  float m_fNoInputAccTime;
  float m_fBlinkAccTime;
  float m_fCursorYOffset;
  uint32 m_uCursorIndex;
  uint32 m_uStringMaxLenght;
  byte m_byAlphaLerp;
  bool m_bHasFocus;
  bool m_bBlinkDown;
};

#endif // __MISC_H__