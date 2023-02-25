

#include <AllegroFlare/Display.hpp>

#include <allegro5/allegro_color.h>
#include <AllegroFlare/Logger.hpp>
//#include <AllegroFlare/Framework.hpp>

//#include <allegro_flare/allegro_flare.h>

#include <iostream>
#include <sstream>


static std::string as_yes_no(int val)
{
   if (val == 0) return "NO";
   return "YES";
}


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
      // TODO: Look into depreciating this; I believe this should be removed entirely and possibly moved into a
      // manager.
      for (unsigned i=0; i<displays.size(); i++)
         if (al_display == displays[i]->al_display) return displays[i];
      return NULL;
   }



   //Display(int width, int height, int display_flags, int samples=4, int depth_size=32, int adapter=-1);
   Display::Display(int width, int height, int display_flags, int samples, int depth_size, int adapter)
   //Display::Display(int width, int height, int display_flags)
      //: _background_color(al_color_name("black"))
      : _width(width)
      , _height(height)
      , display_flags(display_flags)
      , samples(samples)
      , depth_size(depth_size)
      , adapter(adapter)
      , al_display(nullptr)
   {
      if (width < 120 || height < 120)
      {
         // TODO: improve this error message
         throw std::runtime_error("AllegroFlare/Display: Cannot create display: width and height are not valid.");
      }
      if (depth_size < 0) // TODO: improve this error condition to compare against "valid_depth_sizes"
      {
         throw std::runtime_error("AllegroFlare/Display: Cannot create display: depth size cannot be less than zero.");
      }
      if (samples < 0) // TODO: improve this error condition to compare against "valid_depth_sizes"
      {
         throw std::runtime_error("AllegroFlare/Display: Cannot create display: samples cannot be less than zero.");
      }
      // set a few options and flags
      al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_REQUIRE);
      al_set_new_display_option(ALLEGRO_SAMPLES, samples, ALLEGRO_SUGGEST); // TODO: review these numbers
      al_set_new_display_option(ALLEGRO_DEPTH_SIZE, depth_size, ALLEGRO_SUGGEST); // TODO: review these numbers
      al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST); // TODO: review compatibility of vsync
                                                                    // and obtaining info from the driver if it has
      al_set_new_display_flags(display_flags);

      if (adapter!=-1) al_set_new_display_adapter(adapter);

      // create the actual display
      AllegroFlare::Logger::info_from("AllegroFlare::Display::Display()", "creating display.");
      al_display = al_create_display(width, height);

      if (!al_display)
      {
         AllegroFlare::Logger::throw_error("AllegroFlare::Display::Display()", "Display could not be created.");
      }

      std::stringstream display_message;
      display_message << "Display (" << al_display << ") created with the following configuration:" << std::endl;
      display_message << "   - sample_buffers: "
                      << as_yes_no(al_get_display_option(al_display, ALLEGRO_SAMPLE_BUFFERS)) << std::endl;
      display_message << "         depth_size: "
                      << al_get_display_option(al_display, ALLEGRO_DEPTH_SIZE) << std::endl;
      display_message << "            samples: "
                      << al_get_display_option(al_display, ALLEGRO_SAMPLES) << std::endl;
      display_message << "              vsync: "
                      << as_yes_no(al_get_display_option(al_display, ALLEGRO_VSYNC)) << std::endl;
      display_message << "             OpenGL: "
                      << as_yes_no(al_get_display_flags(al_display) & ALLEGRO_OPENGL) << std::endl;

      AllegroFlare::Logger::info_from("AllegroFlare::Display::Display()", display_message.str().c_str());
 
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


   int Display::get_width() { return _width; }


   int Display::get_height() { return _height; }


   float Display::get_middle() { return _height/2; }


   float Display::get_center() { return _width/2; }


   void Display::set_as_target_bitmap()
   {
      al_set_target_bitmap(al_get_backbuffer(al_display));
   }


   void Display::set_orthographic_projection(float left, float top, float right, float bottom)
   {
      ALLEGRO_BITMAP *display_bitmap = al_get_backbuffer(al_display);
      ALLEGRO_TRANSFORM trans;
      al_identity_transform(&trans);
      al_orthographic_transform(
            &trans,
            left,
            top,
            -1.0,
            right,
            bottom,
            1.0
         );

      ALLEGRO_STATE previous_target_bitmap_state;
      al_store_state(&previous_target_bitmap_state, ALLEGRO_STATE_TARGET_BITMAP);

      al_set_target_bitmap(display_bitmap);
      al_use_projection_transform(&trans);

      al_restore_state(&previous_target_bitmap_state);
   }


   void Display::flip()
   {
      al_flip_display();
   }
} // namespace AllegroFlare


