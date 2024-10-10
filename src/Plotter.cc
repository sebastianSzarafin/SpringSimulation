#include "Plotter.hh"
#include "Clock.hh"

#define PLOT_TIME_PERIOD 10

namespace sfl
{
  std::vector<float> time_stamps{};
  std::vector<float> spring_positions{};
  std::vector<float> spring_velocities{};
  std::vector<float> spring_accelerations{};
  float spring_plot1_y_max = FLT_MIN;

  void Plotter::draw_plot1(sfl::Spring& spring)
  {
    float time = Clock::now();
    time_stamps.push_back(time);
    float spring_pos   = spring.get_x();
    spring_plot1_y_max = std::max(spring_plot1_y_max, abs(spring_pos));
    spring_positions.push_back(spring_pos);
    float spring_vel   = spring.get_v();
    spring_plot1_y_max = std::max(spring_plot1_y_max, abs(spring_vel));
    spring_velocities.push_back(spring_vel);
    float spring_acc   = spring.get_a();
    spring_plot1_y_max = std::max(spring_plot1_y_max, abs(spring_acc));
    spring_accelerations.push_back(spring_acc);

    float history = time_stamps[0];
    if (time - history >= PLOT_TIME_PERIOD)
    {
      time_stamps.clear();
      spring_positions.clear();
      spring_velocities.clear();
      spring_accelerations.clear();
    }

    ImGui::Begin("Position and Velocity over Time");
    if (ImPlot::BeginPlot("##Plot1", ImVec2(-1, 0), ImPlotFlags_NoTitle))
    {
      ImPlot::SetupAxisLimits(ImAxis_X1, history, history + PLOT_TIME_PERIOD, ImGuiCond_Always);
      ImPlot::SetupAxisLimits(ImAxis_Y1, -(spring_plot1_y_max + 1), spring_plot1_y_max + 1, ImGuiCond_Always);
      ImPlot::PlotLine("Position x(t)", &time_stamps[0], &spring_positions[0], time_stamps.size());
      ImPlot::PlotLine("Velocity v(t)", &time_stamps[0], &spring_velocities[0], time_stamps.size());
      ImPlot::PlotLine("Acceleration a(t)", &time_stamps[0], &spring_accelerations[0], time_stamps.size());
      ImPlot::EndPlot();
    }
    ImGui::End();
  }
} // namespace sfl