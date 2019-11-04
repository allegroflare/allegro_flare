

#include <AllegroFlare/Display.hpp>

#include <allegro5/allegro_color.h>
//#include <AllegroFlare/Framework.hpp>

//#include <allegro_flare/allegro_flare.h>


namespace AllegroFlare
{
   // in theory, a user would never interface with the backbuffer,
   // they would only draw to sub-bitmaps of the backbuffer, each
   // sub-bitmap belonging to a Screen.  In this way, no transforms
   // or other projections would (should) ever be applied to the
   // backbuffer bitmap.  Clearing and drawing a quad would not be
   // "messed up" by any existing state



   Display *Display::find_display(ALLEGRO_DISPLAY *al_display)
   {
      for (unsigned i=0; i<displays.size(); i++)
         if (al_display == displays[i]->al_display) return displays[i];
      return NULL;
   }



   Display::Display(int width, int height, int display_flags)
      : _background_color(al_color_name("black"))
      , _width(width)
      , _height(height)
      , al_display(NULL)
   {
      // set a few options and flags
      al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 2, ALLEGRO_SUGGEST);
      al_set_new_display_option(ALLEGRO_DEPTH_SIZE, 32, ALLEGRO_SUGGEST);
      al_set_new_display_option(ALLEGRO_SAMPLES, 16, ALLEGRO_SUGGEST);
      al_set_new_display_flags(display_flags);

      // create the actual display
      al_display = al_create_display(width, height);

      // add the display to AllegroFlare's list of displays
      displays.push_back(this);
   }


   Display::~Display()
   {
   }


   void Display::display_close_func()
   {
      //Framework::shutdown_program = true;
   }


   std::vector<Display *> Display::displays;


   int Display::width() { return _width; }


   int Display::height() { return _height; }


   float Display::middle() { return _height/2; }


   float Display::center() { return _width/2; }


   void Display::set_as_target_bitmap()
   {
      al_set_target_bitmap(al_get_backbuffer(al_display));
   }


   void Display::flip()
   {
      al_flip_display();
   }


   void Display::background_color(const ALLEGRO_COLOR &color)
   {
      _background_color = color;
   }
}


