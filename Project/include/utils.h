#ifndef __UTILS_H__
#define __UTILS_H__

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>

typedef unsigned char byte;

namespace Utils
{
static void flipTexture(sf::Texture *pOriginalTexture, sf::Texture *pOutputTexture)
{
  // manually flip left texture
  sf::Vector2u cTextureSize = pOriginalTexture->getSize();
  sf::Image cTmpImage = pOriginalTexture->copyToImage();
  const byte* pPixelPointer = cTmpImage.getPixelsPtr();
  byte* pNewTextureArray = (byte*)malloc(cTextureSize.x *
    cTextureSize.y * 4);
  for (unsigned int i = 0; i < cTextureSize.y; i++)
  {
    for (unsigned int j = 0, k = cTextureSize.x - 1;
      j < cTextureSize.x; j++, k--)
    { // the copy pointer starts on 0 and the original starts on the rightmost pixel
      int iOriginalPtr = (k + i * cTextureSize.x) * 4;
      int iNewPtr = (j + i * cTextureSize.x) * 4;  // ptr to each color

      pNewTextureArray[iNewPtr + 0] = pPixelPointer[iOriginalPtr + 0];
      pNewTextureArray[iNewPtr + 1] = pPixelPointer[iOriginalPtr + 1];
      pNewTextureArray[iNewPtr + 2] = pPixelPointer[iOriginalPtr + 2];
      pNewTextureArray[iNewPtr + 3] = pPixelPointer[iOriginalPtr + 3];
    }
  }
  
  pOutputTexture->create(cTextureSize.x, cTextureSize.y);
  pOutputTexture->update(pNewTextureArray);
  free(pNewTextureArray);
}
}

#endif // __UTILS_H__