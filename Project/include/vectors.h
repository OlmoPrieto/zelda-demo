#ifndef __VECTORS_H__
#define __VECTORS_H__

typedef unsigned int uint32;
typedef unsigned char byte;

class Vector2D {
 public:
  Vector2D();
  Vector2D(float x, float y);
  ~Vector2D();

  Vector2D operator +(const Vector2D &other);
  Vector2D operator -(const Vector2D &other);
  Vector2D operator -();
  Vector2D operator *(float factor);
  float operator *(const Vector2D &other);  // scalar
  float operator [](int index);
  bool operator ==(const Vector2D &other);
  bool operator !=(const Vector2D &other);

  void normalize();
  float length();

  float x;
  float y;
};

#endif // __VECTORS_H__