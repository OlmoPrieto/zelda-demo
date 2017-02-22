#ifndef __VECTOR_H__
#define __VECTOR_H__

//#include <iostream>
#include <memory>
#include <cmath>
#include <cstring>

typedef unsigned int uint32;
typedef unsigned char byte;

namespace elm
{
template <class T>
class vector
{
public:
  vector()
  {
    m_uClassSize = sizeof(T);
    
    m_uCount = 0;
    m_uCapacity = 2;

    m_pVectorBegin = (T*)malloc(m_uCapacity * m_uClassSize);
    m_pIterator = nullptr;
  }
  
  ~vector()
  {
    if (m_uCount > 0)
    {
      T* pPtr = m_pVectorBegin;
      for (unsigned int i = 0; i < m_uCount; i++)
      {
        pPtr->~T();
        //delete pPtr;
        pPtr++;
      }
    }
    
    if (m_pVectorBegin != nullptr)
    {
      free(m_pVectorBegin);
    }
  }

  T* data() const
  {
    return m_pVectorBegin;
  }

  uint32 classSize() const
  {
    return m_uClassSize;
  }

  uint32 size() const
  {
    return m_uCount;
  }

  uint32 capacity() const
  {
    return m_uCapacity;
  }

  void pushBack(const T& element)
  {
    if (m_uCount == m_uCapacity)
    {
      vector::allocate();
    }

    m_pIterator = m_pVectorBegin + m_uCount;
    //*m_pIterator = element;
    new(m_pVectorBegin + m_uCount)T(element);
    //memcpy(m_pIterator, &element, m_uClassSize);

    m_pIterator = nullptr;
    
    m_uCount++;
  }

  /*
   *  Quite costly. Reallocation can happen.
   *
   *  TODO: maybe assert if position >= m_uCount? && do the same as pushBack()
  */
  void insert(const T& element, uint32 position)
  {
    if (position < m_uCount)
    {
      if (m_uCount == m_uCapacity)
      {
        vector::allocate();
      }

      vector<T> aux;
      aux.reserve(m_uCapacity);
      for (uint32 i = position; i < m_uCount; i++)
      {
        T e = *(m_pVectorBegin + i);
        aux.pushBack(e);
      }

      m_pIterator = m_pVectorBegin + position;
      *m_pIterator = element;
      m_uCount++;
      m_pIterator = nullptr;

      for (uint32 i = position + 1; i < m_uCount; i++)
      {
        T e = aux[i - position - 1];
        m_pIterator = m_pVectorBegin + i;
        *m_pIterator = e;
      }
      m_pIterator = nullptr;
    }
  }

  /*
   *  Returns a copy of the popped element.
  */
  T popBack()
  {
    if (m_uCount > 0)
    {
      T* e = m_pVectorBegin + (m_uCount - 1);
      e->~T();
      m_uCount--;
      return *e;
    }
  }

  /*
   *  If amount is lesser than the actual capacity of the vector,
   *  no reallocation will happen and the elements in the difference 
   *  will be lost.
  */
  void reserve(uint32 amount)
  {
    if (amount > m_uCapacity)
    {
      vector::allocate(amount);
    } else
    {
      m_uCapacity = amount;
    }
  }

  /*  
   *  Note: Because it return an object, it has to be destroyed
   *  locally when exiting the function
  */
  T& operator[](uint32 index) const
  {
    //T* p = m_pVectorBegin + (index);// * m_uClassSize);
    //
    //return *p;
    
    return *(m_pVectorBegin + index);
  }

  /*
   *  Should implement exception-throwing system
  */
  T& at(uint32 index) const
  {
    if (index < m_uCount)
    {
      return operator[](index);
    } else
    {
      //printf("Index out of range in vector\n");
      return T();
    }
  }

  uint32 memorySize()
  {
    return (m_uCapacity * m_uClassSize);
  }

private:
  bool allocate(uint32 amount = 0)
  {
    if (amount == 0)
    {
      /* round(cap + log(cap + 1) */
      //double new_cap = (double)m_uCapacity + log(m_uCapacity + 1);
      //uint32 converted_cap = (uint32)round(new_cap) + 1;

      /* cap * 2 */
      //uint32 converted_cap = m_uCapacity * 2;

      /* cap + cap * 2 */
      //uint32 converted_cap = m_uCapacity + m_uCapacity * 2;

      /* round(cap + (cap / 2) + log(cap + 1)) */
      double new_cap = (double)m_uCapacity + ((double)m_uCapacity / 4.0) + log(m_uCapacity + 1);
      uint32 converted_cap = (uint32)round(new_cap);

      amount = converted_cap;
    }

    T* pTmp = m_pVectorBegin;
    m_pVectorBegin = nullptr;
    m_pVectorBegin = (T*)malloc(amount * m_uClassSize);
    if (m_pVectorBegin != nullptr)  // assert(m_pVectorBegin == nullptr && "Failed to allocate new memory");
    {
      //memcpy(m_pVectorBegin, tmp, m_uClassSize * m_uCount);
      
      T* pTmp2 = pTmp;
      for (uint32 i = 0; i < m_uCount; i++)
      {
        new(m_pVectorBegin + i)T(*pTmp2);
        pTmp2++;
      }
      
      for (uint32 i = 0; i < m_uCount; i++)
      {
        (pTmp + i)->~T();
      }
      free(pTmp);
      pTmp = nullptr;
      pTmp2 = nullptr;

      m_uCapacity = amount;

      return true;
    } else
    {
      // shouldn't enter here, assert
      m_pVectorBegin = nullptr;
      m_pIterator = nullptr;
      pTmp = nullptr;
      return false;
    }

    /*m_pVectorBegin = (T*)realloc(m_pVectorBegin, amount * m_uClassSize);
    m_uCapacity = amount;
    return true;*/
  }

  T* m_pVectorBegin;
  T* m_pIterator;
  uint32 m_uClassSize;
  uint32 m_uCount;
  uint32 m_uCapacity;
};
} // elm namespace

#endif // __VECTOR_H__