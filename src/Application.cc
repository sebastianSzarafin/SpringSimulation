#include "Application.hh"
#include "Clock.hh"
#include "Constants.hh"
#include "Plotter.hh"
#include "TimedLoop.hh"

#define MIN_FRAME_RATE 16666667L

namespace sfl
{
  Application::Application(Window::WindowData window_data)
  {
    SDL_Init(SDL_INIT_VIDEO);

    m_window   = Window::create(std::move(window_data));
    m_renderer = Renderer::create();
    m_gui      = Gui::create();

    m_spring = Spring(1, 2.5f, .1f, s_w0, 5);
  }

  Application::~Application()
  {
    m_renderer->terminate();
    m_window->terminate();
    m_gui->terminate();
  }

  void Application::run()
  {
    Clock::init();

    auto simulation_loop = TimedLoop(
        SYM_PERIOD_IN_MS,
        [&]()
        {
          m_spring.update(SYM_PERIOD_IN_MS);
          Plotter::update(m_spring);
        },
        Status::running);
    std::thread simulation_thread([&simulation_loop]() { simulation_loop.go(); });

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
      if (m_window->is_window_closed())
      {
        running = false;
        simulation_loop.stop();
      }

      m_gui->update();

      m_renderer->clear();

      update();

      m_gui->render();
      m_renderer->render();
    }

    simulation_thread.join();
  }

  void Application::update()
  {
    // draw spring
    float spring_pos = m_spring.get_x();
    Quad q1{ { 0, spring_pos }, { 300, 100 }, { 1, 0, 0 } };
    m_renderer->draw_quad(q1);
    Quad q2{ { 0, s_world_treshold.w }, { 100, 2 * q1.get_screen_pos().second }, { 0, 1, 0 } };
    m_renderer->draw_quad(q2);
    //

    // draw plots
    ImGui::SetNextWindowSize(ImVec2(500, 0), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(Window::get_width() - 500, 0), ImGuiCond_Once);
    ImGui::Begin("##Simulation plots", nullptr, ImGuiWindowFlags_NoTitleBar);
    {
      Plotter::draw_xt_vt_at_plot();
      Plotter::draw_ft_gt_ht_wt_plot();
      Plotter::draw_x_v_plot();
    }
    ImGui::End();
    //
  }
} // namespace sfl