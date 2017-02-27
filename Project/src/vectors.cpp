#include "vectors.h"

#include <cmath>

Vector2D::Vector2D() {
  x = 0.0f;
  y = 0.0f;
}

Vector2D::Vector2D(float _x, float _y) {
  x = _x;
  y = _y;
}

Vector2D::~Vector2D() {

}

Vector2D Vector2D::operator +(const Vector2D &other) {
  return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator -(const Vector2D &other) {
  return Vector2D(x - other.x, y - other.y);
}

Vector2D Vector2D::operator-() {
  return Vector2D(x * (-1.0f), y * (-1.0f));
}

Vector2D Vector2D::operator *(float factor) {
  return Vector2D(x * factor, y * factor);
}

float Vector2D::operator *(const Vector2D &other) {
  return x * other.x + y * other.y;
}

float Vector2D::operator [](int index) {
  if (index == 0) {
    return x;
  } else if (index == 1){
    return y;
  } else {
    return -1.0f;
  }
}

bool Vector2D::operator==(const Vector2D &other) {
  if (x == other.x && y == other.y) {
    return true;
  }

  return false;
}

bool Vector2D::operator!=(const Vector2D &other) {
  if (x != other.x || y != other.y) {
    return true;
  }

  return false;
}

void Vector2D::normalize() {
  float length = this->length();

  x = x / length;
  y = y / length;
}

float Vector2D::length() {
  return sqrt((x * x) + (y * y));
}