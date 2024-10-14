#include "Spring.hh"
#include "Clock.hh"
#include "SimulationInfo.hh"
#include "Utils.hh"

namespace sfl
{
  Spring::Spring(float m, float c, float k, float x, float v) : m_m{ m }, m_c{ c }, m_k{ k }, m_x{ x }, m_v{ v } {}

  void Spring::update(uint64_t dt)
  {
    if (!Clock::running()) { return; }

    float t     = Clock::now();
    float dt_ms = dt / 1000.f;

    float k1x = dxdt(m_v);
    float k1v = dvdt(m_x, m_v, t);

    float k2x = dxdt(m_v + .5f * dt_ms * k1v);
    float k2v = dvdt(m_x + .5f * dt_ms * k1x, m_v + .5f * dt_ms * k1v, t + .5f * dt_ms);

    float k3x = dxdt(m_v + .5f * dt_ms * k2v);
    float k3v = dvdt(m_x + .5f * dt_ms * k2x, m_v + .5f * dt_ms * k2v, t + .5f * dt_ms);

    float k4x = dxdt(m_v + dt_ms * k3v);
    float k4v = dvdt(m_x + dt_ms * k3x, m_v + dt_ms * k3v, t + dt_ms);

    m_x += dt_ms / 6.f * (k1x + 2.f * k2x + 2.f * k3x + k4x);
    m_v += dt_ms / 6.f * (k1v + 2.f * k2v + 2.f * k3v + k4v);
    m_a = dvdt(m_x, m_v, t);

    // printf("time: %f, position: %f, velocity: %f\n", t, m_x, m_v);
  }

  float Spring::calc_f(float t) { return m_c * (SimulationInfo::s_w(t) - m_x); }

  float Spring::calc_g(float t) { return -m_k * m_x; }

  float Spring::dxdt(float v) { return v; }

  float Spring::dvdt(float x, float v, float t)
  {
    return (m_c * (SimulationInfo::s_w(t) - x) - m_k * v + SimulationInfo::s_h(t)) / m_m;
  }
} // namespace sfl
