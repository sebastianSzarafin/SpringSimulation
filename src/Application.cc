#include "Application.hh"
#include "Clock.hh"
#include "Plotter.hh"
#include "SimulationInfo.hh"
#include "TimedLoop.hh"
#include "Utils.hh"

static void draw_func_info(sfl::Func& f_info, const std::string& tag);

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

    m_simulation_loop = std::make_unique<TimedLoop>(
        SYM_PERIOD_IN_MS,
        [&]()
        {
          m_spring.update(SYM_PERIOD_IN_MS);
          Plotter::update(m_spring);
        },
        Status::running);
  }

  Application::~Application()
  {
    m_renderer->terminate();
    m_window->terminate();
    m_gui->terminate();
  }

  void Application::run()
  {
    std::thread simulation_thread([&]() { m_simulation_loop->go(); });

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
        m_simulation_loop->set_status(Status::exiting);
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
      ImGui::Spacing();
      draw_func_info(SimulationInfo::s_w, "w");
      ImGui::Spacing();
      draw_func_info(SimulationInfo::s_h, "h");
      static bool simulation_paused = false;
      if (ImGui::Button("Reset"))
      {
        reset_simulation();
        simulation_paused = false;
      }
      ImGui::SameLine();
      if (simulation_paused)
      {
        if (ImGui::Button("Resume"))
        {
          resume_simulation();
          simulation_paused = false;
        }
      }
      else if (ImGui::Button("Pause"))
      {
        pause_simulation();
        simulation_paused = true;
      }
      ImGui::SameLine();
      if (ImGui::Button("Start"))
      {
        start_simulation();
        simulation_paused = false;
      }
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
    m_simulation_loop->set_status(Status::idle);
  }

  void Application::pause_simulation()
  {
    Clock::pause();
    m_simulation_loop->set_status(Status::idle);
  }

  void Application::resume_simulation()
  {
    Clock::resume();
    m_simulation_loop->set_status(Status::running);
  }

  void Application::start_simulation()
  {
    reset_simulation();
    Clock::start();
    m_simulation_loop->set_status(Status::running);
  }
} // namespace sfl

static void draw_func_info(sfl::Func& f_info, const std::string& tag)
{
  ImGui::Text("%s", (tag + std::string("(t):")).c_str());
  int f_type = f_info.m_type;
  ImGui::RadioButton(("const##" + tag).c_str(), &f_type, sfl::Func::Type::Const);
  ImGui::SameLine();
  ImGui::RadioButton(("step##" + tag).c_str(), &f_type, sfl::Func::Type::Step);
  ImGui::SameLine();
  ImGui::RadioButton(("sgn##" + tag).c_str(), &f_type, sfl::Func::Type::Sgn);
  ImGui::SameLine();
  ImGui::RadioButton(("sin##" + tag).c_str(), &f_type, sfl::Func::Type::Sin);
  f_info.m_type = (sfl::Func::Type)f_type;
  switch (f_info.m_type)
  {
  case sfl::Func::Type::Const:
  case sfl::Func::Type::Step:
    ImGui::SliderFloat(("amplitude##" + tag).c_str(), &f_info.m_amplitude, -2.f, 2.f);
    break;
  case sfl::Func::Type::Sgn:
  case sfl::Func::Type::Sin:
    ImGui::SliderFloat(("amplitude##" + tag).c_str(), &f_info.m_amplitude, -2.f, 2.f);
    ImGui::SliderFloat(("omega##" + tag).c_str(), &f_info.m_omega, -2.f, 2.f);
    ImGui::SliderFloat(("phi##" + tag).c_str(), &f_info.m_phi, -2.f, 2.f);
    break;
  }
}