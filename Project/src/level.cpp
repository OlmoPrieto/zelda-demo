#include "level.h"

Level::Level()
{
  sf::Image cImage;
  cImage.loadFromFile("resources/south-hyrule-field_background.png");

  m_cMapTexture.loadFromImage(cImage, sf::IntRect(1, 0, 1008, 1068));
  m_uMapWidth = m_cMapTexture.getSize().x;
  m_uMapHeight = m_cMapTexture.getSize().y;

  m_cMapSprite.setTexture(m_cMapTexture);
  m_cMapSprite.setPosition(0.0f, 0.0f);
}

Level::~Level()
{

}

sf::Sprite* Level::getSprite()
{
  return &m_cMapSprite;
}

uint32 Level::getWidth() const
{
  return m_uMapWidth;
}

uint32 Level::getHeight() const
{
  return m_uMapHeight;
}