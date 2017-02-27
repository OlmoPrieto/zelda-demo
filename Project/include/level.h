#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <SFML/Graphics.hpp>

#include <string>

#include "utils.h"

typedef unsigned int uint32;
typedef unsigned char byte;

class Level
{
public:
  Level();
  ~Level();

  sf::Sprite* getSprite();
  uint32 getWidth() const;
  uint32 getHeight() const;
  
  void setWindowRef(sf::RenderWindow* pWindow);
  
  byte getTileValue(uint32 uX, uint32 uY) const;
  
  sf::View m_cView;
  sf::Vector2f m_cViewPos;

private:
  bool loadGridFile(const std::string& cFileName);

  uint32 m_uMapWidth;
  uint32 m_uMapHeight;
  uint32 m_uTileSize;
  sf::RenderWindow* m_pWindowRef;
  Utils::Matrix<byte> m_cGridMatrix;
  sf::Texture m_cMapTexture;
  sf::Sprite m_cMapSprite;
};

#endif // __LEVEL_H__
