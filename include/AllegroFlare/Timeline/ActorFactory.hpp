#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Timeline/Actors/Actor2D.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Timeline
   {
      class ActorFactory
      {
      private:
         AllegroFlare::BitmapBin* bitmap_bin;

      public:
         ActorFactory(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
         ~ActorFactory();

         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
         AllegroFlare::BitmapBin* get_bitmap_bin();
         AllegroFlare::Timeline::Actors::Actor2D* create_actor2d_with_script(std::string identifier="[unset-identifier]", std::string bitmap_identifier="[unset-bitmap_identifier]", std::string script="[unset-bitmap_identifier]");
      };
   }
}



