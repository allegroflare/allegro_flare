#pragma once


#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_color.h>
#include <ostream>


bool operator==(const ALLEGRO_COLOR& color, const ALLEGRO_COLOR& other_color);
void PrintTo(const ALLEGRO_COLOR& color, ::std::ostream* os);


bool operator==(const AllegroFlare::vec2d& vec, const AllegroFlare::vec2d& other_vec);
namespace AllegroFlare
{
   void PrintTo(const AllegroFlare::vec2d& vec, ::std::ostream* os);
}


