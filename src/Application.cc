#include "Application.hh"

#define MIN_FRAME_RATE 16666667L

namespace sfl
{
  Application::Application(Window::WindowData window_data)
  {
    SDL_Init(SDL_INIT_VIDEO);

    m_window   = Window::create(std::move(window_data));
    m_renderer = Renderer::create();
    m_gui      = Gui::create();
  }

  Application::~Application()
  {
    m_renderer->terminate();
    m_window->terminate();
    m_gui->terminate();
  }

  void Application::run()
  {
    bool running = true;
    while (running)
    {
      m_timer.tick();
      if (m_timer.get_dt() < MIN_FRAME_RATE)
      {
        // wait that many ns
        std::this_thread::sleep_for(std::chrono::nanoseconds(MIN_FRAME_RATE - m_timer.get_dt()));
        continue;
      }
      else { m_timer.reset(); }

      m_window->update();
      if (m_window->is_window_closed()) { running = false; }

      m_gui->update();

      m_renderer->clear();

      update();

      m_gui->render();
      m_renderer->render();
    }
  }

  void Application::update()
  {
    Quad q{ { Window::get_width() / 2, Window::get_height() / 2 }, { 600, 600 }, { 1, 1, 1 } };
    m_renderer->draw_quad(q);
  }
} // namespace sfl