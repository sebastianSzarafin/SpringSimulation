#ifndef SYMFIZLAB1_UTILS_HH
#define SYMFIZLAB1_UTILS_HH

#define NS_IN_S          1000000000L
#define NS_IN_MS         1000000L
#define SYM_PERIOD_IN_MS 5

namespace sfl
{
  static const glm::vec4 s_world_treshold = { -10, 10, -10, 10 }; // {l, r, b, t}

  static int sgn(float x) { return (x > 0) - (x < 0); }
} // namespace sfl

#endif // SYMFIZLAB1_UTILS_HH
