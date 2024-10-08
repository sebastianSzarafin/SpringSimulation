#include "Window.hh"

namespace sfl
{
  Window* Window::s_instance = nullptr;

  std::unique_ptr<Window> Window::create(WindowData data)
  {
    assert(!s_instance);
    Window::s_instance = new Window(std::move(data));
    Window::s_instance->init();

    return std::unique_ptr<Window>{ Window::s_instance };
  }

  void Window::terminate()
  {
    SDL_DestroyWindow(m_window);
    SDL_Quit();
  }

  void Window::update()
  {
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT) { m_window_closed = true; }

      ImGui_ImplSDL2_ProcessEvent(&e);
    }

    if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_ESCAPE]) { m_window_closed = true; }
  }

  Window::Window(WindowData data)
  {
    m_data = std::make_unique<WindowData>(data);

    m_window_closed = false;
  }

  void Window::init()
  {
    m_window = SDL_CreateWindow(m_data->m_title.c_str(),
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                m_data->m_width,
                                m_data->m_height,
                                SDL_WINDOW_SHOWN);
    SDL_WarpMouseInWindow(m_window, m_data->m_width / 2, m_data->m_height / 2);
  }
} // namespace sfl