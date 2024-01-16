

#include <AllegroFlare/RenderSurfaces/Bitmap.hpp>

#include <allegro5/allegro.h>
#include <AllegroFlare/Color.hpp> // for color::transparent
#include <AllegroFlare/Logger.hpp>



namespace AllegroFlare
{
namespace RenderSurfaces
{


Bitmap::Bitmap() //int surface_width, int surface_height, int multisamples, int depth)
   : AllegroFlare::RenderSurfaces::Base(AllegroFlare::RenderSurfaces::Bitmap::TYPE)
   , surface(nullptr)
   , clear_color(AllegroFlare::Color::Eigengrau)
   , surface_width(1920)
   , surface_height(1080)
   , multisamples(0)
   , depth(0)
   , min_linear(false)
   , mag_linear(false)
   , no_preserve_texture(false)
   //, config_has_changed(false)
   , initialized(false)
   , config_has_changed(false)
{
}


Bitmap::~Bitmap()
{
}



void Bitmap::set_surface_width(int surface_width)
{
   if (surface_width < 1) // || surface_height < 1)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::RenderSurfaces::Bitmap::set_surface_width",
         "Surface cannot have neither width or height less than 1."
      );
   }
   //if (initialized) throw std::runtime_error("AllegroFlare::RenderSurface::Bitmap::set_surface_width: error: already setup");
   this->surface_width = surface_width;
   config_has_changed = true;
}


void Bitmap::set_surface_height(int surface_height)
{
   if (surface_height < 1)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::RenderSurfaces::Bitmap::set_surface_height",
         "Surface cannot have neither width or height less than 1."
      );
   }
   //if (initialized) throw std::runtime_error("AllegroFlare::RenderSurface::Bitmap::set_surface_height: error: already setup");
   this->surface_height = surface_height;
   config_has_changed = true;
}


void Bitmap::set_multisamples(int multisamples)
{
   //if (initialized) throw std::runtime_error("AllegroFlare::RenderSurface::Bitmap::set_multisamples: error: already setup");
   this->multisamples = multisamples;
   config_has_changed = true;
}


void Bitmap::set_depth(int depth)
{
   //if (initialized) throw std::runtime_error("AllegroFlare::RenderSurface::Bitmap::set_depth: error: already setup");
   this->depth= depth;
   config_has_changed = true;
}


void Bitmap::set_min_linear(bool min_linear)
{
   //if (initialized) throw std::runtime_error("AllegroFlare::RenderSurface::Bitmap::set_min_linear: error: already setup");
   this->min_linear = min_linear;
   config_has_changed = true;
}


void Bitmap::set_mag_linear(bool mag_linear)
{
   //if (initialized) throw std::runtime_error("AllegroFlare::RenderSurface::Bitmap::set_mag_linear: error: already setup");
   this->mag_linear = mag_linear;
   config_has_changed = true;
}


void Bitmap::set_no_preserve_texture(bool no_preserve_texture)
{
   //if (initialized) throw std::runtime_error("AllegroFlare::RenderSurface::Bitmap::set_no_preserve_texture: error: already setup");
   this->no_preserve_texture = no_preserve_texture;
   config_has_changed = true;
}


//static bool ignore_dep_error_NOTE_please_faze_out = false;


void Bitmap::initialize()
{
   // TODO: add guard for duplicate initialization
   // TODO: eventually remove this flag
   //ignore_dep_error_NOTE_please_faze_out = true;
   setup_surface(); //surface_width, surface_height, multisamples, depth);
   //ignore_dep_error_NOTE_please_faze_out = false;
   initialized = true;
   config_has_changed = false;
}


void Bitmap::recreate_surface()
{
   setup_surface();
}


void Bitmap::setup_surface()
{
   // Store the current bitmap flags state
   al_store_state(&previous_state, ALLEGRO_STATE_TARGET_BITMAP);


   // Set the samples and depth
   al_set_new_bitmap_samples(multisamples);
   al_set_new_bitmap_depth(depth);


   // Set the flags
   int flags = al_get_new_bitmap_flags();
   if (min_linear) flags |= ALLEGRO_MIN_LINEAR;
   if (mag_linear) flags |= ALLEGRO_MAG_LINEAR;
   if (no_preserve_texture) flags |= ALLEGRO_NO_PRESERVE_TEXTURE;
   al_set_new_bitmap_flags(flags);


   // Destroy previous surface if it's present
   if (surface) al_destroy_bitmap(surface);


   // Create the surface texture
   surface = al_create_bitmap(surface_width, surface_height);
   int surface_bitmap_flags = al_get_bitmap_flags(surface);

   //bool memory_bitmap = surface_bitmap_flags & ALLEGRO_MEMORY_BITMAP;
   bool video_bitmap = surface_bitmap_flags & ALLEGRO_VIDEO_BITMAP;

   if (!video_bitmap)
   {
      AllegroFlare::Logger::warn_from("AllegroFlare::RenderSurfaces::Bitmap::setup_surface", "The surface "
                                      "was not created as a video_bitmap. It's expected that the surface will be "
                                      "a video bitmap for optimized rendering for post-processing contexts. It's "
                                      "possible in the future that this RenderSurface could be permitted to be "
                                      "a non-video bitmap, but for now it is not.");
   }

   al_set_target_bitmap(surface);
   al_clear_to_color(color::transparent);
   al_restore_state(&previous_state);

   config_has_changed = false;
}



