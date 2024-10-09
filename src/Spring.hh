#ifndef SYMFIZLAB1_SPRING_HH
#define SYMFIZLAB1_SPRING_HH

#include "pch.hh"

#include "Constants.hh"

namespace sfl
{
  class Spring
  {
   public:
    Spring(float m = 1.f, float c = .5f, float k = .1f, float x = 0, float v = 0);
    ~Spring() = default;

    void update(uint64_t dt);

    inline float get_x() const { return m_x; }
    inline float get_v() const { return m_v; }

   private:
    float dxdt(float v);
    float dvdt(float x, float v, float t);

   private:
    float m_m; // mass
    float m_c; // elasticity coefficient
    float m_k; // damping coefficient

    float m_x; // position
    float m_v; // velocity
  };
} // namespace sfl

#endif // SYMFIZLAB1_SPRING_HH
