#pragma once


#include <AllegroFlare/Vec2D.hpp>
#include <ostream>

bool operator==(const AllegroFlare::vec2d& vec, const AllegroFlare::vec2d& other_vec);


namespace AllegroFlare
{
   void PrintTo(const AllegroFlare::vec2d& vec, ::std::ostream* os);
}


