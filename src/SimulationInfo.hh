#ifndef SYMFIZLAB1_SIMULATIONINFO_HH
#define SYMFIZLAB1_SIMULATIONINFO_HH

#include "pch.hh"

#include "Clock.hh"
#include "Utils.hh"

namespace sfl
{
  struct Func
  {
    enum Type
    {
      Const,
      Step,
      Sgn,
      Sin
    };

    Type m_type;
    float m_amplitude;
    float m_omega;
    float m_phi;

    float operator()(float t) const
    {
      switch (m_type)
      {
      case sfl::Func::Type::Const:
        return m_amplitude;
      case sfl::Func::Type::Step:
        return t > 0 ? m_amplitude : 0;
      case sfl::Func::Type::Sgn:
        return sgn(m_amplitude * sin(m_omega * t + m_phi));
      case sfl::Func::Type::Sin:
        return m_amplitude * sin(m_omega * t + m_phi);
      }
    }
  };

  class SimulationInfo
  {
   public:
    static float s_dt;
    static float s_m;
    static float s_c;
    static float s_k;
    static float s_x0;
    static float s_v0;
    static Func s_w;
    static Func s_h;
  };

  inline float SimulationInfo::s_dt = 1 / 60.f;
  inline float SimulationInfo::s_m  = 1;
  inline float SimulationInfo::s_c  = 2.5f;
  inline float SimulationInfo::s_k  = .1f;
  inline float SimulationInfo::s_x0 = 0.f;
  inline float SimulationInfo::s_v0 = 0.f;
  inline Func SimulationInfo::s_w   = { Func::Type::Const, 0, 0, 0 };
  inline Func SimulationInfo::s_h   = { Func::Type::Const, 0, 0, 0 };
} // namespace sfl

#endif // SYMFIZLAB1_SIMULATIONINFO_HH
