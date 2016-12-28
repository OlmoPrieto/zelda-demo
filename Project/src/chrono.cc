#include "chrono.h"

Chrono::Chrono() {
  time_ = std::chrono::duration<double>();
  clock_ = std::chrono::high_resolution_clock();
  start_ = std::chrono::high_resolution_clock::time_point();
  end_ = std::chrono::high_resolution_clock::time_point();
}

Chrono::~Chrono() {

}

void Chrono::init() {

}

void Chrono::start() {
  start_ = clock_.now();
}

void Chrono::stop() {
  end_ = clock_.now();
  time_ = std::chrono::duration_cast<std::chrono::duration<double>>(end_ - start_);
}

double Chrono::timeAsSeconds() const {
  return time_.count();
}

double Chrono::timeAsMilliseconds() const {
  return time_.count() * 1000.0f;
}

double Chrono::timeAsMicroseconds() const {
  return time_.count() * 1000000.0f;
}