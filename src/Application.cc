#include "Application.hh"
#include "Clock.hh"
#include "Constants.hh"
#include "Plotter.hh"
#include "SimulationInfo.hh"
#include "TimedLoop.hh"

namespace sfl
{
  Application::Application(Window::WindowData window_data)
  {
    SDL_Init(SDL_INIT_VIDEO);

    m_window   = Window::create(std::move(window_data));
    m_renderer = Renderer::create();
    m_gui      = Gui::create();

    m_spring = Spring(SimulationInfo::s_m,
                      SimulationInfo::s_c,
                      SimulationInfo::s_k,
                      SimulationInfo::s_x0,
                      SimulationInfo::s_v0);
  }

  Application::~Application()
  {
    m_renderer->terminate();
    m_window->terminate();
    m_gui->terminate();
  }

  void Application::run()
  {
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
      uint64_t dt_ns = SimulationInfo::s_dt * NS_IN_S;
      if (m_timer.get_dt() < dt_ns)
      {
        // wait that many ns
        std::this_thread::sleep_for(std::chrono::nanoseconds(dt_ns - m_timer.get_dt()));
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

    // draw simulation info
    ImGui::SetNextWindowSize(ImVec2(500, 0), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
    ImGui::Begin("Simulation info");
    {
      ImGui::Text("FPS: %.1f", 1 / SimulationInfo::s_dt);
      ImGui::Text("Simulation time: %.1f", Clock::now());
      ImGui::Spacing();
      ImGui::Text("Position (x): %.1f", m_spring.get_x());
      ImGui::Text("Velocity (v): %.1f", m_spring.get_v());
      ImGui::Text("Acceleration (a): %.1f", m_spring.get_a());
      ImGui::Spacing();
      ImGui::SliderFloat("Time step (dt)", &SimulationInfo::s_dt, .001f, .2f);
      ImGui::SliderFloat("Spring mass (m)", &SimulationInfo::s_m, .001f, 10.f);
      ImGui::SliderFloat("Spring elasticity (c)", &SimulationInfo::s_c, .001f, 10.f);
      ImGui::SliderFloat("Spring damping (k)", &SimulationInfo::s_k, .001f, 10.f);
      ImGui::SliderFloat("Initial position (x0)", &SimulationInfo::s_x0, -10.f, 10.f);
      ImGui::SliderFloat("Initial velocity (v0)", &SimulationInfo::s_v0, -10.f, 10.f);
      if (ImGui::Button("Reset")) { reset_simulation(); }
      ImGui::SameLine();
      if (ImGui::Button("Start")) { start_simulation(); }
    }
    ImGui::End();
    //

    // draw plots
    ImGui::SetNextWindowSize(ImVec2(500, 0), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(Window::get_width() - 500, 0), ImGuiCond_Once);
    ImGui::Begin("Simulation plots", nullptr, ImGuiWindowFlags_NoTitleBar);
    {
      Plotter::draw_xt_vt_at_plot();
      Plotter::draw_ft_gt_ht_wt_plot();
      Plotter::draw_x_v_plot();
    }
    ImGui::End();
    //
  }

  void Application::reset_simulation()
  {
    Clock::reset();
    m_spring = Spring(SimulationInfo::s_m,
                      SimulationInfo::s_c,
                      SimulationInfo::s_k,
                      SimulationInfo::s_x0,
                      SimulationInfo::s_v0);
    Plotter::reset();
  }

  void Application::start_simulation()
  {
    reset_simulation();
    Clock::start();
  }
} // namespace sfl