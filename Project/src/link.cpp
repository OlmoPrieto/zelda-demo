#include "link.h"

#include "utils.h"

#include <cstdio>


Link::Link() : m_cStandingUpAnimation(&m_cSprite, 0.15f, false),
  m_cStandingLeftAnimation(&m_cSprite, 0.15f, false),
  m_cStandingDownAnimation(&m_cSprite, 0.15f, false),
  m_cStandingRightAnimation(&m_cSprite, 0.15f, false),
  m_cIdleDownAnimation(&m_cSprite, 0.15f, false),
  m_cIdleLeftAnimation(&m_cSprite, 0.15f, false),
  m_cIdleRightAnimation(&m_cSprite, 0.15f, false),
  m_cWalkUpAnimation(&m_cSprite, 0.07f, true),
  m_cWalkLeftAnimation(&m_cSprite, 0.07f, true),
  m_cWalkDownAnimation(&m_cSprite, 0.07f, true),
  m_cWalkRightAnimation(&m_cSprite, 0.07f, true)
{
  m_fNoInputTime = 0.0f;
  m_fSpeed = 0.8f;  // pixels/s ??
  m_vFacingDirections.reserve(4);
  m_vFacingDirections.pushBack(false);  // facing up
  m_vFacingDirections.pushBack(false);  // facing left
  m_vFacingDirections.pushBack(true);  // facing down
  m_vFacingDirections.pushBack(false);  // facing right
  m_eFacingDirection = FacingDirection::Down;
  m_eState = State::Idle;
  m_pCurrentAnimation = nullptr;
  m_bStopped = true;
  m_bHadInput = false;
  m_cChrono.start();

  sf::Image cLinkSheet;
  bool opened = cLinkSheet.loadFromFile("resources/link_sheet.png");

  m_cSpriteSheetTexture.loadFromImage(cLinkSheet);
  sf::IntRect cTextureRect;

  // Standing Up
  cTextureRect.left = 79;
  cTextureRect.top = 10;
  cTextureRect.width = 18;
  cTextureRect.height = 23;
  m_cStandingUpAnimation.addFrame(cTextureRect);

  // Standing Left
  cTextureRect.left = 51;
  cTextureRect.top = 10;
  cTextureRect.width = 18;
  cTextureRect.height = 23;
  m_cStandingLeftAnimation.addFrame(cTextureRect);

  // Standing Down
  cTextureRect.left = 15;
  cTextureRect.top = 9;
  cTextureRect.width = 18;
  cTextureRect.height = 23;
  m_cStandingDownAnimation.addFrame(cTextureRect);

  // Standing Right
  cTextureRect.left = 110;
  cTextureRect.top = 10;
  cTextureRect.width = 18;
  cTextureRect.height = 23;
  m_cStandingRightAnimation.addFrame(cTextureRect);

  // Idle Down
  cTextureRect.left = 15;
  cTextureRect.top = 9;
  cTextureRect.width = 18;
  cTextureRect.height = 23;
  m_cIdleDownAnimation.addFrame(cTextureRect);

  cTextureRect.left = 15;
  cTextureRect.top = 45;
  cTextureRect.width = 18;
  cTextureRect.height = 23;
  m_cIdleDownAnimation.addFrame(cTextureRect);

  cTextureRect.left = 43;
  cTextureRect.top = 45;
  cTextureRect.width = 18;
  cTextureRect.height = 23;
  m_cIdleDownAnimation.addFrame(cTextureRect);
  // -- 

  // Idle Left
  cTextureRect.left = 51;
  cTextureRect.top = 10;
  cTextureRect.width = 18;
  cTextureRect.height = 23;
  m_cIdleLeftAnimation.addFrame(cTextureRect);

  cTextureRect.left = 79;
  cTextureRect.top = 46;
  cTextureRect.width = 18;
  cTextureRect.height = 23;
  m_cIdleLeftAnimation.addFrame(cTextureRect);

  cTextureRect.left = 103;
  cTextureRect.top = 46;
  cTextureRect.width = 18;
  cTextureRect.height = 23;
  m_cIdleLeftAnimation.addFrame(cTextureRect);
  // --

  // Idle Right
  cTextureRect.left = 110;
  cTextureRect.top = 10;
  cTextureRect.width = 18;
  cTextureRect.height = 23;
  m_cIdleRightAnimation.addFrame(cTextureRect);

  cTextureRect.left = 143;
  cTextureRect.top = 46;
  cTextureRect.width = 18;
  cTextureRect.height = 23;
  m_cIdleRightAnimation.addFrame(cTextureRect);

  cTextureRect.left = 167;
  cTextureRect.top = 46;
  cTextureRect.width = 18;
  cTextureRect.height = 23;
  m_cIdleRightAnimation.addFrame(cTextureRect);
  // --

  // Walk Up
  cTextureRect.left = 79;
  cTextureRect.top = 10;
  cTextureRect.width = 18;
  cTextureRect.height = 23;
  m_cWalkUpAnimation.addFrame(cTextureRect);

  cTextureRect.left = 683;
  cTextureRect.top = 78;
  cTextureRect.width = 18;
  cTextureRect.height = 22;
  m_cWalkUpAnimation.addFrame(cTextureRect);

  cTextureRect.left = 715;
  cTextureRect.top = 78;
  cTextureRect.width = 18;
  cTextureRect.height = 22;
  m_cWalkUpAnimation.addFrame(cTextureRect);

  cTextureRect.left = 747;
  cTextureRect.top = 76;
  cTextureRect.width = 18;
  cTextureRect.height = 24;
  m_cWalkUpAnimation.addFrame(cTextureRect);

  cTextureRect.left = 779;
  cTextureRect.top = 76;
  cTextureRect.width = 18;
  cTextureRect.height = 25;
  m_cWalkUpAnimation.addFrame(cTextureRect);

  cTextureRect.left = 811;
  cTextureRect.top = 76;
  cTextureRect.width = 18;
  cTextureRect.height = 24;
  m_cWalkUpAnimation.addFrame(cTextureRect);

  cTextureRect.left = 843;
  cTextureRect.top = 78;
  cTextureRect.width = 18;
  cTextureRect.height = 22;
  m_cWalkUpAnimation.addFrame(cTextureRect);

  cTextureRect.left = 875;
  cTextureRect.top = 78;
  cTextureRect.width = 18;
  cTextureRect.height = 22;
  m_cWalkUpAnimation.addFrame(cTextureRect);

  cTextureRect.left = 907;
  cTextureRect.top = 76;
  cTextureRect.width = 18;
  cTextureRect.height = 24;
  m_cWalkUpAnimation.addFrame(cTextureRect);

  cTextureRect.left = 939;
  cTextureRect.top = 77;
  cTextureRect.width = 18;
  cTextureRect.height = 25;
  m_cWalkUpAnimation.addFrame(cTextureRect);

  cTextureRect.left = 971;
  cTextureRect.top = 76;
  cTextureRect.width = 18;
  cTextureRect.height = 24;
  m_cWalkUpAnimation.addFrame(cTextureRect);
  // -- 

  // Walk Left
  //cTextureRect.left = 51;   // 0
  //cTextureRect.top = 10;
  //cTextureRect.width = 18;
  //cTextureRect.height = 23;
  //m_cWalkLeftAnimation.addFrame(cTextureRect);

  cTextureRect.left = 476;  // 5
  cTextureRect.top = 77;
  cTextureRect.width = 20;
  cTextureRect.height = 22;
  m_cWalkLeftAnimation.addFrame(cTextureRect);

  cTextureRect.left = 445;  // 4
  cTextureRect.top = 77;
  cTextureRect.width = 20;
  cTextureRect.height = 22;
  m_cWalkLeftAnimation.addFrame(cTextureRect);

  cTextureRect.left = 412;  // 3
  cTextureRect.top = 77;
  cTextureRect.width = 20;
  cTextureRect.height = 21;
  m_cWalkLeftAnimation.addFrame(cTextureRect);

  cTextureRect.left = 380;  // 2
  cTextureRect.top = 78;
  cTextureRect.width = 20;
  cTextureRect.height = 21;
  m_cWalkLeftAnimation.addFrame(cTextureRect);

  cTextureRect.left = 350;  // 1
  cTextureRect.top = 78;
  cTextureRect.width = 23;
  cTextureRect.height = 22;
  m_cWalkLeftAnimation.addFrame(cTextureRect);

  cTextureRect.left = 510;
  cTextureRect.top = 78;
  cTextureRect.width = 23;
  cTextureRect.height = 22;
  m_cWalkLeftAnimation.addFrame(cTextureRect);

  cTextureRect.left = 540;
  cTextureRect.top = 78;
  cTextureRect.width = 19;
  cTextureRect.height = 22;
  m_cWalkLeftAnimation.addFrame(cTextureRect);

  cTextureRect.left = 573;
  cTextureRect.top = 77;
  cTextureRect.width = 19;
  cTextureRect.height = 22;
  m_cWalkLeftAnimation.addFrame(cTextureRect);

  cTextureRect.left = 609;
  cTextureRect.top = 77;
  cTextureRect.width = 19;
  cTextureRect.height = 22;
  m_cWalkLeftAnimation.addFrame(cTextureRect);

  cTextureRect.left = 636;
  cTextureRect.top = 77;
  cTextureRect.width = 20;
  cTextureRect.height = 22;
  m_cWalkLeftAnimation.addFrame(cTextureRect);
  // --

  // Walk Down
  cTextureRect.left = 15;
  cTextureRect.top = 9;
  cTextureRect.width = 18;
  cTextureRect.height = 23;
  m_cWalkDownAnimation.addFrame(cTextureRect);

  cTextureRect.left = 15;
  cTextureRect.top = 77;
  cTextureRect.width = 18;
  cTextureRect.height = 23;
  m_cWalkDownAnimation.addFrame(cTextureRect);

  cTextureRect.left = 47;
  cTextureRect.top = 76;
  cTextureRect.width = 18;
  cTextureRect.height = 23;
  m_cWalkDownAnimation.addFrame(cTextureRect);

  cTextureRect.left = 79;
  cTextureRect.top = 76;
  cTextureRect.width = 18;
  cTextureRect.height = 24;
  m_cWalkDownAnimation.addFrame(cTextureRect);

  cTextureRect.left = 111;
  cTextureRect.top = 76;
  cTextureRect.width = 18;
  cTextureRect.height = 24;
  m_cWalkDownAnimation.addFrame(cTextureRect);

  cTextureRect.left = 143;
  cTextureRect.top = 76;
  cTextureRect.width = 18;
  cTextureRect.height = 24;
  m_cWalkDownAnimation.addFrame(cTextureRect);

  cTextureRect.left = 175;
  cTextureRect.top = 77;
  cTextureRect.width = 18;
  cTextureRect.height = 23;
  m_cWalkDownAnimation.addFrame(cTextureRect);

  cTextureRect.left = 207;
  cTextureRect.top = 76;
  cTextureRect.width = 18;
  cTextureRect.height = 23;
  m_cWalkDownAnimation.addFrame(cTextureRect);

  cTextureRect.left = 239;
  cTextureRect.top = 76;
  cTextureRect.width = 18;
  cTextureRect.height = 24;
  m_cWalkDownAnimation.addFrame(cTextureRect);

  cTextureRect.left = 271;
  cTextureRect.top = 76;
  cTextureRect.width = 18;
  cTextureRect.height = 24;
  m_cWalkDownAnimation.addFrame(cTextureRect);

  cTextureRect.left = 303;
  cTextureRect.top = 76;
  cTextureRect.width = 18;
  cTextureRect.height = 24;
  m_cWalkDownAnimation.addFrame(cTextureRect);
  // -- 

  // Walk Right
  //cTextureRect.left = 110;  // 0
  //cTextureRect.top = 10;
  //cTextureRect.width = 18;
  //cTextureRect.height = 23;
  //m_cWalkRightAnimation.addFrame(cTextureRect);

  cTextureRect.left = 999;  // 5
  cTextureRect.top = 44;
  cTextureRect.width = 23;
  cTextureRect.height = 22;
  m_cWalkRightAnimation.addFrame(cTextureRect);

  cTextureRect.left = 973;  // 4
  cTextureRect.top = 44;
  cTextureRect.width = 19;
  cTextureRect.height = 22;
  m_cWalkRightAnimation.addFrame(cTextureRect);

  cTextureRect.left = 940;  // 3
  cTextureRect.top = 43;
  cTextureRect.width = 19;
  cTextureRect.height = 22;
  m_cWalkRightAnimation.addFrame(cTextureRect);

  cTextureRect.left = 904;  // 2
  cTextureRect.top = 43;
  cTextureRect.width = 19;
  cTextureRect.height = 22;
  m_cWalkRightAnimation.addFrame(cTextureRect);

  cTextureRect.left = 876;  // 1
  cTextureRect.top = 43;
  cTextureRect.width = 20;
  cTextureRect.height = 22;
  m_cWalkRightAnimation.addFrame(cTextureRect);

  cTextureRect.left = 1036;
  cTextureRect.top = 43;
  cTextureRect.width = 20;
  cTextureRect.height = 22;
  m_cWalkRightAnimation.addFrame(cTextureRect);

  cTextureRect.left = 1067;
  cTextureRect.top = 43;
  cTextureRect.width = 20;
  cTextureRect.height = 22;
  m_cWalkRightAnimation.addFrame(cTextureRect);

  cTextureRect.left = 1100;
  cTextureRect.top = 43;
  cTextureRect.width = 20;
  cTextureRect.height = 21;
  m_cWalkRightAnimation.addFrame(cTextureRect);

  cTextureRect.left = 1132;
  cTextureRect.top = 44;
  cTextureRect.width = 20;
  cTextureRect.height = 21;
  m_cWalkRightAnimation.addFrame(cTextureRect);

  cTextureRect.left = 1159;
  cTextureRect.top = 44;
  cTextureRect.width = 23;
  cTextureRect.height = 22;
  m_cWalkRightAnimation.addFrame(cTextureRect);
  // -- 

  m_pCurrentAnimation = &m_cStandingDownAnimation;
  //m_cSprite.setTextureRect(*m_cCurrentAnimation->getCurrentFrame());
  m_cSprite.setTexture(m_cSpriteSheetTexture);
  m_pCurrentAnimation->play();
  //

  //m_cSprite.setTexture(m_cLinkDownTexture);
  m_cSprite.setPosition(100.0f, 85.0f);
  //m_cSprite.setScale(10.0f, 10.0f);
}

