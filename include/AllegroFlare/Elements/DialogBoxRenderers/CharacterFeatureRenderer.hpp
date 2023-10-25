#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
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
            ALLEGRO_BITMAP* obtain_character_image();

         protected:


         public:
            CharacterFeatureRenderer(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, std::string character_name="[unset-character_name]", std::string description="[unset-description]", std::string character_image_identifier="[unset-character_image_identifier]", float age=999.0);
            ~CharacterFeatureRenderer();

            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_character_name(std::string character_name);
            void set_description(std::string description);
            void set_character_image_identifier(std::string character_image_identifier);
            void set_age(float age);
            AllegroFlare::FontBin* get_font_bin() const;
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            std::string get_character_name() const;
            std::string get_description() const;
            std::string get_character_image_identifier() const;
            float get_age() const;
            void render();
         };
      }
   }
}



