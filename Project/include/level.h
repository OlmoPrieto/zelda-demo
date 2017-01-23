#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <SFML/Graphics.hpp>

typedef unsigned int uint32;

//struct Point
//{
//  Point(float x_, float y_) : x(x_), y(y_) {}
//  float x;
//  float y;
//};

class Level
{
public:
  Level();
  ~Level();

  sf::Sprite* getSprite();
  uint32 getWidth() const;
  uint32 getHeight() const;

private:
  uint32 m_uMapWidth;
  uint32 m_uMapHeight;
  sf::Texture m_cMapTexture;
  sf::Sprite m_cMapSprite;
};

#endif // __LEVEL_H__