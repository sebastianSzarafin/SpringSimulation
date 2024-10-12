#ifndef SYMFIZLAB1_SIMULATIONINFO_HH
#define SYMFIZLAB1_SIMULATIONINFO_HH

namespace sfl
{
  class SimulationInfo
  {
   public:
    static float s_dt;
    static float s_m;
    static float s_c;
    static float s_k;
    static float s_x0;
    static float s_v0;
  };

  inline float SimulationInfo::s_dt = 1 / 60.f;
  inline float SimulationInfo::s_m  = 1;
  inline float SimulationInfo::s_c  = 2.5f;
  inline float SimulationInfo::s_k  = .1f;
  inline float SimulationInfo::s_x0 = 0.f;
  inline float SimulationInfo::s_v0 = 0.f;
} // namespace sfl

#endif // SYMFIZLAB1_SIMULATIONINFO_HH
