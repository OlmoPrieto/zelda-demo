#ifndef __LINK_H__
#define __LINK_H__

#include <SFML/Graphics.hpp>

#include "animation.h"
#include "chrono.h"
#include "level.h"
#include "vectors.h"

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

  void processInput(/*const sf::Keyboard::Key &eKey*/
    sf::RenderWindow* pWindow);
  void update(float fDeltaTime);
  
  void setLevel(Level* pCurrentLevel);
  void setWindowParameters(sf::RenderWindow* pWindow);

private:
  void updateStateMachine(float fDeltaTime);
  void updateIdleState(float fDeltaTime);
  void updateMovingState(float fDeltaTime);

  float m_fNoInputTime;
  float m_fSpeed;
  uint32 m_uWindowWidth;
  uint32 m_uWindowHeight;
  elm::vector<bool> m_vFacingDirections;
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
  Vector2D m_cVelocity;
  sf::Sprite m_cSprite;
  sf::Texture m_cSpriteSheetTexture;
  Level* m_pCurrentLevel;
  bool m_bStopped;
  bool m_bHadInput;
};

#endif // __LINK_H__
