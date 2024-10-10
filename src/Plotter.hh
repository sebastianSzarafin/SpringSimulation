#ifndef SYMFIZLAB1_PLOTTER_HH
#define SYMFIZLAB1_PLOTTER_HH

#include "Spring.hh"

namespace sfl
{
  class Plotter
  {
   public:
    static void draw_plot1(Spring& spring); // x(t), v(t), a(t)
  };
} // namespace sfl

#endif // SYMFIZLAB1_PLOTTER_HH
