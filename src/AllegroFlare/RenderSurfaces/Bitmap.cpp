

#include <AllegroFlare/RenderSurfaces/Bitmap.hpp>

#include <allegro5/allegro.h>
#include <AllegroFlare/Color.hpp> // for color::transparent
#include <AllegroFlare/Logger.hpp>



namespace AllegroFlare
{
namespace RenderSurfaces
{


Bitmap::Bitmap(int surface_width, int surface_height, int multisamples, int depth)
   : AllegroFlare::RenderSurfaces::Base(AllegroFlare::RenderSurfaces::Bitmap::TYPE)
   , surface(nullptr)
   , surface_width(surface_width)
   , surface_height(surface_height)
   , multisamples(multisamples)
   , depth(depth)
   , initialized(false)
   , clear_color(AllegroFlare::Color::Eigengrau)
{
}


Bitmap::~Bitmap()
{
}


static bool ignore_dep_error_NOTE_please_faze_out = false;

void Bitmap::initialize()
{
   // TODO: add guard for duplicate initialization
   // TODO: eventually remove this flag
   ignore_dep_error_NOTE_please_faze_out = true;
   setup_surface(surface_width, surface_height, multisamples, depth);
   ignore_dep_error_NOTE_please_faze_out = false;
}


void Bitmap::setup_surface(int surface_width, int surface_height, int multisamples, int depth)
{
   // TODO: add guard for duplicate initialization
   if (!ignore_dep_error_NOTE_please_faze_out)
   {
      AllegroFlare::Logger::warn_from("AllegroFlare::RenderSurfaces::Bitmap::setup_surface", "Using \"setup_surface\" "
                                      "is depreciated. Please assign the required values and call initialize().");
   }

   int previous_samples = al_get_new_bitmap_samples();
   int previous_depth = al_get_new_bitmap_depth();

   al_store_state(&previous_state, ALLEGRO_STATE_TARGET_BITMAP);

   // create a new render surface if the proper surface does not exist
   if (!surface
       || al_get_bitmap_width(surface) != surface_width
       || al_get_bitmap_height(surface) != surface_height
       || al_get_bitmap_samples(surface) != multisamples
       || al_get_bitmap_depth(surface) != depth
      )
   {
      al_destroy_bitmap(surface);
      al_set_new_bitmap_samples(multisamples);
      al_set_new_bitmap_depth(depth);

      surface = al_create_bitmap(surface_width, surface_height);
      this->surface_width = surface_width;
      this->surface_height = surface_height;
      this->multisamples = multisamples;
      this->depth = depth;
   }


   // TODO:
   //al_get_bitmap_depth(surface);
   //al_get_bitmap_samples(surface);


   al_set_target_bitmap(surface);
   al_clear_to_color(color::transparent);
   al_restore_state(&previous_state);

   initialized = true;
}


// TODO: find a way to optionally clear_to_color and clear_depth
//void Bitmap::set_as_target(bool clear_to_color, bool clear_depth)
bool Bitmap::set_as_target()
{
   // TODO: find a way to optionally use clear_to_color and clear_depth
   bool clear_to_color = true;
   bool clear_depth = true;

   if (!initialized)
   {
      throw std::runtime_error("AllegroFlare::RenderSurface::Bitmap::set_as_target: error: not initialized");
      return false;
   }

   al_set_target_bitmap(surface);

   if (clear_to_color) al_clear_to_color(clear_color);
   if (clear_depth) al_clear_to_color(clear_color); // TODO: actually clear depth buffer
   //al_set_target_bitmap(
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
   return surface;
}


int Bitmap::get_width()
{
   if (!initialized) throw std::runtime_error("AllegroFlare::RenderSurface::Bitmap::get_width: error: not setup");
   return al_get_bitmap_width(surface);
}


int Bitmap::get_height()
{
   if (!initialized) throw std::runtime_error("AllegroFlare::RenderSurface::Bitmap::get_height: error: not setup");
   return al_get_bitmap_height(surface);
}


} // namespace RenderSurfaces
} // namespace AllegroFlare


