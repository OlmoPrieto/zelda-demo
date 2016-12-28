#ifndef __CHRONO_H__
#define __CHRONO_H__

#include <chrono>

/*
 *  @brief Class simulating a chrono
 *
 *    It has a simple interface to simulate a chrono: start will start 
 *  counting time and it will stop when calling the stop method. The measured 
 *  time can be retrieved by calling methods such as timeAsMilliseconds().
 *
 *  @author Olmo Prieto
*/

class Chrono {
 public:
  Chrono();
  ~Chrono();

  /*
   *  @brief Does nothing, because the data is reset when calling start()
  */
  void init();

  /*
   *  @brief Starts measuring time, reseting previous values
  */
  void start();
  /*
   *  @brief Stops measuring time
  */
  void stop();
  
  /*
   *  @brief Retrieves the measured time as seconds
  */
  double timeAsSeconds() const;
  /*
   *  @brief Retrieves the measured time as milliseconds
  */
  double timeAsMilliseconds() const;
  /*
   *  @brief Retrieves the measured time as microseconds
  */
  double timeAsMicroseconds() const;

 private:
   std::chrono::duration<double> time_;
  std::chrono::high_resolution_clock clock_;
  std::chrono::high_resolution_clock::time_point start_;
  std::chrono::high_resolution_clock::time_point end_;
};

#endif // __CHRONO_H__