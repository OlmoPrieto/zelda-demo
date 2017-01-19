#ifndef __LINK_H__
#define __LINK_H__

#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "animation.h"
#include "chrono.h"

class Link
{
public:
  Link();
  ~Link();

  enum FacingDirection
  {
    Up, Left, Down, Right
  };

  sf::Sprite* getSprite();

  void processInput(const sf::Keyboard::Key &eKey);
  void update(float fDeltaTime);

private:
  float m_fNoInputTime;
  FacingDirection m_eFacingDirection;
  Animation* m_pCurrentAnimation;
  Animation m_cStandingUpAnimation;
  Animation m_cStandingLeftAnimation;
  Animation m_cStandingDownAnimation;
  Animation m_cStandingRightAnimation;
  Animation m_cIdleLeftAnimation;
  Animation m_cIdleDownAnimation;
  Animation m_cIdleRightAnimation;
  Animation m_cWalkDownAnimation;
  Chrono m_cChrono;
  sf::Sprite m_cSprite;
  sf::Texture m_cSpriteSheetTexture;
  bool m_bStopped;
};

#endif // __LINK_H__