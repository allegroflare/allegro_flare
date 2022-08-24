#pragma once


#include <string>
#include <AllegroFlare/Timeline/Actors/Base.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare::Timeline::Actors
{
   class Actor2D : public Base
   {
   public:
      ALLEGRO_BITMAP *bitmap;

      Actor2D(std::string identifier="[unidentified-Actor2D]", ALLEGRO_BITMAP *bitmap=nullptr);
      ~Actor2D();

      // IMPORTANT
      void register_params();
      void render(double time);
   };
}



