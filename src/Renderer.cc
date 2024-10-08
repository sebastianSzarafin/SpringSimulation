#include "Renderer.hh"
#include "Gui.hh"
#include "Window.hh"

#define SDL_COLOR_BASE 255.f

namespace sfl
{
  Renderer* Renderer::s_instance = nullptr;

  std::unique_ptr<Renderer> Renderer::create()
  {
    assert(!s_instance);
    Renderer::s_instance = new Renderer();
    Renderer::s_instance->init();

    return std::unique_ptr<Renderer>{ Renderer::s_instance };
  }

  void Renderer::terminate() { SDL_DestroyRenderer(m_renderer); }

  void Renderer::clear()
  {
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
  }

  void Renderer::set_draw_color(glm::vec3& color) const
  {
    // Move color from normalized space to RGB space
    color *= SDL_COLOR_BASE;
    color = glm::clamp(color, 0.f, SDL_COLOR_BASE);
    // Set render draw color
    SDL_SetRenderDrawColor(m_renderer, color.x, color.y, color.z, 255);
  }

  void Renderer::draw_quad(Quad& quad) const
  {
    set_draw_color(quad.m_color);
    int w = (int)quad.m_size.x;
    int h = (int)quad.m_size.y;
    int x = (int)quad.m_pos.x - w / 2;
    int y = (int)quad.m_pos.y - h / 2;
    SDL_Rect r{ x, y, w, h };
    SDL_RenderFillRect(m_renderer, &r);
  }

  void Renderer::render()
  {
    SDL_SetRenderTarget(m_renderer, NULL);
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
    SDL_RenderPresent(m_renderer);
    SDL_SetRenderTarget(m_renderer, m_texture);
  }
  void Renderer::init()
  {
    m_renderer = SDL_CreateRenderer(Window::get_window(), -1, SDL_RENDERER_ACCELERATED);

    m_texture = SDL_CreateTexture(m_renderer,
                                  SDL_PIXELFORMAT_RGBA8888,
                                  SDL_TEXTUREACCESS_TARGET,
                                  Window::get_width(),
                                  Window::get_height());
    SDL_SetRenderTarget(m_renderer, m_texture);
  }
} // namespace sfl