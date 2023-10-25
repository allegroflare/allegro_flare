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
         public:
            static constexpr char* DEFAULT_CHARACTER_NAME_FONT_NAME = (char*)"Inter-Medium.ttf";
            static constexpr int DEFAULT_CHARACTER_NAME_FONT_SIZE = -120;
            static constexpr char* DEFAULT_DESCRIPTION_FONT_NAME = (char*)"Inter-Regular.ttf";
            static constexpr int DEFAULT_DESCRIPTION_FONT_SIZE = -44;
            static constexpr float DEFAULT_DURATION = 6.0f;

         private:
            AllegroFlare::FontBin* font_bin;
            AllegroFlare::BitmapBin* bitmap_bin;
            std::string character_name;
            std::string description;
            std::string character_image_identifier;
            float duration;
            float age;
            std::string character_name_font_name;
            int character_name_font_size;
            std::string description_font_name;
            int description_font_size;
            ALLEGRO_FONT* obtain_character_name_font();
            ALLEGRO_FONT* obtain_description_font();
            ALLEGRO_BITMAP* obtain_character_image();

         protected:


         public:
            CharacterFeatureRenderer(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, std::string character_name="[unset-character_name]", std::string description="[unset-description]", std::string character_image_identifier="[unset-character_image_identifier]", float duration=DEFAULT_DURATION, float age=999.0, std::string character_name_font_name=DEFAULT_CHARACTER_NAME_FONT_NAME, int character_name_font_size=DEFAULT_CHARACTER_NAME_FONT_SIZE, std::string description_font_name=DEFAULT_DESCRIPTION_FONT_NAME, int description_font_size=DEFAULT_DESCRIPTION_FONT_SIZE);
            ~CharacterFeatureRenderer();

            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_character_name(std::string character_name);
            void set_description(std::string description);
            void set_character_image_identifier(std::string character_image_identifier);
            void set_duration(float duration);
            void set_age(float age);
            void set_character_name_font_name(std::string character_name_font_name);
            void set_character_name_font_size(int character_name_font_size);
            void set_description_font_name(std::string description_font_name);
            void set_description_font_size(int description_font_size);
            AllegroFlare::FontBin* get_font_bin() const;
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            std::string get_character_name() const;
            std::string get_description() const;
            std::string get_character_image_identifier() const;
            float get_duration() const;
            float get_age() const;
            std::string get_character_name_font_name() const;
            int get_character_name_font_size() const;
            std::string get_description_font_name() const;
            int get_description_font_size() const;
            void render();
         };
      }
   }
}



