#pragma once


#include <AllegroFlare/Vec2D.hpp>
#include <ostream>


bool operator==(const AllegroFlare::Vec2D& vec, const AllegroFlare::Vec2D& other_vec);


namespace AllegroFlare
{
   void PrintTo(const AllegroFlare::Vec2D& vec, ::std::ostream* os);
}


