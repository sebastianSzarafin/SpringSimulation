#ifndef SYMFIZLAB1_CLOCK_HH
#define SYMFIZLAB1_CLOCK_HH

#include "pch.hh"

namespace sfl
{
  class Clock
  {
   public:
    static void start();
    static void reset();
    static std::chrono::high_resolution_clock::time_point chrono_now();
    static float now();
    static bool running();
  };
} // namespace sfl

#endif // SYMFIZLAB1_CLOCK_HH
