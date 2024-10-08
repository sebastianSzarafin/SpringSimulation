#ifndef SYMFIZLAB1_STATUS_HH
#define SYMFIZLAB1_STATUS_HH

namespace sfl
{
  enum class Status
  {
    /// @brief loop is ready to run
    idle = 1,
    /// @brief loop is running
    running = 2,
    /// @brief loop will be break in next occasion.
    exiting = 3,
    /// @brief loop job should be reloaded
    reload = 4
  };
}

#endif // SYMFIZLAB1_STATUS_HH
