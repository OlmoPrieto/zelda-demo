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
bool bDrawGrid = true;
sf::Font cFont;
sf::Text cDebugText;
sf::RectangleShape cSelectedTile;
bool bIsTileSelected = false;
uint32 uTileSize = 16;

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

  Button cZoomButton(Point(1050.0f, 675.0f), Point(50.0f, 25.0f), "Zoom");
  vButtons.pushBack(cZoomButton);

  TextInput cTextInput(sf::FloatRect(1050.0f, 100.0f, 100.0f, 50.0f));

  if (cFont.loadFromFile("../../../Project/resources/arial.ttf") == false)
  {
    printf("Failed to load font\n");
  }
  cDebugText.setFont(cFont);
  cDebugText.setString("");
  cDebugText.setCharacterSize(25);
  cDebugText.setPosition(1050.0f, 100.0f);
  cDebugText.setColor(sf::Color::Black);

  pGridPtr = (byte*)malloc(uWindowWidth * uWindowHeight * 4);
  memset(pGridPtr, 0, uWindowWidth * uWindowHeight * 4);

  byte* pAuxPtr = pGridPtr;
  for (uint32 i = 0; i < uWindowHeight; i++)
  {
    for (uint32 j = 0; j < uWindowWidth; j++)
    {
      if (j % uTileSize == 0 || i % uTileSize == 0)
      {
        uint32 p = (j + uWindowWidth * i) * 4;
        pAuxPtr[p + 0] = 255;
        pAuxPtr[p + 1] = 0;
        pAuxPtr[p + 2] = 255;
        pAuxPtr[p + 3] = 32;
      }
    }
  }

  /*for (uint32 i = 0; i < uWindowHeight; i += 16)
  {
    memset((pGridPtr + (i * uWindowWidth)), 0x00ff00ff, uWindowWidth * 4);
  }

  for (uint32 i = 0; i < uWindowWidth; i += 16)
  {
    memset((pGridPtr + (i * uWindowHeight)), 0x00ff00ff, uWindowHeight * 4);
  }*/

  sf::Texture cGridTexture;
  cGridTexture.create(uWindowWidth, uWindowHeight);
  cGridTexture.update(pGridPtr);

  sf::Sprite cGridSprite;
  cGridSprite.setTexture(cGridTexture);
  cGridSprite.setPosition(0.0f, 0.0f);

  cSelectedTile.setSize(sf::Vector2f(float(uTileSize) + 1.0f, float(uTileSize) + 1.0f));
  cSelectedTile.setFillColor(sf::Color::Transparent);
  cSelectedTile.setOutlineColor(sf::Color(255, 0, 0, 255));
  cSelectedTile.setOutlineThickness(-1.0f);

  while (cWindow.isOpen())
  {
    // [INPUT]
    //sf::Event cEvent;
    //while (cWindow.pollEvent(cEvent))
    //{
    //  if (cEvent.type == sf::Event::MouseWheelMoved)
    //  {
    //    if (cEvent.mouseWheel.delta > 0)
    //    {
    //      fCurrentZoom = 1.0f;
    //      fMagnifyingZoom += 0.01;
    //      //fReducingZoom = 0.0f;
    //      fCurrentZoom -= fMagnifyingZoom;
    //      fReducingZoom = 0.0f;
    //    } else if (cEvent.mouseWheel.delta < 0)
    //    {
    //      fCurrentZoom = 1.0f;
    //      fReducingZoom += 0.01;
    //      //fMagnifyingZoom = 0.0f;
    //      fCurrentZoom += fReducingZoom;
    //      fMagnifyingZoom = 0.0f;
    //    }
    //    cView.zoom(fCurrentZoom);
    //  }
    //}

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
        uint32 uTileXIndex = (iXPos - int(sImagePos.x)) / uTileSize;
        uint32 uTileYIndex = (iYPos - int(sImagePos.y)) / uTileSize;
        
        cDebugText.setString(std::to_string(sImagePos.x) + " , " + std::to_string(sImagePos.y) + "\n\n" + 
          std::to_string(iXPos - int(sImagePos.x)) + " , " + std::to_string(iYPos - int(sImagePos.y)) + "\n\n" + 
          std::to_string(uTileXIndex) + " , " + std::to_string(uTileYIndex) + "\n");

        cSelectedTile.setPosition(uTileXIndex * uTileSize, uTileYIndex * uTileSize);
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

    /*for (uint32 i = 0; i < vButtons.size(); i++)
    {
      vButtons[i].isClicked();
    }*/
    if (cZoomButton.isClicked(&cWindow) == true)
    {
      bDrawGrid = !bDrawGrid;
    }
    cTextInput.isClicked(&cWindow);
    cTextInput.processInput(&cWindow);
    // [INPUT]


    // [UPDATE]
    cBackgroundSprite.setPosition(sImagePos.x, sImagePos.y);
    cGridSprite.setPosition(cBackgroundSprite.getPosition());
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

    for (uint32 i = 0; i < vButtons.size(); i++)
    {
      vButtons[i].draw(&cWindow);
    }
    cTextInput.draw(&cWindow);
    cWindow.display();
    // [DRAW]
  }

  free(pGridPtr);
  return 0;
}