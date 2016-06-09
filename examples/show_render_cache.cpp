



#include <allegro_flare/allegro_flare.h>




class RenderCachedUIWidget : public UIWidget
{
private:
   RenderCache render_cache;

public:
   RenderCachedUIWidget(UIWidget *p, float x, float y, float w, float h)
      : UIWidget(p, new UISurfaceAreaBox(x, y, w, h))
      , render_cache(RenderCache())
   {}

   void on_draw()
   {
      if (render_cache.is_dirty())
      {
         render_cache.setup_surface(place.size.x, place.size.y, 8);
         draw_widget();
         render_cache.finish_surface();
      }

      render_cache.draw(0, 0);
   }

   void draw_widget()
   {
      al_draw_filled_rounded_rectangle(0, 0, place.size.x, place.size.y, 6, 6, random_color());
      for (unsigned i=0; i<10; i++)
         al_draw_filled_circle(random_int(0, place.size.x), random_int(0, place.size.y), random_int(8, 20), random_color());
      al_draw_filled_rectangle(-1, -1, 1, 1, color::black);
      for (int i=0; i<4; i++) al_draw_circle(0, 0, i*3, color::black, 1.0);
   }

   void on_click()
   {
      render_cache.mark_as_dirty();
   }
};




class Project : public UIScreen
{
private:
   RenderCachedUIWidget ui_widget_1;
   RenderCachedUIWidget ui_widget_2;

public:
   Project()
      : UIScreen(Framework::initialize() ? Framework::create_display() : NULL)
      , ui_widget_1(this, 400, 500, 300, 200)
      , ui_widget_2(this, 800, 300, 300, 200)
      {}
};




int main(int c, char** v)
{
   Project project = Project();
   Framework::run_loop();
   return 0;
}




