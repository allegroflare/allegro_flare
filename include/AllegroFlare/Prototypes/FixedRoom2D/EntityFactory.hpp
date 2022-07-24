#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Entities/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace FixedRoom2D
      {
         class EntityFactory
         {
         private:
            AllegroFlare::BitmapBin* bitmap_bin;

         public:
            EntityFactory(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
            ~EntityFactory();

            AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* create_chair_entity(float x=1920/2, float y=1080/2);
            AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* create_entity(std::string bitmap_image_identifier="[unset-bitmap_identifier]", float x=1920/2, float y=1080/2, float scale=1.0f, std::string name="[unset-name]", std::string on_interact_script_name="[unset-on_interact_script_name]");
         };
      }
   }
}



