#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace DialogBoxRenderers
      {
         class CharacterFeatureRenderer
         {
         private:
            AllegroFlare::FontBin* font_bin;
            AllegroFlare::BitmapBin* bitmap_bin;
            std::string character_name;
            std::string description;
            std::string character_image_identifier;
            float age;
            ALLEGRO_FONT* obtain_character_name_font();
            ALLEGRO_FONT* obtain_description_font();

         protected:


         public:
            CharacterFeatureRenderer(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, std::string character_name="[unset-character_name]", std::string description="[unset-description]", std::string character_image_identifier="[unset-character_image_identifier]", float age=999.0);
            ~CharacterFeatureRenderer();

            void render();
         };
      }
   }
}



