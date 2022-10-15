

#include <AllegroFlare/Integrations/CameraProjectionChanges.hpp>




namespace AllegroFlare
{
namespace Integrations
{


CameraProjectionChanges::CameraProjectionChanges()
   : framework()
   , platforming_2d()
{
}


CameraProjectionChanges::~CameraProjectionChanges()
{
}


void CameraProjectionChanges::initialize()
{
   framework.disable_fullscreen();
   framework.initialize();
   framework.get_bitmap_bin_ref().set_full_path("/Users/markoates/Repos/allegro_flare/bin/data/bitmaps");

   initialize_platforming_2d();

   framework.register_screen("platforming_2d", &platforming_2d);

   return;
}

void CameraProjectionChanges::initialize_tile_drive()
{
   return;
}

void CameraProjectionChanges::initialize_platforming_2d()
{
   AllegroFlare::Prototypes::Platforming2D::Screen platforming_2d;
   platforming_2d.set_bitmap_bin(&framework.get_bitmap_bin_ref());
   platforming_2d.set_display(framework.get_primary_display());
   platforming_2d.set_event_emitter(&framework.get_event_emitter_ref());
   platforming_2d.set_map_dictionary({
      { "map_a", "/Users/markoates/Repos/allegro_flare/bin/data/maps/map1-0x.tmj" },
      { "map_b", "/Users/markoates/Repos/allegro_flare/bin/data/maps/map1b-0x.tmj" },
   });
   platforming_2d.initialize_maps();
   platforming_2d.set_currently_active_map("map_a");
   return;
}


} // namespace Integrations
} // namespace AllegroFlare


