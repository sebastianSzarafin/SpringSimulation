#ifndef SYMFIZLAB1_PLOTTER_HH
#define SYMFIZLAB1_PLOTTER_HH

#include "Spring.hh"

namespace sfl
{
  class Plotter
  {
   public:
    static void update(Spring& spring);
    static void reset(bool all = true);
    static void draw_xt_vt_at_plot();
    static void draw_ft_gt_ht_wt_plot();
    static void draw_x_v_plot();
  };
} // namespace sfl

#endif // SYMFIZLAB1_PLOTTER_HH
