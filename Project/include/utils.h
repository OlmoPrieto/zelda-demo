#ifndef __UTILS_H__
#define __UTILS_H__

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <cstring>

typedef unsigned int uint32;
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

template <class T>
class Matrix
{
public:
  Matrix()
  {
    m_pMatrixPtr = nullptr;
    m_uWidth = 0;
    m_uHeight = 0;
  }

  Matrix(uint32 uWidth, uint32 uHeight, bool bIdentity = false)
  {
    m_uWidth = uWidth;
    m_uHeight = uHeight;

    m_pMatrixPtr = (T*)malloc(uWidth * uHeight * sizeof(T));

    T* pPtr = m_pMatrixPtr;
    for (uint32 i = 0; i < uHeight; i++)
    {
      for (uint32 j = 0; j < uWidth; j++)
      {
        *pPtr = 0;
        if (bIdentity == true)
        {
          if (i == j)
          {
            *pPtr = 1;
          }
        }

        pPtr++;
      }
    }

    pPtr = nullptr;
  } // Matrix(w,h,b);

  ~Matrix()
  {
    if (m_pMatrixPtr != nullptr)
    {
      free(m_pMatrixPtr);
    }
  }

  void setData(uint32 uIndex, const T& cValue)
  {
    m_pMatrixPtr[uIndex] = cValue;
  }

  void setData(uint32 uX, uint32 uY, const T& cValue)
  {
    m_pMatrixPtr[uX + m_uWidth * uY] = cValue;
  }

  T getData(uint32 uIndex) const
  {
    if (m_pMatrixPtr == nullptr)
    {
      return 0;
    } else
    {
      return m_pMatrixPtr[uIndex];
    }
  }

  T getData(uint32 uX, uint32 uY) const
  {
    if (m_pMatrixPtr == nullptr)
    {
      return 0;
    } else
    {
      return m_pMatrixPtr[uX + m_uWidth * uY];
    }
  }

  void cleanMatrix()
  {
    memset(m_pMatrixPtr, 0, m_uWidth * m_uHeight * sizeof(T));
  }

  void setIdentity()
  {
    T* pPtr = m_pMatrixPtr;
    for (uint32 i = 0; i < m_uHeight; i++)
    {
      for (uint32 j = 0; j < m_uWidth; j++)
      {
        *pPtr = 0;

        if (i == j)
        {
          *pPtr = 1;
        }

        pPtr++;
      }
    }

    pPtr = nullptr;
  }

  void setSize(uint32 uWidth, uint32 uHeight)
  {
    if (m_pMatrixPtr != nullptr)
    {
      free(m_pMatrixPtr);
    }

    m_uWidth = uWidth;
    m_uHeight = uHeight;

    m_pMatrixPtr = (T*)malloc(uWidth * uHeight * sizeof(T));

    memset(m_pMatrixPtr, 0, uWidth * uHeight * sizeof(T));
  }

  uint32 getNumElements() const
  {
    return (m_uWidth * m_uHeight);
  }

  T* m_pMatrixPtr;
  uint32 m_uWidth;
  uint32 m_uHeight;
};
}

#endif // __UTILS_H__
