#include "link.h"

#include "utils.h"

#include <cstdio>


Link::Link() : m_cStandingUpAnimation(&m_cSprite, 0.15f, false),
  m_cStandingLeftAnimation(&m_cSprite, 0.15f, false),
  m_cStandingDownAnimation(&m_cSprite, 0.15f, false),
  m_cStandingRightAnimation(&m_cSprite, 0.15f, false),
  m_cIdleDownAnimation(&m_cSprite, 0.15f, false),
  m_cIdleLeftAnimation(&m_cSprite, 0.15f, false),
  m_cIdleRightAnimation(&m_cSprite, 0.15f, false)
{
  m_fNoInputTime = 0.0f;
  m_eFacingDirection = FacingDirection::Down;
  m_pCurrentAnimation = nullptr;
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

  m_pCurrentAnimation = &m_cIdleDownAnimation;
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

  if (eKey == sf::Keyboard::Key::Up)
  {
    m_eFacingDirection = Up;
    m_pCurrentAnimation = &m_cStandingUpAnimation;
  } else if (eKey == sf::Keyboard::Key::Left)
  {
    m_eFacingDirection = Left;
    m_pCurrentAnimation = &m_cStandingLeftAnimation;
  } else if (eKey == sf::Keyboard::Key::Down)
  {
    m_eFacingDirection = Down;
    m_pCurrentAnimation = &m_cStandingDownAnimation;
  } else if (eKey == sf::Keyboard::Key::Right)
  {
    m_eFacingDirection = Right;
    m_pCurrentAnimation = &m_cStandingRightAnimation;
  } else if (eKey == sf::Keyboard::Key::Unknown)
  {
    bIsInput = false;
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
  m_pCurrentAnimation->update(fDeltaTime);

  if (m_fNoInputTime >= 3.0f)
  {
    m_fNoInputTime = 0.0f;
    m_pCurrentAnimation->stop();

    switch (m_eFacingDirection)
    {
    case Up:
    {
      m_pCurrentAnimation = &m_cStandingUpAnimation;
      break;
    }
    case Left:
    {
      m_pCurrentAnimation = &m_cIdleLeftAnimation;
      break;
    }
    case Down:
    {
      m_pCurrentAnimation = &m_cIdleDownAnimation;
      break;
    }
    case Right:
    {
      m_pCurrentAnimation = &m_cIdleRightAnimation;
      break;
    }
    }

    m_pCurrentAnimation->play();
  }
}