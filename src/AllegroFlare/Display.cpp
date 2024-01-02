

#include <AllegroFlare/Display.hpp>

#include <allegro5/allegro_color.h>
#include <AllegroFlare/Logger.hpp>
//#include <AllegroFlare/Framework.hpp>
#include <AllegroFlare/Logger.hpp>

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
   Display::Display(int width, int height, int display_flags__depreciated, int samples, int depth_size, int adapter, bool fullscreen)
      : width(width)
      , height(height)
      , display_flags__depreciated(display_flags__depreciated)
      , samples_requested_at_creation(samples)
      , samples(samples)
      , depth_size(depth_size)
      , adapter(adapter)
      , fullscreen(fullscreen)
      , initialized(false)
      , destroyed(false)
      , result_fullscreen(false)
      , al_display(nullptr)
   {}


   Display::~Display()
   {
      if (initialized && !destroyed)
      {
         AllegroFlare::Logger::warn_from("AllegroFlare::Display::Display()", "creating display.");
         //AllegroFlare::Errors::warn_from(
         //throw std::runtime_error("[AllegroFlare::Display::~Display()]: error: You must call destroy() before the "
                                  //"destructor is called. This will most certainly result in a crash. Continuing.");
      }
   }


   void Display::display_close_func()
   {
      //Framework::shutdown_program = true;
   }


   void Display::initialize()
   {
      if (initialized) throw std::runtime_error("[AllegroFlare::Display::initialize()]: error: already initialized.");


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
      if (samples != 0)
      {
         al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_REQUIRE);
         al_set_new_display_option(ALLEGRO_SAMPLES, samples, ALLEGRO_SUGGEST); // TODO: review these numbers
      }
      al_set_new_display_option(ALLEGRO_DEPTH_SIZE, depth_size, ALLEGRO_SUGGEST); // TODO: review these numbers
      al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST); // TODO: review compatibility of vsync
                                                                    // and obtaining info from the driver if it has

      int display_flags = ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE;
      if (fullscreen) display_flags |= ALLEGRO_FULLSCREEN_WINDOW;

      al_set_new_display_flags(display_flags);

      if (adapter!=-1) al_set_new_display_adapter(adapter);

      // create the actual display
      AllegroFlare::Logger::info_from("AllegroFlare::Display::Display()", "creating display.");
      al_display = al_create_display(width, height);

      if (!al_display)
      {
         AllegroFlare::Logger::throw_error("AllegroFlare::Display::Display()", "Display could not be created.");
      }

      samples = al_get_display_option(al_display, ALLEGRO_SAMPLES);


      result_fullscreen = al_get_display_flags(al_display) & ALLEGRO_FULLSCREEN_WINDOW;



      std::stringstream display_message;
      display_message << "Display (" << al_display << ") created with the following configuration:" << std::endl;
      display_message <<   "     - sample_buffers: "
                      << as_yes_no(al_get_display_option(al_display, ALLEGRO_SAMPLE_BUFFERS)) << std::endl;
      display_message << "             depth_size: "
                      << al_get_display_option(al_display, ALLEGRO_DEPTH_SIZE) << std::endl;
      display_message << "                samples: "
                      << al_get_display_option(al_display, ALLEGRO_SAMPLES) << std::endl;
      display_message << "        max_bitmap_size: "
                      << al_get_display_option(al_display, ALLEGRO_MAX_BITMAP_SIZE) << std::endl;
      display_message << "                  vsync: "
                      << as_yes_no(al_get_display_option(al_display, ALLEGRO_VSYNC)) << std::endl;
      display_message << "                 OpenGL: "
                      << as_yes_no(al_get_display_flags(al_display) & ALLEGRO_OPENGL) << std::endl;
      display_message << "   as fullscreen window: "
                      << as_yes_no(result_fullscreen) << std::endl;

      AllegroFlare::Logger::info_from("AllegroFlare::Display::Display()", display_message.str().c_str());
 
      // add the display to AllegroFlare's list of displays
      // TODO: consider removing this concept of multiple displays?
      displays.push_back(this);


      initialized = true;
   }


   void Display::destroy()
   {
      // TODO: unregister display from "displays"
      // TODO: improve guards before and after initialization and destruction
      if (al_display)
      {
         al_destroy_display(al_display);
         al_display = nullptr;
      }

      destroyed = true;
   }


   std::vector<Display *> Display::displays;


   int Display::get_width() { return width; }


   int Display::get_height() { return height; }


   float Display::get_middle() { return height/2; }


   float Display::get_center() { return width/2; }


   int Display::get_samples_requested_at_creation()
   {
      return samples_requested_at_creation;
   }


   int Display::get_samples()
   {
      if (!al_is_system_installed() || !al_display) throw std::runtime_error("Display::get_samples() not initialized");

      return al_get_display_option(al_display, ALLEGRO_SAMPLES);
   }


   void Display::set_fullscreen(bool fullscreen)
   {
      if (initialized)
      {
         throw std::runtime_error("[Display::set_fullscreen()]: error: Display has already been created. You can only "
                                  "set this option prior to calling initialize()"
                                 );
      }
      this->fullscreen = fullscreen;
   }


   bool Display::get_result_fullscreen()
   {
      if (!initialized)
      {
         throw std::runtime_error("[Display::get_result_fullscreen()]: error: Display has not yet been initialized.");
      }

      return result_fullscreen;
   }


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


