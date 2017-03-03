#include "level.h"

#include <fstream>

Level::Level()
{
  sf::Image cImage;
  cImage.loadFromFile("resources/south-hyrule-field_background.png");

  m_cMapTexture.loadFromImage(cImage, sf::IntRect(1, 0, 1008, 1068));
  m_uMapWidth = m_cMapTexture.getSize().x;
  m_uMapHeight = m_cMapTexture.getSize().y;
  
  m_uTileSize = 0;
  
  loadGridFile("resources/grid1.gr");

  m_pWindowRef = nullptr;
  // TODO: healty harcode here for window's parameters
  m_cView.reset(sf::FloatRect(0.0f, 0.0f, 800.0f, 600.0f));
  m_cView.zoom(0.5f);
  m_cView.move(-(800.0f * 0.25f), -(600.0f * 0.25f));

  m_cViewPos.x = 800.0f * 0.25f * 2.0f;
  m_cViewPos.y = 600.0f * 0.25f * 2.0f;

  m_cMapSprite.setTexture(m_cMapTexture);
  m_cMapSprite.setPosition(0.0f, 0.0f);
}

Level::~Level()
{

}

bool Level::loadGridFile(const std::string& cFileName)
{
  FILE* pFile = fopen(cFileName.c_str(), "r");
  if (pFile != nullptr)
  {
    fread(&m_uTileSize, sizeof(uint32), 1, pFile);
    uint32 uGridWidth;
    fread(&uGridWidth, sizeof(uint32), 1, pFile);
    uint32 uGridHeight;
    fread(&uGridHeight, sizeof(uint32), 1, pFile);

    m_cGridMatrix.setSize(uGridWidth, uGridHeight);
    fread(m_cGridMatrix.m_pMatrixPtr, 1, uGridWidth * uGridHeight, pFile);
    
    /*for (uint32 i = 0; i < uGridHeight; i++)
    {
      for (uint32 j = 0; j < uGridWidth; j++)
      {
        printf("%u ", m_cGridMatrix.getData(j, i));
      }
      printf("\n");
    }*/
    
    fclose(pFile);
    
    return true;
  } else 
  {
    printf("Failed to open %s\n", cFileName.c_str());
    
    return false;
  }
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

void Level::setWindowRef(sf::RenderWindow* pWindow)
{
  m_pWindowRef = pWindow;
  pWindow->setView(m_cView);
}

byte Level::getTileValue(uint32 uX, uint32 uY) const
{
  return m_cGridMatrix.getData(uX, uY);
}
