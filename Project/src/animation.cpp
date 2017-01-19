#include "animation.h"

Animation::Animation(sf::Sprite *pTargetSprite, float fFrameTime, bool bLooped)
{
  m_bPaused = false;
  m_bStopped = true;
  m_bLooped = bLooped;
  m_bIsStaticAnimation = true;
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
  return m_vFramesRects.size();
}

bool Animation::isPlaying() const
{
  return !(m_bPaused || m_bStopped);
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
  m_pTargetSprite->setTextureRect(m_vFramesRects[0]);
}

void Animation::update(float fDeltaTime)
{
  if (m_bIsStaticAnimation == false)
  {
    if (m_bPaused == false && m_bStopped == false)  // is playing
    {
      m_cChrono.stop();
      m_fElapsedTime += m_cChrono.timeAsSeconds();
      m_cChrono.start();

      if (m_fElapsedTime >= m_fFrameTime)
      {
        if (m_byFrameIndex + 1 == m_vFramesRects.size())
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

        m_pTargetSprite->setTextureRect(m_vFramesRects[m_byFrameIndex]);

        m_fElapsedTime = 0.0f;
      } else
      {
        // not needed
      }
    }
  } else
  {
    m_pTargetSprite->setTextureRect(m_vFramesRects[0]);
  }
}

void Animation::addFrame(const sf::IntRect &cNewFrameRect)
{
  m_vFramesRects.push_back(cNewFrameRect);
  if (m_vFramesRects.size() == 1)
  {
    m_pTargetSprite->setTextureRect(m_vFramesRects[0]);
  } else if (m_vFramesRects.size() > 1) {
    m_bIsStaticAnimation = false;
  }
}

sf::IntRect* Animation::getCurrentFrame()
{
  return &m_vFramesRects[m_byFrameIndex];
}