

#include <AllegroFlare/WorldMapRenderers/Basic.hpp>

#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/WorldMaps/Locations/Basic.hpp>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace WorldMapRenderers
{


Basic::Basic(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::WorldMaps::Maps::Basic* map, std::string quote)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , map(map)
   , quote(quote)
{
}


Basic::~Basic()
{
}


void Basic::set_map(AllegroFlare::WorldMaps::Maps::Basic* map)
{
   this->map = map;
}


AllegroFlare::WorldMaps::Maps::Basic* Basic::get_map() const
{
   return map;
}


void Basic::render_location(AllegroFlare::WorldMaps::Locations::Base* location)
{
   if (!(location))
   {
      std::stringstream error_message;
      error_message << "[Basic::render_location]: error: guard \"location\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic::render_location: error: guard \"location\" not met");
   }
   if (location->is_type(AllegroFlare::WorldMaps::Locations::Basic::TYPE))
   {
      float size = 20;
      AllegroFlare::WorldMaps::Locations::Basic *as =
         static_cast<AllegroFlare::WorldMaps::Locations::Basic*>(location);
      // TODO: Do some nice rendering
      //ALLEGRO_COLOR point_color = ALLEGRO_COLOR{0.5, 0.8, 0.89, 1.0};
      ALLEGRO_COLOR point_color = ALLEGRO_COLOR{0.96, 0.89, 0.5, 1.0}; // A yellow color
      ALLEGRO_COLOR outline_color = ALLEGRO_COLOR{0.2, 0.18, 0.0, 1.0}; // A dark brown color
      al_draw_filled_circle(as->get_x(), as->get_y(), size * 0.5, point_color);
      al_draw_circle(as->get_x(), as->get_y(), size * 0.5, outline_color, 3.0f);
   }
   else
   {
      AllegroFlare::Logger::throw_unhandled_case(
         "AllegroFlare::WorldMapRenderers::Basic::render_location",
         location->get_type()
      );
   }
   return;
}

void Basic::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Basic::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Basic::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic::render: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Basic::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic::render: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[Basic::render]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic::render: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Basic::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic::render: error: guard \"font_bin\" not met");
   }
   if (!(map))
   {
      std::stringstream error_message;
      error_message << "[Basic::render]: error: guard \"map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic::render: error: guard \"map\" not met");
   }
   // Draw the background
   al_draw_bitmap(obtain_background_image(), 0, 0, 0);

   // background_image_identifier
   for (auto &location : map->get_locations())
   {
      render_location(location.second);
   }
   return;
   return;
}

ALLEGRO_FONT* Basic::obtain_font()
{
   return font_bin->auto_get("Inter-Medium.ttf -52");
}

ALLEGRO_BITMAP* Basic::obtain_background_image()
{
   return bitmap_bin->auto_get(map->get_background_image_identifier());
}


} // namespace WorldMapRenderers
} // namespace AllegroFlare


