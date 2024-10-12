#ifndef SYMFIZLAB1_QUAD_HH
#define SYMFIZLAB1_QUAD_HH

#include "pch.hh"

#include "Utils.hh"
#include "Window.hh"

namespace sfl
{
  struct Quad
  {
    glm::vec2 m_pos;
    glm::vec2 m_size;
    glm::vec3 m_color;

    std::pair<float, float> get_screen_pos();
  };

  inline std::pair<float, float> Quad::get_screen_pos()
  {
    float x = (m_pos.x - s_world_treshold.x) / (s_world_treshold.y - s_world_treshold.x) * Window::get_width();
    float y = (1 - (m_pos.y - s_world_treshold.z) / (s_world_treshold.w - s_world_treshold.z)) * Window::get_height();

    return { x, y };
  }
} // namespace sfl

#endif // SYMFIZLAB1_QUAD_HH
