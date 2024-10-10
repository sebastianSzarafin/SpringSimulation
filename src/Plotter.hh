#ifndef SYMFIZLAB1_PLOTTER_HH
#define SYMFIZLAB1_PLOTTER_HH

#include "Spring.hh"

namespace sfl
{
  class Plotter
  {
   public:
    static void update();
    static void draw_xt_vt_at_plot(Spring& spring);
    static void draw_ft_gt_ht_wt_plot(Spring& spring);
    static void draw_x_v_plot(Spring& spring);
  };
} // namespace sfl

#endif // SYMFIZLAB1_PLOTTER_HH
