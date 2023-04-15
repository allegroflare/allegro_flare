#pragma once


#include <AllegroFlare/Model3D.hpp> // TODO: Move ALLEGRO_FLARE_VERTEX_WITH_NORMAL out of Model3D
#include <ostream>


namespace AllegroFlare
{
   bool operator==(const ALLEGRO_VERTEX_WITH_NORMAL& object, const ALLEGRO_VERTEX_WITH_NORMAL& other_object);
   bool operator!=(const ALLEGRO_VERTEX_WITH_NORMAL& object, const ALLEGRO_VERTEX_WITH_NORMAL& other_object);
   void PrintTo(const ALLEGRO_VERTEX_WITH_NORMAL& object, ::std::ostream* os);
}


