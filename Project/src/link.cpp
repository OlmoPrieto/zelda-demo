#include "link.h"

#include "utils.h"

#include <cstdio>


Link::Link()
{
  sf::Image cLinkSheet;
  bool opened = cLinkSheet.loadFromFile("resources/link_sheet.png");

  
  sf::IntRect cUpSpriteRect(79, 10, 18, 23);  // x y w h
  m_cLinkUpTexture.loadFromImage(cLinkSheet, cUpSpriteRect);

  sf::IntRect cLeftSpriteRect(51, 10, 18, 23);  // x y w h
  m_cLinkLeftTexture.loadFromImage(cLinkSheet, cLeftSpriteRect);

  sf::IntRect cDownSpriteRect(15, 9, 18, 23);  // x y w h
  m_cLinkDownTexture.loadFromImage(cLinkSheet, cDownSpriteRect);
  
  // manually flip left texture
  //sf::Vector2u cLeftTextureSize = m_cLinkLeftTexture.getSize();
  //sf::Image cLeftTextureImage = m_cLinkLeftTexture.copyToImage();
  //const byte* pPixelPointer = cLeftTextureImage.getPixelsPtr();
  //byte* pNewTextureArray = (byte*)malloc(cLeftTextureSize.x * 
  //  cLeftTextureSize.y * 4);
  //for (unsigned int i = 0; i < cLeftTextureSize.y; i++)
  //{
  //  for (unsigned int j = 0, k = cLeftTextureSize.x - 1; 
  //    j < cLeftTextureSize.x; j++, k--)
  //  { // the copy pointer starts on 0 and the original starts on the rightmost pixel
  //    int iOriginalPtr = (k + i * cLeftTextureSize.x) * 4;
  //    int iNewPtr = (j + i * cLeftTextureSize.x) * 4;  // ptr to each color
  //    
  //    pNewTextureArray[iNewPtr + 0] = pPixelPointer[iOriginalPtr + 0];
  //    pNewTextureArray[iNewPtr + 1] = pPixelPointer[iOriginalPtr + 1];
  //    pNewTextureArray[iNewPtr + 2] = pPixelPointer[iOriginalPtr + 2];
  //    pNewTextureArray[iNewPtr + 3] = pPixelPointer[iOriginalPtr + 3];
  //  }
  //}
  //m_cLinkRightTexture.create(cLeftTextureSize.x, cLeftTextureSize.y);
  //m_cLinkRightTexture.update(pNewTextureArray);
  //free(pNewTextureArray);

  Utils::flipTexture(&m_cLinkLeftTexture, &m_cLinkRightTexture);

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
