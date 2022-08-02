#pragma once


#include <AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/Color.hpp>
#include <allegro5/allegro_color.h>
#include <ostream>

#include <AllegroFlare/Testing/Comparison/ALLEGRO_COLOR.hpp>


bool operator==(const AllegroFlare::Vec2D& vec, const AllegroFlare::Vec2D& other_vec);

namespace AllegroFlare
{
   void PrintTo(const AllegroFlare::Vec2D& vec, ::std::ostream* os);
   void PrintTo(const AllegroFlare::Color& color, ::std::ostream* os);
}


