#pragma once


#include <AllegroFlare/FrameAnimation/Animation.hpp>
#include <AllegroFlare/FrameAnimation/SpriteSheet.hpp>
#include <allegro5/allegro.h>
#include <map>
#include <string>


namespace AllegroFlare
{
   namespace FrameAnimation
   {
      class Book
      {
      private:
         std::string png_source_filename;
         std::string json_source_filename;
         int sprite_sheet_scale;
         AllegroFlare::FrameAnimation::SpriteSheet* sprite_sheet;
         std::map<std::string, AllegroFlare::FrameAnimation::Animation> dictionary;
         bool initialized;
         void _build_placeholder_dictionary();

      protected:


      public:
         Book(std::string png_source_filename="./bin/data/bitmaps/sprites_grid-x.png", std::string json_source_filename="./bin/data/bitmaps/sprites_grid-x.json", int sprite_sheet_scale=5);
         ~Book();

         void set_dictionary(std::map<std::string, AllegroFlare::FrameAnimation::Animation> dictionary);
         int get_sprite_sheet_scale() const;
         void set_sprite_sheet_scale(int sprite_sheet_scale=5);
         AllegroFlare::FrameAnimation::SpriteSheet* get_sprite_sheet();
         void initialize();
         ALLEGRO_BITMAP* get_still_frame(std::string tag_name="[unset-tag_name]");
         bool animation_exists(std::string name="[unset-name]");
         AllegroFlare::FrameAnimation::Animation find_animation_by_name(std::string name="[unset-name]");
      };
   }
}



