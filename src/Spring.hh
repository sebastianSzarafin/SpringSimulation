#ifndef SYMFIZLAB1_SPRING_HH
#define SYMFIZLAB1_SPRING_HH

#include "pch.hh"

namespace sfl
{
  class Spring
  {
   public:
    Spring(float m, float c, float k, float x, float v);
    Spring()  = default;
    ~Spring() = default;

    void update(uint64_t dt);

    inline float get_x() const { return m_x; }
    inline float get_v() const { return m_v; }
    inline float get_a() const { return m_a; }

   private:
    float dxdt(float v);

    float dvdt(float x, float v, float t);

   private:
    float m_m; // mass
    float m_c; // elasticity coefficient
    float m_k; // damping coefficient

    float m_x; // position
    float m_v; // velocity
    float m_a; // acceleration
  };
} // namespace sfl

#endif // SYMFIZLAB1_SPRING_HH
