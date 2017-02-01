/*
 * Vector2.cpp
 *
 *  Created on: Feb 1, 2017
 *      Author: zxi
 */

#include "Vector2.h"

#include <cmath>
#include <algorithm>
#include <stdexcept>

namespace three {

Vector2::Vector2() :
    x(0), y(0) {
}

Vector2::Vector2(double x, double y) :
    x(x), y(y) {
}

Vector2::Vector2(const Vector2& v) :
    x(v.x), y(v.y) {
}

Vector2& Vector2::set(double x, double y) {
  this->x = x;
  this->y = y;

  return *this;
}

Vector2::~Vector2() {

}

////////////////////////////////////////////////////////

const double Vector2::operator[](int index) const {
  if (index < 0 || index > 1)
    throw std::out_of_range("index out of range.");

  return index == 0 ? x : y;
}

double& Vector2::operator[](int index) {
  if (index < 0 || index > 1)
    throw std::out_of_range("index out of range.");

  return index == 0 ? x : y;
}

Vector2& Vector2::copy(const Vector2& v) {
  this->x = v.x;
  this->y = v.y;

  return *this;
}

Vector2 Vector2::clone() {
  return Vector2(this->x, this->y);
}

Vector2& Vector2::min(const Vector2& v) {
  this->x = std::min(this->x, v.x);
  this->y = std::min(this->y, v.y);

  return *this;
}

Vector2& Vector2::max(const Vector2& v) {
  this->x = std::max(this->x, v.x);
  this->y = std::max(this->y, v.y);

  return *this;
}

Vector2& Vector2::clamp(const Vector2& min_v, const Vector2& max_v)
{

  this->x = std::max(min_v.x, std::min(this->x, max_v.x));
  this->y = std::max(min_v.y, std::min(this->y, max_v.x));

  return *this;
}


// Operatros

Vector2 Vector2::operator+(const double scalar) const {

  return Vector2 { x + scalar, y + scalar };
}

Vector2 Vector2::operator-(const double scalar) const {
  return Vector2 { x - scalar, y - scalar };
}

Vector2 Vector2::operator*(const double scalar) const {

  if (isnan(scalar)) {
    return Vector2 { 0, 0 };
  } else {
    return Vector2(x * scalar, y * scalar);
  }
}

Vector2 Vector2::operator/(const double scalar) const {
  return (*this) * (1.0 / scalar);
}

Vector2 Vector2::operator+(const Vector2& v) const {
  return Vector2 { x + v.x, y + v.y };
}

Vector2 Vector2::operator-(const Vector2& v) const {
  return Vector2 { x - v.x, y - v.y };
}

Vector2 Vector2::operator*(const Vector2& v) const {
  return Vector2 { x * v.x, y * v.y };
}

Vector2 Vector2::operator/(const Vector2& v) const {
  return Vector2 { x / v.x, y / v.y };
}

/* namespace three */
