#ifndef SYMFIZLAB1_APPLICATION_HH
#define SYMFIZLAB1_APPLICATION_HH

#include "pch.hh"

#include "Gui.hh"
#include "Renderer.hh"
#include "Spring.hh"
#include "Timer.hh"
#include "Window.hh"

namespace sfl
{
  class Application
  {
   private:
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<Gui> m_gui;

    Timer m_timer;
    Spring m_spring;

   public:
    Application(Window::WindowData window_data);
    ~Application();

    void run();

   private:
    void update();
    void reset_simulation();
    void start_simulation();
  };
} // namespace sfl

#endif // SYMFIZLAB1_APPLICATION_HH
