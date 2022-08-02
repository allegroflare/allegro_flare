#pragma once


#include <AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/Color.hpp>
#include <allegro5/allegro_color.h>
#include <ostream>

#include <AllegroFlare/Testing/Comparison/ALLEGRO_COLOR.hpp>
#include <AllegroFlare/Testing/Comparison/AllegroFlare/Vec2D.hpp>


namespace AllegroFlare
{
   void PrintTo(const AllegroFlare::Color& color, ::std::ostream* os);
}


