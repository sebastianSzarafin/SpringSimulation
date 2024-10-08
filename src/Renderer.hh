#ifndef SYMFIZLAB1_RENDERER_HH
#define SYMFIZLAB1_RENDERER_HH

#include "pch.hh"

#include "Quad.hh"

namespace sfl
{
  class Renderer
  {
   private:
    static Renderer* s_instance;

    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;

   public:
    static std::unique_ptr<Renderer> create();

    ~Renderer() = default;

    void terminate();
    void clear();
    void set_draw_color(glm::vec3& color) const;
    void draw_quad(Quad& quad) const;
    void render();

    inline static SDL_Renderer* get_renderer() { return s_instance->m_renderer; }
    inline static const Renderer* get_instance() { return s_instance; }

   private:
    Renderer() = default;

    void init();
  };
} // namespace sfl

#endif // SYMFIZLAB1_RENDERER_HH
