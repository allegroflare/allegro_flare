

#include <AllegroFlare/Elements/Backgrounds/Monoplex.hpp>

#include <AllegroFlare/Placement2D.hpp>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace Backgrounds
{


Monoplex::Monoplex(AllegroFlare::BitmapBin* bitmap_bin)
   : AllegroFlare::Elements::Backgrounds::Base(AllegroFlare::Elements::Backgrounds::Monoplex::TYPE)
   , bitmap_bin(bitmap_bin)
   , monoplex_1_counter(0)
   , monoplex_2_counter(0)
   , monoplex_3_counter(0)
{
}


Monoplex::~Monoplex()
{
}


void Monoplex::update()
{
   monoplex_1_counter += 60.0/1.0f * 0.0001;
   monoplex_2_counter += 60.0/1.0f * 0.0001;
   monoplex_3_counter += 60.0/1.0f * 0.0001;
   return;
}

void Monoplex::render()
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Backgrounds::Monoplex::render]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Backgrounds::Monoplex::render]: error: guard \"bitmap_bin\" not met");
   }
   float screen_cx = 1920/2;
   float screen_cy = 1080/2;
   float time_now = al_get_time();
   ALLEGRO_BITMAP *monoplex_1_bitmap = bitmap_bin->auto_get("monoplex-1.png");
   ALLEGRO_BITMAP *monoplex_2_bitmap = bitmap_bin->auto_get("monoplex-2.png");
   ALLEGRO_BITMAP *monoplex_3_bitmap = bitmap_bin->auto_get("monoplex-3.png");
   AllegroFlare::Placement2D monoplex_1_place{screen_cx, screen_cy, 800, 800};
   AllegroFlare::Placement2D monoplex_2_place{screen_cx, screen_cy, 800, 800};
   AllegroFlare::Placement2D monoplex_3_place{screen_cx, screen_cy, 800, 800};

   monoplex_1_place.rotation = monoplex_1_counter * 0.95;
   monoplex_2_place.rotation = sin(monoplex_2_counter * 2) * -1.8;
   monoplex_3_place.rotation = monoplex_3_counter * -1.0;

   float monoplex_1_scale = sin(monoplex_1_counter * 4) * 0.3 + 2.6 + 0.5;
   float monoplex_2_scale = sin(monoplex_2_counter * 4) * 0.5 + 2.6 + 0.5;
   float monoplex_3_scale = sin(monoplex_3_counter * 4) * 0.9 + 2.6 + 0.5;

   monoplex_1_place.scale.x = monoplex_1_place.scale.y = monoplex_1_scale;
   monoplex_2_place.scale.x = monoplex_2_place.scale.y = monoplex_2_scale;
   monoplex_3_place.scale.x = monoplex_3_place.scale.y = monoplex_3_scale;

   monoplex_1_place.start_transform();
   al_draw_bitmap(monoplex_1_bitmap, 0, 0, 0);
   monoplex_1_place.restore_transform();

   monoplex_2_place.start_transform();
   al_draw_bitmap(monoplex_2_bitmap, 0, 0, 0);
   monoplex_2_place.restore_transform();

   monoplex_3_place.start_transform();
   al_draw_bitmap(monoplex_3_bitmap, 0, 0, 0);
   monoplex_3_place.restore_transform();

   return;
}


} // namespace Backgrounds
} // namespace Elements
} // namespace AllegroFlare


