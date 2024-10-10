#include "Application.hh"
#include "Clock.hh"
#include "Constants.hh"
#include "TimedLoop.hh"

#define MIN_FRAME_RATE 16666667L

namespace sfl
{
  std::vector<float> time_stamps{};
  std::vector<float> spring_positions{};
  std::vector<float> spring_velocities{};
  std::vector<float> spring_accelerations{};
  float spring_plot1_y_max = FLT_MIN;

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

    auto spring_loop = TimedLoop(SYM_PERIOD_IN_MS, [&]() { m_spring.update(SYM_PERIOD_IN_MS); }, Status::running);
    std::thread spring_thread([&spring_loop]() { spring_loop.go(); });

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
        spring_loop.stop();
      }

      m_gui->update();

      m_renderer->clear();

      update();

      m_gui->render();
      m_renderer->render();
    }

    spring_thread.join();
  }

  void Application::update()
  {
    float time = Clock::now();
    time_stamps.push_back(time);
    float spring_pos   = m_spring.get_x();
    spring_plot1_y_max = std::max(spring_plot1_y_max, abs(spring_pos));
    spring_positions.push_back(spring_pos);
    float spring_vel   = m_spring.get_v();
    spring_plot1_y_max = std::max(spring_plot1_y_max, abs(spring_vel));
    spring_velocities.push_back(spring_vel);
    float spring_acc   = m_spring.get_a();
    spring_plot1_y_max = std::max(spring_plot1_y_max, abs(spring_acc));
    spring_accelerations.push_back(spring_acc);

    // render spring
    Quad q1{ { 0, spring_pos }, { 300, 100 }, { 1, 0, 0 } };
    m_renderer->draw_quad(q1);
    Quad q2{ { 0, s_world_treshold.w }, { 100, 2 * q1.get_screen_pos().second }, { 0, 1, 0 } };
    m_renderer->draw_quad(q2);
    //

    ImGui::Begin("Position and Velocity over Time");
    if (ImPlot::BeginPlot("##Plot1", ImVec2(-1, 0), ImPlotFlags_NoTitle))
    {
      ImPlot::SetupAxisLimits(ImAxis_X1, 0, Clock::now(), ImGuiCond_Always);
      ImPlot::SetupAxisLimits(ImAxis_Y1, -(spring_plot1_y_max + 1), spring_plot1_y_max + 1, ImGuiCond_Always);
      ImPlot::PlotLine("Position x(t)", &time_stamps[0], &spring_positions[0], time_stamps.size());
      ImPlot::PlotLine("Velocity v(t)", &time_stamps[0], &spring_velocities[0], time_stamps.size());
      ImPlot::PlotLine("Acceleration a(t)", &time_stamps[0], &spring_accelerations[0], time_stamps.size());
      ImPlot::EndPlot();
    }
    ImGui::End();
  }
} // namespace sfl