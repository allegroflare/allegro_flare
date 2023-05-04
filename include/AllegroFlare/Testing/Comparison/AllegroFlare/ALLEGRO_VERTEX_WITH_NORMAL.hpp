#pragma once


#include <AllegroFlare/ALLEGRO_VERTEX_WITH_NORMAL.hpp>
#include <ostream>


namespace AllegroFlare
{
   bool operator==(const ALLEGRO_VERTEX_WITH_NORMAL& object, const ALLEGRO_VERTEX_WITH_NORMAL& other_object);
   bool operator!=(const ALLEGRO_VERTEX_WITH_NORMAL& object, const ALLEGRO_VERTEX_WITH_NORMAL& other_object);
   void PrintTo(const ALLEGRO_VERTEX_WITH_NORMAL& object, ::std::ostream* os);
}


