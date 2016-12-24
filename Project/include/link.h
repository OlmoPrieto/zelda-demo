#ifndef __LINK_H__
#define __LINK_H__

#include <SFML/Graphics.hpp>

class Link
{
public:
  Link();
  ~Link();

  sf::Sprite* getSprite();

  void processInput(const sf::Keyboard::Key &eKey);

private:
  sf::Sprite m_cSprite;
  sf::Texture m_cLinkUpTexture;
  sf::Texture m_cLinkLeftTexture;
  sf::Texture m_cLinkDownTexture;
  sf::Texture m_cLinkRightTexture;
};

#endif // __LINK_H__