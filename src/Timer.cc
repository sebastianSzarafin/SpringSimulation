#include "Timer.hh"
#include "Clock.hh"

namespace sfl
{
  Timer::Timer() : m_delta_time{ 0 } { reset(); }

  void Timer::tick()
  {
    auto current_time = Clock::chrono_now();
    m_delta_time =
        std::chrono::duration<uint64_t, std::chrono::nanoseconds::period>(current_time - m_start_time).count();
  }

  void Timer::reset() { m_start_time = Clock::chrono_now(); }
} // namespace sfl