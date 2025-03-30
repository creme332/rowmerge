#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iomanip>
#include <iostream>

class Timer {
private:
  std::chrono::time_point<std::chrono::steady_clock> start_time;
  std::chrono::time_point<std::chrono::steady_clock> stop_time;
  bool is_running;

public:
  Timer();      // Constructor
  void start(); // Start the timer
  void stop();  // Stop the timer
  void reset(); // Reset the timer
  void
  printElapsedTime() const; // Print the elapsed time in a user-friendly format
  long long getDurationInMilliseconds() const;
};

#endif // TIMER_H
