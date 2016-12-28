#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <vector>

#include "chrono.h"
#include "vector.h"

class Animation
{
public:
  Animation(sf::Sprite *pTargetSprite, float fFrameTime, 
    bool bLooped);
  ~Animation();

  uint32 framesCount() const;

  void play();
  void pause();
  void stop();

  void update(float fDeltaTime);

  void addFrame(const sf::Texture &cNewFrame);

  sf::Texture* getCurrentFrame();

private:
  Animation() {}

  bool m_bPaused;
  bool m_bStopped;
  bool m_bLooped;
  byte m_byFrameIndex;  // 255 frames max
  float m_fElapsedTime;
  float m_fFrameTime;
  sf::Sprite* m_pTargetSprite;  // the sprite where the animation is going to be drawn at
  Chrono m_cChrono;
  std::vector<sf::Texture> m_vFramesTextures;
};

#endif // __ANIMATION_H__