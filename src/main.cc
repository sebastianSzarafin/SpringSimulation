#include "Application.hh"

int main()
{
  sfl::Application app({ .m_title = "SymFizLab1", .m_width = 720, .m_height = 720 });
  {
    app.run();
  }

  return EXIT_SUCCESS;
}
