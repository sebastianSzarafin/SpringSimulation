#ifndef SYMFIZLAB1_TIMER_HH
#define SYMFIZLAB1_TIMER_HH

#include "pch.hh"

namespace sfl
{
  class Timer
  {
   public:
    Timer();
    ~Timer() = default;

    /// @brief Updates previous and current's tick time.
    void tick();
    /// @brief Resets tick time.
    void reset();
    /// @brief Returns delta time between ticks in nanoseconds.
    /// @return Delta time between ticks.
    inline uint64_t get_dt() { return m_delta_time; }

   private:
    std::chrono::high_resolution_clock::time_point m_start_time;
    uint64_t m_delta_time;
  };
} // namespace sfl

#endif // SYMFIZLAB1_TIMER_HH
