#ifndef SYMFIZLAB1_TIMEDLOOP_HH
#define SYMFIZLAB1_TIMEDLOOP_HH

#include "pch.hh"

#include "Status.hh"

namespace sfl
{
  /// @brief Simulation of real-time synchronized loop
  class TimedLoop
  {
   public:
    /// @brief Constructor
    /// @param period_in_ms loop m_period in milliseconds
    /// @param func function that should be called in loop
    /// @param status reference to controlling status
    TimedLoop(int period_in_ms, std::function<void(void)> func, Status& status);
    /// @brief start infinite loop
    void go();
    /// @brief start loop for specific cycle numbers
    /// @param loops how many cycles should be done
    void go(uint32_t loops);

   private:
    /// @brief Get process time
    /// @return process time in nanoseconds
    uint64_t get_current_clock_ns();
    /// @brief Calculate time that should be wait
    /// @return time to wait in nanosecounds
    int64_t calc_time_to_wait();
    /// @brief When next loop should be called
    uint64_t m_next_clock;

    /// @brief loop function
    std::function<void(void)> m_on_tick;
    uint64_t m_period;
    Status& m_status;
  };
} // namespace sfl

#endif // SYMFIZLAB1_TIMEDLOOP_HH
