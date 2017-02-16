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
elm::vector<Button> vGridButtons;
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
int uUserTileSize = 0;
byte* pMatrixPtr = nullptr;
uint32 uNumMatrixElements = 0;

void createMatrix()
{
  if (pMatrixPtr != nullptr)
  {
    free(pMatrixPtr);
  }

  uNumMatrixElements = (uGridWidth / uTileSize) * (uGridHeight / uTileSize);
  pMatrixPtr = (byte*)malloc(uNumMatrixElements);
  memset(pMatrixPtr, 0, uNumMatrixElements);
}

void setMatrixElement(uint32 uX, uint32 uY, byte byValue)
{
  pMatrixPtr[uX + uNumMatrixElements * uY] = byValue;
}

void createGrid(uint32 uBeginX, uint32 uBeginY, uint32 uWidth, uint32 uHeight)
{
  // find tile size
  uGridWidth = uWidth - uBeginX;
  uGridHeight = uHeight - uBeginY;
  uint32 uDivider = 0;
  if (uUserTileSize == -1)
  {
    uGridHeight <= uGridWidth ? uDivider = uGridHeight : uDivider = uGridWidth;
    bool bIsDivisor = (uGridWidth % uDivider == 0 && uGridHeight % uDivider == 0);
    while (bIsDivisor == false)
    {
      uDivider--;
      bIsDivisor = (uGridWidth % uDivider == 0 && uGridHeight % uDivider == 0);
    }

    uTileSize = uDivider;
  } else
  {
    uTileSize = uUserTileSize;
  }

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
  cGridTexture.update(pGridPtr);

  cGridSprite = sf::Sprite();
  cGridSprite.setTexture(cGridTexture);
  sGridPosition.setPos(float(uBeginX), float(uBeginY));
  cGridSprite.setPosition(sGridPosition.x, sGridPosition.y);
  
  bDrawGrid = true;

  // Now that everything is set, create the collision matrix
  createMatrix();
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

  TextInput cX1TextInput(sf::FloatRect(1050.0f, 100.0f, 100.0f, 25.0f), 5);
  TextInput cY1TextInput(sf::FloatRect(cX1TextInput.m_cDimensions.left + 
    cX1TextInput.m_cDimensions.width + cX1TextInput.m_cDimensions.width * 0.2f, 
    cX1TextInput.m_cDimensions.top, 100.0f, 25.0f), 5);
  TextInput cX2TextInput(sf::FloatRect(cX1TextInput.m_cDimensions.left, 
    cX1TextInput.m_cDimensions.top + cX1TextInput.m_cDimensions.height + 
    cX1TextInput.m_cDimensions.height * 0.2, 100.0f, 25.0f), 5);
  TextInput cY2TextInput(sf::FloatRect(cY1TextInput.m_cDimensions.left, 
    cY1TextInput.m_cDimensions.top + cY1TextInput.m_cDimensions.height + 
    cY1TextInput.m_cDimensions.height * 0.2, 100.0f, 25.0f), 5);
  std::string cXValue = cX1TextInput.getString();
  std::string cYValue = cY1TextInput.getString();
  std::string cX2Value = cX2TextInput.getString();
  std::string cY2Value = cY2TextInput.getString();

  TextInput cTileSizeTextInput(sf::FloatRect(cX2TextInput.m_cDimensions.left, 
    cX2TextInput.m_cDimensions.top + cX2TextInput.m_cDimensions.height + 
    cX2TextInput.m_cDimensions.height * 0.2f, cX2TextInput.m_cDimensions.width, 
    cX2TextInput.m_cDimensions.height), 5);

  sf::Text cTileSizeInfoText;
  cTileSizeInfoText.setFont(cFont);
  cTileSizeInfoText.setCharacterSize(15);
  cTileSizeInfoText.setString("<- Tile size (-1 for best fit)");
  cTileSizeInfoText.setColor(sf::Color::Black);
  cTileSizeInfoText.setPosition(cTileSizeTextInput.m_cDimensions.left + 
    cTileSizeTextInput.m_cDimensions.width + cTileSizeTextInput.m_cDimensions.width * 0.2f,
    cTileSizeTextInput.m_cDimensions.top + cTileSizeTextInput.m_cDimensions.height * 0.2f);

  sf::Text cWarning;
  cWarning.setFont(cFont);
  cWarning.setCharacterSize(20);
  cWarning.setString("click when all fields are filled");
  cWarning.setColor(sf::Color::Black);
  Point cWarningPos(cTileSizeTextInput.m_cDimensions.left,
    cTileSizeTextInput.m_cDimensions.top + cTileSizeTextInput.m_cDimensions.height +
    cTileSizeTextInput.m_cDimensions.height * 0.5f);
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

  cSelectedTile.setSize(sf::Vector2f(float(uTileSize) + 1.0f, float(uTileSize) + 1.0f));
  cSelectedTile.setFillColor(sf::Color::Transparent);
  cSelectedTile.setOutlineColor(sf::Color(255, 0, 0, 255));
  cSelectedTile.setOutlineThickness(-1.0f);

  {
    Button cButton(Point(cX2TextInput.m_cDimensions.left,
      cX2TextInput.m_cDimensions.top + cX2TextInput.m_cDimensions.height * 5.0f),
      Point(25.0f, 25.0f), "0", sf::Color::Transparent, true);

    vGridButtons.pushBack(cButton);
  }

  {
    Point sPrevButtonPos(vGridButtons[0].m_sPosition);
    Point sPrevButtonSize(vGridButtons[0].m_sSize);
    Button cButton(Point(sPrevButtonPos.x + sPrevButtonSize.x * 1.5f,
      sPrevButtonPos.y), Point(25.0f, 25.0f), "1", sf::Color::Red, true);

    vGridButtons.pushBack(cButton);
  }

  {
    Point sPrevButtonPos(vGridButtons[1].m_sPosition);
    Point sPrevButtonSize(vGridButtons[1].m_sSize);
    Button cButton(Point(sPrevButtonPos.x + sPrevButtonSize.x * 1.5f,
      sPrevButtonPos.y), Point(25.0f, 25.0f), "2", sf::Color::Green, true);

    vGridButtons.pushBack(cButton);
  }

  {
    Point sPrevButtonPos(vGridButtons[2].m_sPosition);
    Point sPrevButtonSize(vGridButtons[2].m_sSize);
    Button cButton(Point(sPrevButtonPos.x + sPrevButtonSize.x * 1.5f,
      sPrevButtonPos.y), Point(25.0f, 25.0f), "3", sf::Color::Blue, true);

    vGridButtons.pushBack(cButton);
  }

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
        
        cDebugText.setString(std::to_string(sImagePos.x) + " , " + std::to_string(sImagePos.y) + "\n" + 
          std::to_string(iXPos - int(sImagePos.x)) + " , " + std::to_string(iYPos - int(sImagePos.y)) + "\n" + 
          std::to_string(uTileXIndex) + " , " + std::to_string(uTileYIndex) + "\n" + 
          std::to_string(iXPos) + " , " + std::to_string(iYPos) + "\n");

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

    for (uint32 i = 0; i < vGridButtons.size(); i++)
    {
      if (vGridButtons[i].isClicked(&cWindow))
      {
        uint32 uButtonValue = std::atoi(vGridButtons[i].getText().c_str());
        printf("Value: %u\n", uButtonValue);
      }
    }

    if (cTextureParametersButton.isClicked(&cWindow) == true)
    {
      cXValue = cX1TextInput.getString();
      cYValue = cY1TextInput.getString();
      cX2Value = cX2TextInput.getString();
      cY2Value = cY2TextInput.getString();

      uint32 uX1Value = std::atoi(cXValue.c_str());
      uint32 uY1Value = std::atoi(cYValue.c_str());
      uint32 uX2Value = std::atoi(cX2Value.c_str());
      uint32 uY2Value = std::atoi(cY2Value.c_str());

      uUserTileSize = std::atoi(cTileSizeTextInput.getString().c_str());

      if (uX2Value > 0 && uY2Value > 0 && uUserTileSize != 0)
      {
        createGrid(uX1Value, uY1Value, uX2Value, uY2Value);
      }
    }
    cX1TextInput.isClicked(&cWindow);
    cX1TextInput.processInput(&cWindow);
    cY1TextInput.isClicked(&cWindow);
    cY1TextInput.processInput(&cWindow);
    cX2TextInput.isClicked(&cWindow);
    cX2TextInput.processInput(&cWindow);
    cY2TextInput.isClicked(&cWindow);
    cY2TextInput.processInput(&cWindow);
    cTileSizeTextInput.isClicked(&cWindow);
    cTileSizeTextInput.processInput(&cWindow);
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
    cWindow.draw(cToolPanel);
    cWindow.draw(cDebugText);

    cGridButton.draw(&cWindow);
    cX1TextInput.draw(&cWindow);
    cY1TextInput.draw(&cWindow);
    cX2TextInput.draw(&cWindow);
    cY2TextInput.draw(&cWindow);
    cTileSizeTextInput.draw(&cWindow);
    cWindow.draw(cTileSizeInfoText);
    cWindow.draw(cWarning);
    cTextureParametersButton.draw(&cWindow);
    for (uint32 i = 0; i < vGridButtons.size(); i++)
    {
      vGridButtons[i].draw(&cWindow);
    }

    cWindow.display();
    // [DRAW]
  }

  if (pGridPtr != nullptr)
  {
    free(pGridPtr);
  }
  if (pMatrixPtr != nullptr)
  {
    free(pMatrixPtr);
  }

  return 0;
}