Link::~Link()
{
  
}

sf::Sprite* Link::getSprite()
{
  return &m_cSprite;
}

void Link::processInput(/*const sf::Keyboard::Key &eKey*/sf::RenderWindow* pWindow)
{
  m_bHadInput = true;
  m_bStopped = false;

  sf::Keyboard::Key eKey = sf::Keyboard::Key::Unknown;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
  {
    eKey = sf::Keyboard::Key::Up;
    m_vFacingDirections[0] = true;
  } else
  {
    m_vFacingDirections[0] = false;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
  {
    eKey = sf::Keyboard::Key::Left;
    m_vFacingDirections[1] = true;
  } else
  {
    m_vFacingDirections[1] = false;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
  {
    eKey = sf::Keyboard::Key::Down;
    m_vFacingDirections[2] = true;
  } else
  {
    m_vFacingDirections[2] = false;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
  {
    eKey = sf::Keyboard::Key::Right;
    m_vFacingDirections[3] = true;
  } else
  {
    m_vFacingDirections[3] = false;
  }

  if (eKey == sf::Keyboard::Key::Unknown)
  {
    m_bHadInput = false;
    m_bStopped = true;
  }

  //if (eKey == sf::Keyboard::Key::Up)
  //{
  //  m_eFacingDirection = Up;
  //  m_vFacingDirections[0] = true;
  //}/* else
  //{
  //  m_vFacingDirections[0] = false;
  //}*/
  //if (eKey == sf::Keyboard::Key::Left)
  //{
  //  m_eFacingDirection = Left;
  //  m_vFacingDirections[1] = true;
  //}/* else
  //{
  //  m_vFacingDirections[1] = false;
  //}*/
  //if (eKey == sf::Keyboard::Key::Down)
  //{
  //  m_eFacingDirection = Down;
  //  m_vFacingDirections[2] = true;
  //}/* else
  //{
  //  m_vFacingDirections[2] = false;
  //}*/
  //if (eKey == sf::Keyboard::Key::Right)
  //{
  //  m_eFacingDirection = Right;
  //  m_vFacingDirections[3] = true;
  //}/* else
  //{
  //  m_vFacingDirections[3] = false;
  //}*/
  //if (eKey == sf::Keyboard::Key::Unknown)
  //{
  //  m_bHadInput = false;
  //  m_bStopped = true;
  //}

  if (m_bHadInput == false)
  {
    m_cChrono.stop();
    static float sfCurrentTime = m_fNoInputTime;
    m_fNoInputTime += m_cChrono.timeAsSeconds() - sfCurrentTime;
    m_cChrono.start();

    /*m_cVelocity.x = 0.0f;
    m_cVelocity.y = 0.0f;*/
  } else // if it was useful input, reset the chrono
  {
    m_cChrono.start();
    m_fNoInputTime = 0.0;

    m_cVelocity.x = 0.0f;
    m_cVelocity.y = 0.0f;
  }
}

void Link::updateStateMachine(float fDeltaTime)
{
  switch (m_eState)
  {
  case Idle:
  {
    if (m_bHadInput == true)
    {
      m_eState = Moving;
    } else
    {
      updateIdleState(fDeltaTime);
    }
  }
  case Moving:
  {
    if (m_bHadInput == false)
    {
      m_eState = Idle;
    } else
    {
      updateMovingState(fDeltaTime);
    }
  }
  }
}

void Link::updateIdleState(float fDeltaTime)
{
  bool bPlayIdleAnimation = false;
  bool bChangedAnimation = false;
  Animation* pLastAnimation = nullptr;

  if (m_fNoInputTime >= 2.5f)
  {
    m_fNoInputTime = 0.0f;
    bPlayIdleAnimation = true;
  }

  switch (m_eFacingDirection)
  {
  case Up:
  {
    /*if (bPlayIdleAnimation == true)
    {
      pLastAnimation = m_pCurrentAnimation;
      m_pCurrentAnimation = &m_cIdleUpAnimation;
      bChangedAnimation = true;
    } else*/
    {
      pLastAnimation = m_pCurrentAnimation;
      m_pCurrentAnimation = &m_cStandingUpAnimation;
      bChangedAnimation = true;
    }

    break;
  }
  case Left:
  {
    if (bPlayIdleAnimation == true)
    {
      pLastAnimation = m_pCurrentAnimation;
      m_pCurrentAnimation = &m_cIdleLeftAnimation;
      bChangedAnimation = true;
    } else if (m_cIdleLeftAnimation.isPlaying() == false)
    {
      pLastAnimation = m_pCurrentAnimation;
      m_pCurrentAnimation = &m_cStandingLeftAnimation;
      bChangedAnimation = true;
    }

    break;
  }
  case Down:
  {
    if (bPlayIdleAnimation == true)
    {
      pLastAnimation = m_pCurrentAnimation;
      m_pCurrentAnimation = &m_cIdleDownAnimation;
      bChangedAnimation = true;
    } else if (m_cIdleDownAnimation.isPlaying() == false)
    {
      pLastAnimation = m_pCurrentAnimation;
      m_pCurrentAnimation = &m_cStandingDownAnimation;
      bChangedAnimation = true;
    }

    break;
  }
  case Right:
  {
    if (bPlayIdleAnimation == true)
    {
      pLastAnimation = m_pCurrentAnimation;
      m_pCurrentAnimation = &m_cIdleRightAnimation;
      bChangedAnimation = true;
    } else if (m_cIdleRightAnimation.isPlaying() == false)
    {
      pLastAnimation = m_pCurrentAnimation;
      m_pCurrentAnimation = &m_cStandingRightAnimation;
      bChangedAnimation = true;
    }

    break;
  }
  } // switch()

  if (bChangedAnimation == true)
  {
    pLastAnimation->stop();
    m_pCurrentAnimation->play();
  }

  /*m_cVelocity.x = 0.0f;
  m_cVelocity.y = 0.0f;*/
}

void Link::updateMovingState(float fDeltaTime)
{
  bool bChangedAnimation = false;
  Animation* pLastAnimation = nullptr;
  uint32 uDirectionCount = 0;
  float fVelocityMult = 1.0f;

  // Prior to this there was a switch() instead of ifs()

  if (m_vFacingDirections[0] == true)
  {
    if (m_bStopped == false)
    {
      if (bChangedAnimation == false && m_pCurrentAnimation != &m_cWalkUpAnimation && uDirectionCount == 0)
      {
        pLastAnimation = m_pCurrentAnimation;
        m_pCurrentAnimation = &m_cWalkUpAnimation;
        bChangedAnimation = true;
      }
    }
    
    if (uDirectionCount > 0)
    {
      fVelocityMult = 0.5f;
    }

    //m_cVelocity.x = 0.0f;
    m_cVelocity.y = -1.0f * fVelocityMult;
    uDirectionCount++;
  }
  
  if (m_vFacingDirections[2] == true) // order changed to maintain animation priority when moving
  {
    if (m_bStopped == false)
    {
      if (bChangedAnimation == false && m_pCurrentAnimation != &m_cWalkDownAnimation && uDirectionCount == 0)
      {
        pLastAnimation = m_pCurrentAnimation;
        m_pCurrentAnimation = &m_cWalkDownAnimation;
        bChangedAnimation = true;
      }
    }

    if (uDirectionCount > 0)
    {
      fVelocityMult = 0.5f;
    }

    //m_cVelocity.x = 0.0f;
    m_cVelocity.y = 1.0f * fVelocityMult;
    uDirectionCount++;
  }
  
  if (m_vFacingDirections[1] == true)
  {
    if (m_bStopped == false)
    {
      if (bChangedAnimation == false && m_pCurrentAnimation != &m_cWalkLeftAnimation && uDirectionCount == 0)
      {
        pLastAnimation = m_pCurrentAnimation;
        m_pCurrentAnimation = &m_cWalkLeftAnimation;
        bChangedAnimation = true;
      }
    }

    if (uDirectionCount > 0)
    {
      fVelocityMult = 0.5f;
    }

    m_cVelocity.x = -1.0f * fVelocityMult;
    //m_cVelocity.y = 0.0f;
    uDirectionCount++;
  }

  if (m_vFacingDirections[3] == true)
  {
    if (m_bStopped == false)
    {
      if (bChangedAnimation == false && m_pCurrentAnimation != &m_cWalkRightAnimation && uDirectionCount == 0)
      {
        pLastAnimation = m_pCurrentAnimation;
        m_pCurrentAnimation = &m_cWalkRightAnimation;
        bChangedAnimation = true;
      }
    }

    if (uDirectionCount > 0)
    {
      fVelocityMult = 0.5f;
    }

    m_cVelocity.x = 1.0f * fVelocityMult;
    //m_cVelocity.y = 0.0f;
    uDirectionCount++;
  }

  if (bChangedAnimation == true)
  {
    pLastAnimation->stop();
    m_pCurrentAnimation->play();
  }

  sf::Vector2f cPosition = m_cSprite.getPosition();
  m_cSprite.setPosition(cPosition.x + m_cVelocity.x * m_fSpeed * fDeltaTime, 
    cPosition.y + m_cVelocity.y * m_fSpeed * fDeltaTime);
}

void Link::update(float fDeltaTime)
{
  updateStateMachine(fDeltaTime);

  m_pCurrentAnimation->update(fDeltaTime);
}