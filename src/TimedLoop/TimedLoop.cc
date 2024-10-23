#include "TimedLoop.hh"
#include "Utils.hh"

namespace sfl
{
  TimedLoop::TimedLoop(int period_in_ms, std::function<void(void)> func, Status status) : m_status{ status }
  {
    m_on_tick = std::move(func);
    m_period  = period_in_ms * NS_IN_MS; // convert to nanoseconds
  }

  void TimedLoop::go()
  {
    while (m_status != Status::exiting)
    {
      m_timer.tick();
      if (m_timer.get_dt() < m_period)
      {
        // wait that many ns
        std::this_thread::sleep_for(std::chrono::nanoseconds(m_period - m_timer.get_dt()));
        continue;
      }
      else { m_timer.reset(); }

      if (m_status == Status::running) { m_on_tick(); }
    }
  }

  void TimedLoop::go(uint32_t loops)
  {
    for (uint32_t loop = 0; loop < loops; ++loop)
    {
      if (m_status != Status::running) break;

      m_timer.tick();
      if (m_timer.get_dt() < m_period)
      {
        // wait that many ns
        std::this_thread::sleep_for(std::chrono::nanoseconds(m_period - m_timer.get_dt()));
        continue;
      }
      else { m_timer.reset(); }

      m_on_tick();
    }
  }
  void TimedLoop::set_status(Status status) { m_status = status; }
} // namespace sfl