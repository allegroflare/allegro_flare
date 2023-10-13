#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/ChapterSelect/CarouselElementRenderers/Base.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace ChapterSelect
      {
         namespace CarouselElementRenderers
         {
            class ThumbnailWithLabelRenderer : public AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::Base
            {
            public:
               static constexpr char* TYPE = (char*)"AllegroFlare/Elements/ChapterSelect/CarouselElementRenderers/ThumbnailWithLabelRenderer";

            private:
               AllegroFlare::BitmapBin* bitmap_bin;
               AllegroFlare::FontBin* font_bin;
               std::string thumbnail_image_identifier;
               std::string label_text;
               ALLEGRO_BITMAP* obtain_thumbnail_image();
               ALLEGRO_FONT* obtain_label_font();

            protected:


            public:
               ThumbnailWithLabelRenderer();
               ~ThumbnailWithLabelRenderer();

               void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
               void set_font_bin(AllegroFlare::FontBin* font_bin);
               void set_thumbnail_image_identifier(std::string thumbnail_image_identifier);
               void set_label_text(std::string label_text);
               AllegroFlare::BitmapBin* get_bitmap_bin() const;
               AllegroFlare::FontBin* get_font_bin() const;
               std::string get_thumbnail_image_identifier() const;
               std::string get_label_text() const;
               void render();
            };
         }
      }
   }
}



