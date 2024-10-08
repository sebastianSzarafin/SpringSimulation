#ifndef SYMFIZLAB1_GUI_HH
#define SYMFIZLAB1_GUI_HH

#include "pch.hh"

namespace sfl
{
  class Gui
  {
   private:
    static Gui* s_instance;

   public:
    static std::unique_ptr<Gui> create();

    ~Gui() = default;

    void terminate();
    void update();
    void render();

   private:
    Gui() = default;

    void init();
  };
} // namespace sfl

#endif // SYMFIZLAB1_GUI_HH
