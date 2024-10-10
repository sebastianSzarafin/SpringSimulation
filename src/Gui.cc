#include "Gui.hh"
#include "Renderer.hh"
#include "Window.hh"

namespace sfl
{
  Gui* Gui::s_instance = nullptr;

  std::unique_ptr<Gui> Gui::create()
  {
    assert(!s_instance);
    Gui::s_instance = new Gui();
    Gui::s_instance->init();

    return std::unique_ptr<Gui>{ Gui::s_instance };
  }

  void Gui::terminate()
  {
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    ImPlot::DestroyContext();
  }

  void Gui::update()
  {
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGui::ShowDemoWindow();
    ImPlot::ShowDemoWindow();
  }

  void Gui::render()
  {
    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
  }

  void Gui::init()
  {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    ImGui_ImplSDL2_InitForSDLRenderer(Window::get_window(), Renderer::get_renderer());
    ImGui_ImplSDLRenderer2_Init(Renderer::get_renderer());
  }
} // namespace sfl