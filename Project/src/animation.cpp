#include "animation.h"

Animation::Animation(sf::Sprite *pTargetSprite, float fFrameTime, bool bLooped)
{
  m_bPaused = false;
  m_bStopped = true;
  m_bLooped = bLooped;
  m_byFrameIndex = 0;
  m_fElapsedTime = 0.0f;
  m_fFrameTime = fFrameTime;
  m_pTargetSprite = pTargetSprite;
}

Animation::~Animation()
{
  
}

uint32 Animation::framesCount() const
{
  return m_vFramesTextures.size();
}

void Animation::play()
{
  m_cChrono.start();
  m_bPaused = false;
  m_bStopped = false;
}

void Animation::pause()
{
  m_bPaused = true;
}

void Animation::stop()
{
  m_bStopped = true;
  m_byFrameIndex = 0;
}

void Animation::update(float fDeltaTime)
{
  if (m_bPaused == false && m_bStopped == false)  // is playing
  {
    m_cChrono.stop();
    m_fElapsedTime += m_cChrono.timeAsSeconds();
    m_cChrono.start();

    if (m_fElapsedTime >= m_fFrameTime)
    {
      if (m_byFrameIndex + 1 == m_vFramesTextures.size())
      {
        m_byFrameIndex = 0;
        if (m_bLooped == false)
        {
          m_bStopped = true;
        }
      } else
      {
        m_byFrameIndex++;
      }

      m_pTargetSprite->setTexture(m_vFramesTextures[m_byFrameIndex]);

      m_fElapsedTime = 0.0f;
    } else
    {
      // not needed
    }
  }
}

void Animation::addFrame(const sf::Texture &cNewFrame)
{
  m_vFramesTextures.push_back(cNewFrame);
  if (m_vFramesTextures.size() == 1)
  {
    m_pTargetSprite->setTexture(m_vFramesTextures[0]);
  }
}

sf::Texture* Animation::getCurrentFrame()
{
  return &m_vFramesTextures[m_byFrameIndex];
}