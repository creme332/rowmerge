#include "timer.h"

Timer::Timer() : is_running(false) {}

void Timer::start() {
  if (!is_running) {
    start_time = std::chrono::steady_clock::now();
    is_running = true;
  }
}

void Timer::stop() {
  if (is_running) {
    stop_time = std::chrono::steady_clock::now();
    is_running = false;
  }
}

void Timer::reset() { is_running = false; }

void Timer::printElapsedTime() const {
  if (!is_running) {
    std::chrono::milliseconds elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(stop_time -
                                                              start_time);

    int minutes = (elapsed.count() / 60000);
    int seconds = (elapsed.count() / 1000) % 60;
    int milliseconds = elapsed.count() % 1000;

    std::cout << "Elapsed Time: " << std::setw(2) << std::setfill('0')
              << minutes << ":" << std::setw(2) << std::setfill('0') << seconds
              << "." << std::setw(3) << std::setfill('0') << milliseconds
              << " (seconds + milliseconds)\n";
  } else {
    std::cout << "Timer is still running.\n";
  }
}

long long Timer::getDurationInMilliseconds() const {
  if (!is_running) {
    std::chrono::milliseconds elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(stop_time -
                                                              start_time);
    return elapsed.count();
  }
  return 0; // Returns 0 if the timer is still running
}