void Bitmap::setup_surface_with_settings_that_match_display(
      ALLEGRO_DISPLAY* display,
      int surface_width,
      int surface_height
   )
{
   if (!display)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::RenderSurfaces::Bitmap::setup_surface_with_settings_that_match_display",
         "A valid display must be present."
      );
   }
   //if (surface_width < 1 || surface_height < 1)
   //{
      //AllegroFlare::Logger::throw_error(
         //"AllegroFlare::RenderSurfaces::Bitmap::setup_surface_with_settings_that_match_display",
         //"Surface cannot have neither width or height less than 1."
      //);
   //}

   //int display_num_samples = al_get_display_option(display, ALLEGRO_SAMPLES);
   //int display_depth_size = al_get_display_option(display, ALLEGRO_DEPTH_SIZE);

   set_surface_width(surface_width);
   set_surface_height(surface_height);
   set_multisamples(al_get_display_option(display, ALLEGRO_SAMPLES));
   set_depth(al_get_display_option(display, ALLEGRO_DEPTH_SIZE));
   //set_surface_width(surface_width);
   //set_surface_height(surface_height);

   // TODO: include min linear, mag linear, and no preserve texture

   //setup_surface(); //surface_width, surface_height, display_num_samples, display_depth_size);
   //initialized = true;
   config_has_changed = false;
}


bool Bitmap::set_as_target()
{
   if (!initialized)
   {
      throw std::runtime_error("AllegroFlare::RenderSurface::Bitmap::set_as_target: error: not initialized");
      return false;
   }
   if (config_has_changed)
   {
      throw std::runtime_error("AllegroFlare::RenderSurface::Bitmap::set_as_target: error: config has changed");
      return false;
   }

   al_set_target_bitmap(surface);
   return true;
}


void Bitmap::set_clear_color(ALLEGRO_COLOR clear_color)
{
   this->clear_color = clear_color;
}



ALLEGRO_COLOR Bitmap::get_clear_color()
{
   return clear_color;
}


ALLEGRO_BITMAP *Bitmap::obtain_surface()
{
   if (!initialized) throw std::runtime_error("AllegroFlare::RenderSurface::Bitmap::get_surface_bitmap: error: not setup");
   if (config_has_changed)
   {
      throw std::runtime_error("AllegroFlare::RenderSurface::Bitmap::get_surface_bitmap: error: config has changed");
      //throw std::runtime_error("AllegroFlare::RenderSurface::Bitmap::set_as_target: error: config has changed");
      return nullptr;
   }
   //if (!initialized) throw std::runtime_error("AllegroFlare::RenderSurface::Bitmap::get_surface_bitmap: error: not setup");
   return surface;
}


void Bitmap::clear_surface()
{
   if (!initialized) throw std::runtime_error("AllegroFlare::RenderSurface::Bitmap::clear_surface: error: not setup");
   if (config_has_changed)
   {
      throw std::runtime_error("AllegroFlare::RenderSurface::Bitmap::clear_surface: error: config has changed");
      //throw std::runtime_error("AllegroFlare::RenderSurface::Bitmap::set_as_target: error: config has changed");
      //return false;
   }
   //if (!initialized) throw std::runtime_error("AllegroFlare::RenderSurface::Bitmap::get_surface_bitmap: error: not setup");

   al_clear_to_color(clear_color);
   al_clear_depth_buffer(1); // This clears on the display, but not necessarily the bitmap?
                             // TODO: Ask if bitmaps can have their depth buffer cleared
}


int Bitmap::get_width()
{
   if (!initialized) throw std::runtime_error("AllegroFlare::RenderSurface::Bitmap::get_width: error: not setup");
   if (config_has_changed)
   {
      throw std::runtime_error("asdfasdfasdfa");
   }
   return al_get_bitmap_width(surface);
}


int Bitmap::get_height()
{
   if (!initialized) throw std::runtime_error("AllegroFlare::RenderSurface::Bitmap::get_height: error: not setup");
   if (config_has_changed)
   {
      throw std::runtime_error("qjsajsdiofahpgd");
   }
   return al_get_bitmap_height(surface);
}


} // namespace RenderSurfaces
} // namespace AllegroFlare


