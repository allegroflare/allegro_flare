

#include <allegro_flare/allegro_flare.h>




class Project : public UIScreen
{
private:
  RenderCache render_cache;
  int width;
  int height;

public:
  Project()
    : UIScreen(Framework::initialize() ? Framework::create_display() : NULL)
    , render_cache(RenderCache())
    , width(300)
    , height(200)
  {
    draw_to_render_cache();
  }
  void draw_to_render_cache()
  {
    render_cache.setup_surface(width, height, 8);
    al_draw_filled_rectangle(-1, -1, 1, 1, color::black);
    for (int i=0; i<4; i++) al_draw_circle(0, 0, i*3, color::black, 1.0);
    render_cache.finish_surface();
  }
  void on_draw()
  {
    render_cache.draw(100, 100);
  }
};


int main(int c, char** v)
{
  Project project = Project();
  Framework::run_loop();
  return 0;
}


