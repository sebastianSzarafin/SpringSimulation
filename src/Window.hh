#ifndef SYMFIZLAB1_WINDOW_HH
#define SYMFIZLAB1_WINDOW_HH

#include "pch.hh"

namespace sfl
{
  class Window
  {
   public:
    struct WindowData
    {
      std::string m_title;
      const uint32_t m_width;
      const uint32_t m_height;
    };

   private:
    static Window* s_instance;

    std::unique_ptr<WindowData> m_data;
    SDL_Window* m_window;

    bool m_window_closed;

   public:
    static std::unique_ptr<Window> create(WindowData data);

    ~Window() = default;

    void terminate();
    void update();

    inline static uint32_t get_width() { return s_instance->m_data->m_width; }
    inline static uint32_t get_height() { return s_instance->m_data->m_height; }
    inline static SDL_Window* get_window() { return s_instance->m_window; }
    inline static bool is_window_closed() { return s_instance->m_window_closed; }
    inline static const Window* get_instance() { return s_instance; }

   private:
    Window(WindowData data);

    void init();
  };
} // namespace sfl

#endif // SYMFIZLAB1_WINDOW_HH
