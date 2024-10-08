#include "Timer.hh"

namespace sfl
{
  Timer::Timer() : m_delta_time{ 0 } { reset(); }

  void Timer::tick()
  {
    auto current_time = std::chrono::high_resolution_clock::now();
    m_delta_time =
        std::chrono::duration<uint64_t, std::chrono::nanoseconds::period>(current_time - m_start_time).count();
  }

  void Timer::reset() { m_start_time = std::chrono::high_resolution_clock::now(); }
} // namespace sfl