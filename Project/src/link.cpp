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
  m_eFacingDirection = FacingDirection::Down;
  m_pCurrentAnimation = nullptr;
  m_bStopped = true;
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
  m_cSprite.setPosition(100.0f, 100.0f);
  m_cSprite.setScale(10.0f, 10.0f);
}

Link::~Link()
{
  
}

sf::Sprite* Link::getSprite()
{
  return &m_cSprite;
}

void Link::processInput(const sf::Keyboard::Key &eKey)
{
  bool bIsInput = true;
  m_bStopped = false;

  if (eKey == sf::Keyboard::Key::Up)
  {
    m_eFacingDirection = Up;
    //m_pCurrentAnimation = &m_cStandingUpAnimation;
    if (m_pCurrentAnimation != &m_cWalkUpAnimation)
    {
      m_pCurrentAnimation = &m_cWalkUpAnimation;
      m_pCurrentAnimation->play();
    }
  } else if (eKey == sf::Keyboard::Key::Left)
  {
    m_eFacingDirection = Left;
    //m_pCurrentAnimation = &m_cStandingLeftAnimation;
    if (m_pCurrentAnimation != &m_cWalkLeftAnimation)
    {
      m_pCurrentAnimation = &m_cWalkLeftAnimation;
      m_pCurrentAnimation->play();
    }
  } else if (eKey == sf::Keyboard::Key::Down)
  {
    m_eFacingDirection = Down;
    if (m_pCurrentAnimation != &m_cWalkDownAnimation)
    {
      m_pCurrentAnimation = &m_cWalkDownAnimation;
      m_pCurrentAnimation->play();
    }
  } else if (eKey == sf::Keyboard::Key::Right)
  {
    m_eFacingDirection = Right;
    //m_pCurrentAnimation = &m_cStandingRightAnimation;
    if (m_pCurrentAnimation != &m_cWalkRightAnimation)
    {
      m_pCurrentAnimation = &m_cWalkRightAnimation;
      m_pCurrentAnimation->play();
    }
  } else if (eKey == sf::Keyboard::Key::Unknown)
  {
    bIsInput = false;
    m_bStopped = true;
  }

  if (bIsInput == false)
  {
    m_cChrono.stop();
    static float sfCurrentTime = m_fNoInputTime;
    m_fNoInputTime += m_cChrono.timeAsSeconds() - sfCurrentTime;
    m_cChrono.start();
  } else // if it was useful input, reset the chrono
  {
    m_cChrono.start();
    m_fNoInputTime = 0.0;
  }
}

void Link::update(float fDeltaTime)
{
  bool bPlayIdleAnimation = false;
  bool bChangedAnimation = false;
  Animation* pLastAnimation = nullptr;

  m_pCurrentAnimation->update(fDeltaTime);

  if (m_fNoInputTime >= 2.5f)
  {
    m_fNoInputTime = 0.0f;
    bPlayIdleAnimation = true;
  }

  switch (m_eFacingDirection)
  {
  case Up:
  {
    if (bPlayIdleAnimation == true)
    {
      pLastAnimation = m_pCurrentAnimation;
      m_pCurrentAnimation = &m_cStandingUpAnimation;
      bChangedAnimation = true;
    } else if (m_bStopped == true)
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
    } else if (m_bStopped == true && m_cIdleLeftAnimation.isPlaying() == false)
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
    } else if (m_bStopped == true && m_cIdleDownAnimation.isPlaying() == false)
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
    } else if (m_bStopped == true && m_cIdleRightAnimation.isPlaying() == false)
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
}