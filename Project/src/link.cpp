#include "link.h"

Link::Link()
{
  sf::Image cLinkSheet;
  bool opened = cLinkSheet.loadFromFile("resources/link_sheet.png");

  
  sf::IntRect cUpSpriteRect(15, 9, 18, 23);  // x y w h
  m_cLinkUpTexture.loadFromImage(cLinkSheet, cUpSpriteRect);

  sf::IntRect cLeftSpriteRect(51, 10, 17, 22);  // x y w h
  m_cLinkLeftTexture.loadFromImage(cLinkSheet, cLeftSpriteRect);

  sf::IntRect cDownSpriteRect(79, 10, 17, 21);  // x y w h
  m_cLinkDownTexture.loadFromImage(cLinkSheet, cDownSpriteRect);

  // TODO: this doesn't get the correct texture-rect
  cLinkSheet.flipHorizontally();
  sf::IntRect cRightSpriteRect(1157, 10, 17, 22);  // x y w h
  m_cLinkRightTexture.loadFromImage(cLinkSheet, cRightSpriteRect);

  m_cSprite.setTexture(m_cLinkDownTexture);
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
  if (eKey == sf::Keyboard::Key::Up)
  {
    m_cSprite.setTexture(m_cLinkUpTexture);
  } else if (eKey == sf::Keyboard::Key::Left)
  {
    m_cSprite.setTexture(m_cLinkLeftTexture);
  } else if (eKey == sf::Keyboard::Key::Down)
  {
    m_cSprite.setTexture(m_cLinkDownTexture);
  } else if (eKey == sf::Keyboard::Key::Right)
  {
    m_cSprite.setTexture(m_cLinkRightTexture);
  }
}