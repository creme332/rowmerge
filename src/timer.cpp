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

    if (elapsed.count() >= 1000) {
      std::cout << "Elapsed Time: " << std::setw(2) << std::setfill('0')
                << minutes << ":" << std::setw(2) << std::setfill('0')
                << seconds << "\n";
    } else {
      std::cout << "Elapsed Time: " << milliseconds << " ms\n";
    }
  } else {
    std::cout << "Timer is still running.\n";
  }
}