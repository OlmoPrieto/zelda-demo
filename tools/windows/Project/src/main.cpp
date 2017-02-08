#include <iostream>

#include "misc.h"
#include "vector.h"

sf::RenderWindow cWindow;
uint32 uWindowWidth = 1366;
uint32 uWindowHeight = 768;
sf::Image cBackgroundImage;
sf::Texture cBackgroundTexture;
sf::Sprite cBackgroundSprite;
Point sImagePos(0.0f, 0.0f);
Point sImagePosDrag(0.0f, 0.0f);
sf::RectangleShape cToolPanel;
bool bIsMousePressed = false;
bool bIsMouseFirstPosSet = false;
Point sMouseFirstPos(0.0f, 0.0f);
Point sMouseSecondPos(0.0f, 0.0f);
sf::View cView;
double fCurrentZoom = 1.0f;
double fMagnifyingZoom = 0.0f;
double fReducingZoom = 0.0f;
elm::vector<Button> vButtons;
byte* pGridPtr = nullptr;
uint32 uGridWidth = 0;
uint32 uGridHeight = 0;
bool bDrawGrid = false;
sf::Font cFont;
sf::Text cDebugText;
sf::RectangleShape cSelectedTile;
bool bIsTileSelected = false;
uint32 uTileSize = 16;
sf::Texture cGridTexture;
sf::Sprite cGridSprite;
Point sGridPosition;

void createGrid(uint32 uBeginX, uint32 uBeginY, uint32 uWidth, uint32 uHeight)
{
  if (pGridPtr != nullptr)
  {
    free(pGridPtr);
  }

  pGridPtr = (byte*)malloc((uWidth - uBeginX + 1) * (uHeight - uBeginY + 1) * 4);
  memset(pGridPtr, 0, (uWidth - uBeginX + 1) * (uHeight - uBeginY + 1) * 4);

  for (uint32 i = 0; i < (uHeight - uBeginY + 1); i++)
  {
    for (uint32 j = 0; j < (uWidth - uBeginX + 1); j++)
    {
      if (j % uTileSize == 0 || i % uTileSize == 0)
      {
        uint32 p = (j + (uWidth - uBeginX + 1) * i) * 4;
        pGridPtr[p + 0] = 255;
        pGridPtr[p + 1] = 0;
        pGridPtr[p + 2] = 255;
        pGridPtr[p + 3] = 32;
      }
    }
  } // for()
  
  /* THE PROBLEM MUST BE IN SFML texture OR sprite */ /* FUCKING TRUE */
  cGridTexture = sf::Texture();
  cGridTexture.create((uWidth - uBeginX + 1), (uHeight - uBeginY + 1));
  //byte* pCleanup = (byte*)malloc((uWidth - uBeginX + 1) * (uHeight - uBeginY + 1) * 4);
  //memset(pCleanup, 0, (uWidth - uBeginX + 1) * (uHeight - uBeginY + 1) * 4);
  //cGridTexture.update(pCleanup);
  cGridTexture.update(pGridPtr);
  //free(pCleanup);

  cGridSprite = sf::Sprite();
  cGridSprite.setTexture(cGridTexture);
  sGridPosition.setPos(float(uBeginX), float(uBeginY));
  cGridSprite.setPosition(sGridPosition.x, sGridPosition.y);
  
  bDrawGrid = true;
}

