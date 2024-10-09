#ifndef SYMFIZLAB1_CONSTANTS_HH
#define SYMFIZLAB1_CONSTANTS_HH

#define NS_IN_MS   1000000L
#define SYM_PERIOD 5

namespace sfl
{
  static const float s_w0 = 1.f; // equilibrium position
  static const float s_h0 = .2f; // external force

  static float w(float t) { return s_w0; }
  static float h(float t) { return s_h0; }
} // namespace sfl

#endif // SYMFIZLAB1_CONSTANTS_HH
