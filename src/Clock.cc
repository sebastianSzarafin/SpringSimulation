#include "Clock.hh"

namespace sfl
{
  std::chrono::high_resolution_clock::time_point start_time;

  void Clock::init() { start_time = chrono_now(); }

  std::chrono::high_resolution_clock::time_point Clock::chrono_now()
  {
    return std::chrono::high_resolution_clock::now();
  }

  float Clock::now()
  {
    auto current_time = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<float, std::chrono::seconds::period>(current_time - start_time).count();
  }
} // namespace sfl