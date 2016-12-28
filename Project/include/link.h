#ifndef __LINK_H__
#define __LINK_H__

#include <SFML/Graphics.hpp>

#include "animation.h"
#include "chrono.h"

class Link
{
public:
  Link();
  ~Link();

  sf::Sprite* getSprite();

  void processInput(const sf::Keyboard::Key &eKey);
  void update(float fDeltaTime);

private:
  float m_fNoInputTime;
  Animation* m_cCurrentAnimation;
  Animation m_cIdleDownAnimation;
  Chrono m_cChrono;
  sf::Sprite m_cSprite;
  sf::Texture m_cLinkUpTexture;
  sf::Texture m_cLinkLeftTexture;
  sf::Texture m_cLinkDownTexture;
  sf::Texture m_cLinkRightTexture;
};

#endif // __LINK_H__