



//
// ex_masked_bitmap.cpp
//
// This program demonstrates the create_masked_bitmap() function, which combines two images.
// The resulting bitmap is the least alpha of both, and the color values of the first.
// In other words, the first image is the source, and the opacity of the second is combined
// into it.
//




#include <allegro_flare/allegro_flare.h>




class MaskedBitmapExampleProgram : public Screen
{
private:
   ALLEGRO_BITMAP *bitmap;

public:
   MaskedBitmapExampleProgram(Display *display) : Screen(display)
   {
      bitmap = create_masked_bitmap(Framework::bitmap("rooster_cat_grid.png"), Framework::bitmap("elm_circle.png"));
   }

   void primary_timer_func() override
   {
      al_draw_bitmap(Framework::bitmap("rooster_cat_grid.png"), 100, 100, 0);
      al_draw_bitmap(Framework::bitmap("elm_circle.png"), 400, 100, 0);
      al_draw_bitmap(bitmap, 700, 100, 0);
   }
};




int main(int argc, char **argv)
{
   Framework::initialize();
   Display *display = Framework::create_display(1100, 500);
   MaskedBitmapExampleProgram *prog = new MaskedBitmapExampleProgram(display);
   Framework::run_loop();

   return 0;
}




