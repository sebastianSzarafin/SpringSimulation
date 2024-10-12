#ifndef SYMFIZLAB1_CONSTANTS_HH
#define SYMFIZLAB1_CONSTANTS_HH

#include "SimulationInfo.hh"

#define NS_IN_S          1000000000L
#define NS_IN_MS         1000000L
#define SYM_PERIOD_IN_MS 5

namespace sfl
{
  static float calc_w(float t) { return 0.f; }
  static float calc_h(float t) { return .2f; }

  static const glm::vec4 s_world_treshold = { -10, 10, -10, 10 }; // {l, r, b, t}
} // namespace sfl

#endif // SYMFIZLAB1_CONSTANTS_HH
