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

  enum State
  {
    Idle, Moving
  };

  sf::Sprite* getSprite();

  void processInput(const sf::Keyboard::Key &eKey);
  void update(float fDeltaTime);

private:
  void updateStateMachine();
  void updateIdleState();
  void updateMovingState();

  float m_fNoInputTime;
  FacingDirection m_eFacingDirection;
  State m_eState;
  Animation* m_pCurrentAnimation;
  Animation m_cStandingUpAnimation;
  Animation m_cStandingLeftAnimation;
  Animation m_cStandingDownAnimation;
  Animation m_cStandingRightAnimation;
  Animation m_cIdleLeftAnimation;
  Animation m_cIdleDownAnimation;
  Animation m_cIdleRightAnimation;
  Animation m_cWalkUpAnimation;
  Animation m_cWalkLeftAnimation;
  Animation m_cWalkDownAnimation;
  Animation m_cWalkRightAnimation;
  Chrono m_cChrono;
  sf::Sprite m_cSprite;
  sf::Texture m_cSpriteSheetTexture;
  bool m_bStopped;
  bool m_bHadInput;
};

#endif // __LINK_H__