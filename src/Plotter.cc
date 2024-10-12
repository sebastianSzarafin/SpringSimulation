#include "Plotter.hh"
#include "Clock.hh"
#include "Utils.hh"

#define PLOT_TIME_PERIOD 10
#define MAX_POSITIONS    10000

namespace sfl
{
  std::vector<float> time_stamps{};

  std::vector<float> positions{};
  std::vector<float> velocities{};
  std::vector<float> accelerations{};
  float plot1_y_max = FLT_MIN;

  std::vector<float> fts{};
  std::vector<float> gts{};
  std::vector<float> hts{};
  std::vector<float> wts{};
  float plot2_y_max = FLT_MIN;

  std::vector<float> all_positions{};
  std::vector<float> all_velocities{};
  float plot3_y_max = FLT_MIN;

  void Plotter::update(Spring& spring)
  {
    float time = Clock::now();
    time_stamps.push_back(time);

    float history = time_stamps[0];
    if (time - history >= PLOT_TIME_PERIOD)
    {
      time_stamps.clear();
      positions.clear();
      velocities.clear();
      accelerations.clear();
    }

    // update position, velocity and time data
    float spring_pos = spring.get_x();
    plot1_y_max      = std::max(plot1_y_max, abs(spring_pos));
    positions.push_back(spring_pos);
    float spring_vel = spring.get_v();
    plot1_y_max      = std::max(plot1_y_max, abs(spring_vel));
    velocities.push_back(spring_vel);
    float spring_acc = spring.get_a();
    plot1_y_max      = std::max(plot1_y_max, abs(spring_acc));
    accelerations.push_back(spring_acc);
    // update forces data
    float t     = time_stamps.back();
    float f     = spring.calc_f(t);
    plot2_y_max = std::max(plot2_y_max, abs(f));
    fts.push_back(f);
    float g     = spring.calc_g(t);
    plot2_y_max = std::max(plot2_y_max, abs(g));
    gts.push_back(g);
    float h     = calc_h(t);
    plot2_y_max = std::max(plot2_y_max, abs(f));
    hts.push_back(h);
    float w     = calc_w(t);
    plot2_y_max = std::max(plot2_y_max, abs(w));
    wts.push_back(h);
    // update trajectory data
    if (all_positions.size() < MAX_POSITIONS)
    {
      float spring_pos = spring.get_x();
      plot3_y_max      = std::max(plot3_y_max, abs(spring_pos));
      all_positions.push_back(spring_pos);
      float spring_vel = spring.get_v();
      plot3_y_max      = std::max(plot3_y_max, abs(spring_vel));
      all_velocities.push_back(spring_vel);
    }
  }

  void Plotter::reset()
  {
    time_stamps.clear();
    positions.clear();
    velocities.clear();
    accelerations.clear();
    all_positions.clear();
    all_velocities.clear();
  }

  void Plotter::draw_xt_vt_at_plot()
  {
    if (ImPlot::BeginPlot("Position and Velocity over Time", ImVec2(-1, 0)))
    {
      float history = time_stamps[0];
      ImPlot::SetupAxisLimits(ImAxis_X1, history, history + PLOT_TIME_PERIOD, ImGuiCond_Always);
      ImPlot::SetupAxisLimits(ImAxis_Y1, -(plot1_y_max + 1), plot1_y_max + 1, ImGuiCond_Always);
      ImPlot::PlotLine("Position x(t)", &time_stamps[0], &positions[0], time_stamps.size());
      ImPlot::PlotLine("Velocity v(t)", &time_stamps[0], &velocities[0], time_stamps.size());
      ImPlot::PlotLine("Acceleration a(t)", &time_stamps[0], &accelerations[0], time_stamps.size());
      ImPlot::EndPlot();
    }
  }
  void Plotter::draw_ft_gt_ht_wt_plot()
  {
    if (ImPlot::BeginPlot("Forces over Time", ImVec2(-1, 0)))
    {
      float history = time_stamps[0];
      ImPlot::SetupAxisLimits(ImAxis_X1, history, history + PLOT_TIME_PERIOD, ImGuiCond_Always);
      ImPlot::SetupAxisLimits(ImAxis_Y1, -(plot2_y_max + 1), plot2_y_max + 1, ImGuiCond_Always);
      ImPlot::PlotLine("f(t)", &time_stamps[0], &fts[0], time_stamps.size());
      ImPlot::PlotLine("g(t)", &time_stamps[0], &gts[0], time_stamps.size());
      ImPlot::PlotLine("h(t)", &time_stamps[0], &hts[0], time_stamps.size());
      ImPlot::PlotLine("w(t)", &time_stamps[0], &wts[0], time_stamps.size());
      ImPlot::EndPlot();
    }
  }

  void Plotter::draw_x_v_plot()
  {
    if (ImPlot::BeginPlot("Trajectory (x(t), x'(t))", ImVec2(-1, 0)))
    {
      ImPlot::SetupAxisLimits(ImAxis_X1, -(plot3_y_max + 1), plot3_y_max + 1, ImGuiCond_Always);
      ImPlot::SetupAxisLimits(ImAxis_Y1, -(plot3_y_max + 1), plot3_y_max + 1, ImGuiCond_Always);
      ImPlot::PlotLine("Position x(t)", &all_positions[0], &all_velocities[0], all_positions.size());
      ImPlot::EndPlot();
    }
  }
} // namespace sfl