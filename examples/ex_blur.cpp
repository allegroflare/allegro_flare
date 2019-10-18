



#include <allegro_flare/allegro_flare.h>




using namespace allegro_flare;



class MyProject : public Screen
{
private:
   ALLEGRO_BITMAP *blurred;
   ALLEGRO_BITMAP *src;

public:
   MyProject(Display *display)
      : Screen(display)
      , blurred(NULL)
      , src(NULL)
   {
      ALLEGRO_BITMAP *src = Framework::bitmap("elm_circle.png");
      blurred = al_create_bitmap(al_get_bitmap_width(src), al_get_bitmap_height(src));
   }

   void key_down_func() override
   {
      static int algo = -1;
      algo++;
      algo = algo % 4;

      al_destroy_bitmap(src);
      src = al_clone_bitmap(Framework::bitmap("elm_circle.png"));

      switch(algo)
      {
      case 0:
         horizontal_box_blur(src, blurred, al_get_bitmap_width(src), al_get_bitmap_height(src), 10);
         break;
      case 1:
         vertical_box_blur(src, blurred, al_get_bitmap_width(src), al_get_bitmap_height(src), 10);
         break;
      case 2:
         box_blur(src, blurred, al_get_bitmap_width(src), al_get_bitmap_height(src), 10);
         break;
      case 3:
         gaussian_blur(src, blurred, al_get_bitmap_width(src), al_get_bitmap_height(src), 10);
         break;
      }
   }

   void primary_timer_func() override
   {
      int h=al_get_bitmap_height(blurred), w=al_get_bitmap_width(blurred);
      al_draw_bitmap(Framework::bitmap("elm_circle.png"), display->width()/2-w/2-w/2, display->height()/2-h/2, 0);
      al_draw_bitmap(blurred, display->width()/2-w/2+w/2, display->height()/2-h/2, 0);

      al_draw_text(Framework::font("DroidSans.ttf 20"), color::white, 100, 100, 0, "Press any key to cycle through the blending modes");
   }
};




int main(int argc, char **argv)
{
   Framework::initialize();
   Display *display = Framework::create_display();
   MyProject *proj = new MyProject(display);
   Framework::run_loop();

   return 0;
}




