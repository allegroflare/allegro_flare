#pragma once


#include <AllegroFlare/Vec3D.hpp>
#include <ostream>


bool operator==(const AllegroFlare::Vec3D& vec, const AllegroFlare::Vec3D& other_vec);


namespace AllegroFlare
{
   void PrintTo(const AllegroFlare::Vec3D& vec, ::std::ostream* os);
}


