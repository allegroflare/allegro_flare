



#include <allegro_flare/allegro_flare.h>




using namespace allegro_flare;



class CoordinateWidget : public UIWidget
{
public:
   ALLEGRO_COLOR color;

   CoordinateWidget(UIWidget *parent, float x, float y, float w, float h, ALLEGRO_COLOR color)
      : UIWidget(parent, "CoordinateWidget", new UISurfaceAreaBox(x, y, w, h))
      , color(color)
   {}
   void on_draw() override
   {
      al_draw_rectangle(0, 0, place.size.x, place.size.y, color, 4.0);
      if (mouse_over) draw_crosshair(local_mouse_x, local_mouse_y, color, 30);
   }
};




class DevNestedWidgetCoordinates : public UIScreen
{
public:
   DevNestedWidgetCoordinates(Display *display)
      : UIScreen(display)
   {
      display->background_color(color::black);
      CoordinateWidget *widget1 = new CoordinateWidget(this, 400, 300, 300, 300, color::white);
      CoordinateWidget *widget2 = new CoordinateWidget(widget1, 300, 200, 300, 300, color::orange);
      CoordinateWidget *widget3 = new CoordinateWidget(widget2, 300, 200, 300, 300, color::chartreuse);
      widget2->place.rotation = 0.2;
      widget2->place.scale = vec2d(1.5, 1.5);
      widget3->place.rotation = 0.2;
      widget3->place.scale = vec2d(0.75, 0.75);
   }
};




int main(int argc, char **argv)
{
   Framework::initialize();
   Display *display = Framework::create_display(1280, 720);
   DevNestedWidgetCoordinates project(display);
   Framework::run_loop();
   return 0;
}




