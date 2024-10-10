#ifndef SYMFIZLAB1_CONSTANTS_HH
#define SYMFIZLAB1_CONSTANTS_HH

#define NS_IN_MS         1000000L
#define SYM_PERIOD_IN_MS 5

namespace sfl
{
  static const float s_w0 = 0.f; // equilibrium position
  static const float s_h0 = .2f; // external force

  static float w(float t) { return s_w0; }
  static float h(float t) { return s_h0; }

  static const glm::vec4 s_world_treshold = { -10, 10, -10, 10 }; // {l, r, b, t}
} // namespace sfl

#endif // SYMFIZLAB1_CONSTANTS_HH