int main()
{
  cWindow.create(sf::VideoMode(uWindowWidth, uWindowHeight), "WINDOW");
  cView.reset(sf::FloatRect(0.0f, 0.0f, (float)uWindowWidth, (float)uWindowHeight));

  cBackgroundImage.loadFromFile("../../../Project/resources/south-hyrule-field_background.png"); 
  cBackgroundTexture.loadFromImage(cBackgroundImage);
  cBackgroundSprite.setTexture(cBackgroundTexture);

  cToolPanel.setSize(sf::Vector2f(366.0f, (float)uWindowHeight));
  cToolPanel.setFillColor(sf::Color(96, 96, 96, 255));
  cToolPanel.setPosition(1000.0f, 0.0f);

  Button cGridButton(Point(1050.0f, 675.0f), Point(80.0f, 25.0f), "SHOW GRID");

  TextInput cXTextInput(sf::FloatRect(1050.0f, 100.0f, 100.0f, 25.0f), 5);
  TextInput cYTextInput(sf::FloatRect(cXTextInput.m_cDimensions.left + 
    cXTextInput.m_cDimensions.width + cXTextInput.m_cDimensions.width * 0.2f, 
    cXTextInput.m_cDimensions.top, 100.0f, 25.0f), 5);
  TextInput cWidthTextInput(sf::FloatRect(cXTextInput.m_cDimensions.left, 
    cXTextInput.m_cDimensions.top + cXTextInput.m_cDimensions.height + 
    cXTextInput.m_cDimensions.height * 0.2, 100.0f, 25.0f), 5);
  TextInput cHeightTextInput(sf::FloatRect(cYTextInput.m_cDimensions.left, 
    cYTextInput.m_cDimensions.top + cYTextInput.m_cDimensions.height + 
    cYTextInput.m_cDimensions.height * 0.2, 100.0f, 25.0f), 5);
  std::string cXValue = cXTextInput.getString();
  std::string cYValue = cYTextInput.getString();
  std::string cWidthValue = cWidthTextInput.getString();
  std::string cHeightValue = cHeightTextInput.getString();

  sf::Text cWarning;
  cWarning.setFont(cFont);
  cWarning.setCharacterSize(20);
  cWarning.setString("click when all fields are filled");
  cWarning.setColor(sf::Color::Black);
  Point cWarningPos(cWidthTextInput.m_cDimensions.left,
    cWidthTextInput.m_cDimensions.top + cWidthTextInput.m_cDimensions.height +
    cWidthTextInput.m_cDimensions.height * 0.5f);
  cWarning.setPosition(cWarningPos.x, cWarningPos.y);
  
  Button cTextureParametersButton(Point(uWindowWidth - uWindowWidth * 0.04f, 
    cWarningPos.y), Point(30.0f, 25.0f), "SET");

  if (cFont.loadFromFile("../../../Project/resources/arial.ttf") == false)
  {
    printf("Failed to load font\n");
  }
  cDebugText.setFont(cFont);
  cDebugText.setString("");
  cDebugText.setCharacterSize(25);
  cDebugText.setPosition(1050.0f, 300.0f);
  cDebugText.setColor(sf::Color::Black);

  //pGridPtr = (byte*)malloc(uWindowWidth * uWindowHeight * 4);
  //memset(pGridPtr, 0, uWindowWidth * uWindowHeight * 4);

  //for (uint32 i = 0; i < uWindowHeight; i++)
  //{
  //  for (uint32 j = 0; j < uWindowWidth; j++)
  //  {
  //    if (j % uTileSize == 0 || i % uTileSize == 0)
  //    {
  //      uint32 p = (j + uWindowWidth * i) * 4;
  //      pGridPtr[p + 0] = 255;
  //      pGridPtr[p + 1] = 0;
  //      pGridPtr[p + 2] = 255;
  //      pGridPtr[p + 3] = 32;
  //    }
  //  }
  //} // for()

  /*for (uint32 i = 0; i < uWindowHeight; i += 16)
  {
    memset((pGridPtr + (i * uWindowWidth)), 0x00ff00ff, uWindowWidth * 4);
  }

  for (uint32 i = 0; i < uWindowWidth; i += 16)
  {
    memset((pGridPtr + (i * uWindowHeight)), 0x00ff00ff, uWindowHeight * 4);
  }*/

  /*sf::Texture cGridTexture;
  cGridTexture.create(uWindowWidth, uWindowHeight);
  cGridTexture.update(pGridPtr);

  sf::Sprite cGridSprite;
  cGridSprite.setTexture(cGridTexture);
  cGridSprite.setPosition(0.0f, 0.0f);*/

  cSelectedTile.setSize(sf::Vector2f(float(uTileSize) + 1.0f, float(uTileSize) + 1.0f));
  cSelectedTile.setFillColor(sf::Color::Transparent);
  cSelectedTile.setOutlineColor(sf::Color(255, 0, 0, 255));
  cSelectedTile.setOutlineThickness(-1.0f);

  while (cWindow.isOpen())
  {
    // [INPUT]
    sf::Event cEvent;
    while (cWindow.pollEvent(cEvent))
    {
      if (cEvent.type == sf::Event::MouseWheelMoved)
      {
        if (cEvent.mouseWheel.delta > 0)
        {
          fCurrentZoom = 1.0f;
          fMagnifyingZoom += 0.01;
          //fReducingZoom = 0.0f;
          fCurrentZoom -= fMagnifyingZoom;
          fReducingZoom = 0.0f;
        } else if (cEvent.mouseWheel.delta < 0)
        {
          fCurrentZoom = 1.0f;
          fReducingZoom += 0.01;
          //fMagnifyingZoom = 0.0f;
          fCurrentZoom += fReducingZoom;
          fMagnifyingZoom = 0.0f;
        }
        cView.zoom(fCurrentZoom);
      }
    }

    sf::Keyboard::Key eKey;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
      eKey = sf::Keyboard::Key::Escape;
      cWindow.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
      if (sf::Mouse::getPosition(cWindow).x < 1000)
      {
        if (bIsMouseFirstPosSet == false)
        {
          sMouseFirstPos.setPos(sf::Mouse::getPosition(cWindow));
          sMouseSecondPos.setPos(sMouseFirstPos);
          bIsMouseFirstPosSet = true;
        }
        if (bIsMousePressed == true)
        {
          sMouseSecondPos.setPos(sf::Mouse::getPosition(cWindow));
          //if (sMouseFirstPos * fCurrentZoom != sMouseSecondPos * fCurrentZoom)
          if (sMouseFirstPos != sMouseSecondPos)
          {
            sImagePos.setPos((sImagePosDrag.x - (sMouseSecondPos.x - sMouseFirstPos.x)),
              (sImagePosDrag.y - (sMouseSecondPos.y - sMouseFirstPos.y)));
          }
        }
      }

      bIsMousePressed = true;
    } else
    {
      bIsMousePressed = false;
      bIsMouseFirstPosSet = false;
      sImagePosDrag.setPos(sImagePos);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
      if (sf::Mouse::getPosition(cWindow).x < 1000)
      {
        Point sMousePos;
        sMousePos.setPos(sf::Mouse::getPosition(cWindow));

        int iXPos = int(((float(uWindowWidth) - (cView.getSize().x)) / 2.0f) + (sMousePos.x / (uWindowWidth / cView.getSize().x)));
        int iYPos = int(((float(uWindowHeight) - (cView.getSize().y)) / 2.0f) + (sMousePos.y / (uWindowHeight / cView.getSize().y)));

        // indices in the collision matix
        int uTileXIndex = (iXPos - int(sImagePos.x)) / int(uTileSize);
        int uTileYIndex = (iYPos - int(sImagePos.y)) / int(uTileSize);
        
        cDebugText.setString(std::to_string(sImagePos.x) + " , " + std::to_string(sImagePos.y) + "\n\n" + 
          std::to_string(iXPos - int(sImagePos.x)) + " , " + std::to_string(iYPos - int(sImagePos.y)) + "\n\n" + 
          std::to_string(uTileXIndex) + " , " + std::to_string(uTileYIndex) + "\n\n" + 
          std::to_string(iXPos) + " , " + std::to_string(iYPos) + "\n\n");

        cSelectedTile.setPosition(((uTileXIndex * uTileSize) + sImagePos.x), (uTileYIndex * uTileSize) + sImagePos.y);
        bIsTileSelected = true;
      }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && bIsTileSelected == true)
    {
      if (sf::Mouse::getPosition(cWindow).x < 1000)
      {
        bIsTileSelected = false;
      }
    }

    if (cGridButton.isClicked(&cWindow) == true)
    {
      bDrawGrid = !bDrawGrid;
    }
    if (cTextureParametersButton.isClicked(&cWindow) == true)
    {
      cXValue = cXTextInput.getString();
      cYValue = cYTextInput.getString();
      cWidthValue = cWidthTextInput.getString();
      cHeightValue = cHeightTextInput.getString();

      uGridWidth = std::atoi(cWidthValue.c_str());
      uGridHeight = std::atoi(cHeightValue.c_str());

      if (uGridWidth > 0 && uGridHeight)
      {
        createGrid(std::atoi(cXValue.c_str()), std::atoi(cYValue.c_str()), 
          uGridWidth, uGridHeight);
      }
    }
    cXTextInput.isClicked(&cWindow);
    cXTextInput.processInput(&cWindow);
    cYTextInput.isClicked(&cWindow);
    cYTextInput.processInput(&cWindow);
    cWidthTextInput.isClicked(&cWindow);
    cWidthTextInput.processInput(&cWindow);
    cHeightTextInput.isClicked(&cWindow);
    cHeightTextInput.processInput(&cWindow);
    // [INPUT]


    // [UPDATE]
    cBackgroundSprite.setPosition(sImagePos.x, sImagePos.y);
    cGridSprite.setPosition(sGridPosition.x + cBackgroundSprite.getPosition().x, 
      sGridPosition.y + cBackgroundSprite.getPosition().y);
    // [UPDATE]
    

    // [DRAW]
    cWindow.setView(cView);
    cWindow.clear();
    cWindow.draw(cBackgroundSprite);
    if (bDrawGrid == true)
    {
      cWindow.draw(cGridSprite);
    }
    if (bIsTileSelected == true)
    {
      cWindow.draw(cSelectedTile);
    }
    cWindow.setView(cWindow.getDefaultView());
    //cWindow.clear();
    /*if (bIsTileSelected == true)
    {
      cWindow.draw(cSelectedTile);
    }*/
    cWindow.draw(cToolPanel);
    cWindow.draw(cDebugText);

    cGridButton.draw(&cWindow);
    cXTextInput.draw(&cWindow);
    cYTextInput.draw(&cWindow);
    cWidthTextInput.draw(&cWindow);
    cHeightTextInput.draw(&cWindow);
    cWindow.draw(cWarning);
    cTextureParametersButton.draw(&cWindow);

    cWindow.display();
    // [DRAW]
  }

  free(pGridPtr);
  return 0;
}