#include "TimedLoop.hh"

namespace sfl
{
  TimedLoop::TimedLoop(int period_in_ms, std::function<void(void)> func, Status& status) : m_status{ status }
  {
    m_on_tick = std::move(func);
    m_period  = period_in_ms * 1000000L; // convert to nanoseconds
  }

  void TimedLoop::go()
  {
    int64_t time_to_wait = 0;
    // m_next_clock = ((get_current_clock_ns() / one_ms_in_ns) * one_ms_in_ns);
    m_next_clock = get_current_clock_ns();
    while (m_status == Status::running)
    {
      m_on_tick();

      // calculate the next tick time and time to wait from now until that time
      time_to_wait = calc_time_to_wait();

      // check if we're already past the 1ms time interval
      if (time_to_wait > 0)
      {
        // wait that many ns
        std::this_thread::sleep_for(std::chrono::nanoseconds(time_to_wait));
      }
    }
  }

  void TimedLoop::go(uint32_t loops)
  {
    int64_t time_to_wait = 0;
    // m_next_clock = ((get_current_clock_ns() / one_ms_in_ns) * one_ms_in_ns);
    m_next_clock = get_current_clock_ns();
    for (uint32_t loop = 0; loop < loops; ++loop)
    {
      if (m_status != Status::running) break;
      m_on_tick();

      // calculate the next tick time and time to wait from now until that time
      time_to_wait = calc_time_to_wait();

      // check if we're already past the 1ms time interval
      if (time_to_wait > 0)
      {
        // wait that many ns
        std::this_thread::sleep_for(std::chrono::nanoseconds(time_to_wait));
      }
    }
  }

  uint64_t TimedLoop::get_current_clock_ns()
  {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch())
        .count();
  }

  int64_t TimedLoop::calc_time_to_wait()
  {
    m_next_clock += m_period;
    return m_next_clock - get_current_clock_ns();
  }
} // namespace sfl