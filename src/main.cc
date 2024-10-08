#include "Application.hh"

int main()
{
  sfl::Application app({ .m_title = "SymFizLab1", .m_width = 1920, .m_height = 1080 });
  {
    app.run();
  }

  return EXIT_SUCCESS;
}
