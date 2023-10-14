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
            class ThumbnailWithLabelUnlockableRenderer : public AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::Base
            {
            public:
               static constexpr char* TYPE = (char*)"AllegroFlare/Elements/ChapterSelect/CarouselElementRenderers/ThumbnailWithLabelUnlockableRenderer";

            private:
               AllegroFlare::BitmapBin* bitmap_bin;
               AllegroFlare::FontBin* font_bin;
               std::string thumbnail_image_identifier;
               std::string label_text;
               std::string locked_thumbnail_image_identifier;
               std::string locked_label_text;
               bool is_locked;
               float padding_x;
               float padding_y;
               float label_y_gutter;
               ALLEGRO_BITMAP* obtain_thumbnail_image();
               ALLEGRO_FONT* obtain_label_font();

            protected:


            public:
               ThumbnailWithLabelUnlockableRenderer(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr);
               ~ThumbnailWithLabelUnlockableRenderer();

               void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
               void set_font_bin(AllegroFlare::FontBin* font_bin);
               void set_thumbnail_image_identifier(std::string thumbnail_image_identifier);
               void set_label_text(std::string label_text);
               void set_locked_thumbnail_image_identifier(std::string locked_thumbnail_image_identifier);
               void set_locked_label_text(std::string locked_label_text);
               void set_is_locked(bool is_locked);
               void set_padding_x(float padding_x);
               void set_padding_y(float padding_y);
               void set_label_y_gutter(float label_y_gutter);
               AllegroFlare::BitmapBin* get_bitmap_bin() const;
               AllegroFlare::FontBin* get_font_bin() const;
               std::string get_thumbnail_image_identifier() const;
               std::string get_label_text() const;
               std::string get_locked_thumbnail_image_identifier() const;
               std::string get_locked_label_text() const;
               bool get_is_locked() const;
               float get_padding_x() const;
               float get_padding_y() const;
               float get_label_y_gutter() const;
               void render();
               float calculate_width();
               float calculate_height();
               float calculate_label_text_line_height();
            };
         }
      }
   }
}



